#include<stdio.h>
#include<unistd.h>
#include<string.h>

static char files[20][20] = {"1024.dat", "2048.dat", "4096.dat", "8192.dat", "16384.dat","32768.dat","65536.dat","131072.dat","262144.dat","524288.dat","1048576.dat","2097152.dat","4194304.dat","8388608.dat","16777216.dat","33554432.dat","67108864.dat","134217728.dat","268435456.dat","536870912.dat"};
static int l1_data[32];
static int l2_data[32];
static int l3_data[32];
static int mem_data[32];
static char* res_file = "cache-stat.dat";
static char* ratio_file = "cache-ratio.dat";
static char* percent_file = "cache-percent.dat";
int get_min(int data[]);
int get_max(int data[]);
int get_mode(int data[]);

static int l1_unb, l2_unb, l3_unb, mem_unb;

int get_line_num(char *div);
int write_to_file(char *dir, int l1, int l2, int l3, int mem);

int clear_cache_stats(char *dir){
    FILE *fp;
    int i=1;
    if((fp = fopen(res_file, "w")) == NULL)
        return -1;
    fputs("#Sr\tLimit\t\tL1 Hit\tL2 hit\tL3 Hit\tMemory",fp);
    while(i<21){
        if(i == get_line_num(dir)){
            
        }
        i++;
    }
}

int write_to_file(char *dir, int l1, int l2, int l3, int mem){

    int line_num = 0, i = 0;
    float l2_l1, l3_l2, mem_l3;
    float sum;
    FILE *fp;
    char buffer_in[128], buffer_out[128], limit[8];
    printf("Dir: %s\n", dir);
    strncpy(limit, dir+4,4);
    limit[4] = '\0';
    printf("Limit: %s\n", limit);
    if((fp = fopen(res_file, "a")) == NULL)
        return -1;
    //fputs("#Sr\tLimit\t\tL1 Hit\tL2 hit\tL3 Hit\tMemory\n",fp);
    //while(i < 12){
    //        if(i == get_line_num(dir)){
    if(get_line_num(dir) != -1){
        sprintf(buffer_out, "%d\t%s \t%f\t\t%f\t\t%f\t\t%f\n",get_line_num(dir),limit,(float)l1/l1_unb,(float)l2/l2_unb,(float)l3/l3_unb,(float)mem/mem_unb);
        /*sprintf(buffer_out, "%2.1f\t%s \t%d\n",((float)get_line_num(dir) - 0.3),"    ",l1);
        fputs(buffer_out, fp);
        sprintf(buffer_out, "%2.1f\t%s \t%d\n",((float)get_line_num(dir) - 0.1),limit,l2);
        fputs(buffer_out, fp);
        sprintf(buffer_out, "%2.1f\t%s \t%d\n",((float)get_line_num(dir) + 0.1),"    ",l3);
        fputs(buffer_out, fp);
        sprintf(buffer_out, "%2.1f\t%s \t%d\n",((float)get_line_num(dir) + 0.3),"    ",mem);*/
        fputs(buffer_out, fp);
    }
    fclose(fp);
    if((fp = fopen(ratio_file, "a"))==NULL)
        return -1;
    
    l2_l1 = (float)l2/l1;
    l3_l2 = (float)l3/l2;
    mem_l3 = (float)mem/l3;
    printf("L2/L1 Ratio: %2.2f, L3/L2 Ratio: %2.2f, Mem/L3 Ratio: %2.2f\n", l2_l1, l3_l2, mem_l3);
    
    if(get_line_num(dir) != -1){
        sprintf(buffer_out, "%d\t%s \t%2.2f\t\t%2.2f\t\t%2.2f\n",get_line_num(dir),limit,l2_l1,l3_l2,mem_l3);
        fputs(buffer_out, fp);
    }  
    fclose(fp);     
    
    if((fp = fopen(percent_file, "a"))==NULL)
        return -1;
    
    sum = l1+l2+l3;
    printf("L1: %d, L2: %d, L3: %d, Sum: %f\n", l1,l2,l3,sum);
    printf("L1 pc: %2.2f, L2 pc: %2.2f, L3 pc: %2.2f\n", (((float)l1)*100/sum),(((float)l2)*100/sum),(((float) l3)*100/sum));
    
    if(get_line_num(dir) != -1){
        sprintf(buffer_out, "%d\t%s \t%2.2f\t\t%2.2f\t\t%2.2f\n",get_line_num(dir),limit,(((float) l1)*100/sum), (((float)l2)*100/sum), (((float)l3)*100/sum));
        fputs(buffer_out, fp);
    }  
    fclose(fp);  
    //        }
    //    i++;
    //}   
    return 0;
}

int get_max(int data[]){
    int max,i;
    i=0;
    max = data[0];
    while(i<32){
        if(max < data[i] && data[i] != (-1))
            max = data[i];
        i++;
    }
    return max;
}     

int get_min(int data[]){
    int min,i;
    i=0;
    min = data[0];
    while(i<32){
        if(min > data[i] && data[i] != (-1) && data[i] != 0)
            min = data[i];
        i++;
    }
    return min;
}

