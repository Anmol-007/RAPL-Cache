#include <stdio.h>
#include <sys/times.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define CACHE_MIN (256) /* smallest cache */
//#define CACHE_MAX (2048) /* largest cache */
#define CACHE_MAX (65536*2048) /* largest cache */
#define SAMPLE 10 /* to get a larger time sample */
#ifndef CLK_TCK
#define CLK_TCK 60 /* number clock ticks per second */
#endif

int x[CACHE_MAX]; /* array going to stride through */
double get_seconds() { /* routine to read time */
    struct tms rusage;
    times(&rusage); /* UNIX utility: time in clock ticks */
    return (double) (rusage.tms_utime)/CLK_TCK;
}
void main() {
    int register i, index, stride, limit, temp;
    int steps, tsteps, csize;
    double sec0, sec; /* timing variables */
    //FILE *fp;
    //char buffer[32];
    //printf("Filename; %s", argv[1]);
    //printf("Clock Ticks per sec:%lu, CLK_TCK %lu\n", CLOCKS_PER_SEC, sysconf(_SC_CLK_TCK)); 
    for (csize=CACHE_MIN; csize <= CACHE_MAX; csize=csize*2){
        
       // sprintf(buffer, "unbounded/unb_%lu.dat", csize*sizeof(int));
        //fp = fopen(buffer, "w");
        //fprintf(fp, "Size of memory array: %lu\n", csize*sizeof(int));
        printf("Size of memory array: %lu\n", csize*sizeof(int));
        for (stride=1; stride <= csize/2; stride=stride*2) {
        sec = 0; /* initialize timer */
        limit = csize-stride+1; /* cache size this loop */
        steps = 0;
        do { /* repeat until collect 1 second */
            sec0 = get_seconds(); /* start timer */
            for (i=SAMPLE*stride;i!=0;i=i-1) /* larger sample */
            for (index=0; index < limit; index=index+stride)
            x[index] = x[index] + 1; /* cache access */
            steps += 1; /* count while loop iterations */
            sec = sec + (get_seconds() - sec0);/* end timer */
        }while (sec < 1.0);
       
        /* until collect 1 second */
        /* Repeat empty loop to subtract loop overhead */
        tsteps = 0; /* used to match no. while iterations */
        do { /* repeat until same no. iterations as above */
            sec0 = get_seconds(); /* start timer */
            for (i=SAMPLE*stride;i!=0;i=i-1) /* larger sample */
            for (index=0; index < limit; index=index+stride)
            temp += index; /* dummy code */
            tsteps += 1; /* count while iterations */
            sec = sec - (get_seconds() - sec0);/* - overhead */
        }while (tsteps<steps); /* until = no. iterations */
      
        //fprintf(fp, "%7lu\t%7lu \t%4.0lf\n", csize*sizeof(int), stride*sizeof(int), (double)
        //sec*1e9/(steps*SAMPLE*stride*((limit-1)/stride+1)));
        printf("%7lu\t%7lu\t\t%4.0lf\n", csize*sizeof(int), stride*sizeof(int), (double)
        sec*1e9/(steps*SAMPLE*stride*((limit-1)/stride+1)));
        }
        //fclose(fp);
    }; /* end of both outer for loops */
}