int get_mode(int data[]){
        int i, j, sum = 0, t, b[20] = {0}, k = 0, c = 1, max = 0, mode;
    float x = 0.0, y = 0.0;
    for (i = 0; i < 31; i++)
    {
        mode = 0;
        for (j = i + 1; j < 32; j++)
        {
            if (data[i] == data[j]) {
                mode++;
            }
        }
        if ((mode > max) && (mode != 0) && (data[i] != -1)) {
            k = 0;
            max = mode;
            b[k] = data[i];
            k++;
        }
        else if ((mode == max) && data[i] != -1) {
            b[k] = data[i];
            k++;
        }
    }
    for (i = 0; i < 32; i++)
    {
        if (data[i] == b[i]) 
            c++;
        }
        if (c == 32)
            printf("\nThere is no mode");
        else
        {
            printf("\nMode\t= ");
            for (i = 0; i < k; i++)
                printf("%d ",b[i]);
        }
        printf("\n");
        return 0;    
}

int get_l1_cache_latency(char *dir){
    
    int line_num=0;
    int mem_size;
    int max, min, range, mode;
    int l1_min = 1, l1_max = 4;
    char buffer[64], filename[16];
    char temp1[32], temp2[32], strdata[32];
    FILE *fp;
    int i = 0;
    /*while(i<10){
        printf("Filename: %s\n", files[i]);
        i++;
    }*/
    i=0;
    for(mem_size=0; mem_size < 5; mem_size++){
        sprintf(filename,"%s/%s",dir,files[mem_size]);
        //printf("Filename: %s\n", filename); 
        if((fp = fopen(filename, "r")) == NULL){
        return -1;
        }
        line_num=0;
        while(line_num <= l1_max){
            if(fgets(buffer, 64, fp) != NULL){
                if(line_num >= l1_min && line_num <= l1_max){
                    //printf("Data: %s",buffer);
                    sscanf(buffer, "%s\t%s\t%s\n", temp1, temp2, strdata); 
                    //printf("Strdata: %s\n", strdata);
                    l1_data[i] = atoi(strdata);
                    i++;
                }
            line_num++;
            }
        }
    }
    /*i=0;
    printf("l1 Data\n");
    while(l1_data[i] != -1){
        printf("%d, ", l1_data[i]);
        i++;
    }
    */
    min = get_min(l1_data);
    max = get_max(l1_data);
    range = max - min;
    fclose(fp);    
    //printf("\nRange: %d, Max: %d, Min: %d",range, max, min);
    //get_mode(l1_data);
    return min;
}

int get_l2_cache_latency(char *dir){
    
    int line_num=0;
    int mem_size;
    int max, min, range, mode;
    int l2_min = 5, l2_max = 8;
    char buffer[64], filename[16];
    char temp1[32], temp2[32], strdata[32];
    FILE *fp;
    int i = 0;
    /*while(i<10){
        printf("Filename: %s\n", files[i]);
        i++;
    }*/
    i=0;
    for(mem_size=6; mem_size < 9; mem_size++){
        sprintf(filename,"%s/%s",dir,files[mem_size]);
        //printf("Filename: %s\n", filename); 
        if((fp = fopen(filename, "r")) == NULL){
        return -1;
        }
        line_num=0;
        while(line_num <= l2_max){
            if(fgets(buffer, 64, fp) != NULL){
                if(line_num >= l2_min && line_num <= l2_max){
                    //printf("Data: %s",buffer);
                    sscanf(buffer, "%s\t%s\t%s\n", temp1, temp2, strdata); 
                    //printf("Strdata: %s\n", strdata);
                    l2_data[i] = atoi(strdata);
                    i++;
                }
            line_num++;
            }
        }
    }
    /*i=0;
    printf("l2 Data\n");
    while(l2_data[i] != -1){
        printf("%d, ", l2_data[i]);
        i++;
    }
    */
    min = get_min(l2_data);
    max = get_max(l2_data);
    range = max - min;
    fclose(fp);
    //printf("\nRange: %d, Max: %d, Min: %d",range, max, min);
    //get_mode(l2_data);
    return min;
}

int get_l3_cache_latency(char *dir){
    
    int l3_cache_latency;
    int line_num=0;
    int mem_size;
    int max, min, range, mode;
    int l1_min = 11, l1_max;
    char buffer[64], filename[16];
    char temp1[32], temp2[32], strdata[32];
    FILE *fp;
    int i = 0;
    /*while(i<10){
        printf("Filename: %s\n", files[i]);
        i++;
    }*/
    sprintf(filename,"%s/%s",dir,files[13]);
    printf("Filename: %s\n", filename); 
    if((fp = fopen(filename, "r")) == NULL){
        return -1;
    }
    while(line_num < 12){ 
        if(fgets(buffer, 64, fp) != NULL && line_num == 11){
            //printf("Data: %s",buffer);
            sscanf(buffer, "%s\t%s\t%s\n", temp1, temp2, strdata); 
            printf("Strdata: %s\n", strdata);
            l3_cache_latency =  atoi(strdata);
        }
        line_num++;
    }
    fclose(fp);
    return l3_cache_latency;
    /*
    i=0;
    for(mem_size=9; mem_size < 13; mem_size++){
        sprintf(filename,"%s/%s",dir,files[mem_size]);
        //printf("Filename: %s\n", filename); 
        if((fp = fopen(filename, "r")) == NULL){
            return -1;
        }
        switch(mem_size){
                        case 9:
                        l1_max=12;
                        break;
            
                        case 10:
                        l1_max=13;
                        break;

                        case 11:
                        l1_max=14;
                        break;

                        case 12:
                        l1_max=16;
                        break;
    
                        default:
                        l1_max=16;
        }
        line_num=0;
        while(line_num <= l1_max){
            if(fgets(buffer, 64, fp) != NULL){
                if(line_num >= l1_min && line_num <= l1_max){
                    //printf("Data: %s",buffer);
                    sscanf(buffer, "%s\t%s\t%s\n", temp1, temp2, strdata); 
                    //printf("Strdata: %s\n", strdata);
                    l3_data[i] = atoi(strdata);
                    i++;
                }
            line_num++;
            }
        }
    }
    i=0;
    printf("l3 Data\n");
    while(l3_data[i] != -1){
        printf("%d, ", l3_data[i]);
        i++;
    }
    min = get_min(l3_data);
    max = get_max(l3_data);
    range = max - min;
    
    printf("\nRange: %d, Max: %d, Min: %d",range, max, min);
    get_mode(l3_data);
    */
}
int get_mem_latency(char *dir){
    int mem_latency;
    int line_num=0; 
    FILE *fp;
    char buffer[32], filename[32];
    char temp1[32], temp2[32], strdata[32];
    
    sprintf(filename, "%s/%s",dir,files[19]);
    printf("Filename(mem_latency): %s\n", filename);
    if((fp = fopen(filename, "r")) == NULL)
        return -1;

    while(line_num < 20){ 
        if(fgets(buffer, 64, fp) != NULL && line_num == 19){
            //printf("Data: %s",buffer);
            sscanf(buffer, "%s\t%s\t%s\n", temp1, temp2, strdata); 
            printf("Strdata: %s\n", strdata);
            mem_latency =  atoi(strdata);
        }
        line_num++;
    }
    fclose(fp);
    return mem_latency;

}
int get_line_num(char *dir){
    int line;
    char limit[8];
    strncpy(limit, dir+4,4);
    limit[4] = '\0';
    int i = atoi(limit);
    if(strcmp(dir, "lim_none") == 0){ 
	line = 1;
	return line;
    }
    else if( i <= 4000 && i >= 125){
	
	printf("In Get Line Num. limit =  %d\n", i);
	line = i/125 + 1;
	printf("Line after div: %d\n", line);
	return line;
    }
    else if(strcmp(dir, "lim_4500") == 0)                   
        line = 34;
    else if(strcmp(dir, "lim_5000") == 0)                   
        line = 35;
    else if(strcmp(dir, "lim_5500") == 0)                   
        line = 36;
    else if(strcmp(dir, "lim_6000") == 0)                   
        line = 37;
    else if(strcmp(dir, "lim_6500") == 0)                   
        line = 38;   
    else if(strcmp(dir, "lim_7000") == 0)                   
        line = 39;
    else if(strcmp(dir, "lim_7500") == 0)                   
        line = 40;  
    else if(strcmp(dir, "lim_8000") == 0)                   
        line = 41;
    else if(strcmp(dir, "lim_8500") == 0)                   
        line = 42;   
    else if(strcmp(dir, "lim_9000") == 0)                   
        line = 43;
    else if(strcmp(dir, "lim_9500") == 0)                   
        line = 44;  
    else
        line = -1;                   
    
    return line;                
}
int main(int argc, char *argv[]){
    
    if (argc < 2 || argc > 2){
        printf("Usage: <program> <dir>\n");
    }
    int i=0;
    int l1,l2,l3,mem;
    while(i<32){
        l1_data[i] = -1;
        l2_data[i] = -1;
        l3_data[i] = -1;
        mem_data[i] = -1;
        i++;
    }
    if(get_l1_cache_latency(argv[1]) != 0)
    	l1 = get_l1_cache_latency(argv[1]);
    else
	l1 = 1;
    l2 = get_l2_cache_latency(argv[1]);
    l3 = get_l3_cache_latency(argv[1]);

    if(get_l1_cache_latency("lim_none") != 0)
    	l1_unb = get_l1_cache_latency("lim_none");
    else
	l1_unb = 1;
    l2_unb = get_l2_cache_latency("lim_none");
    l3_unb = get_l3_cache_latency("lim_none");

    if((mem = get_mem_latency(argv[1])) == (-1)){
        printf("Error: Mem latency = %d\n", mem);
        return -1;    
    }
    if((mem_unb = get_mem_latency("lim_none")) == (-1)){
        printf("Error: Mem latency = %d\n", mem);
        return -1;    
    }

    printf("L1: %d, L2: %d, L3: %d, Mem: %d\n", l1,l2,l3,mem);
    printf("Line num: %d\n", get_line_num(argv[1]));

    write_to_file(argv[1], l1, l2, l3, mem);
}
    
