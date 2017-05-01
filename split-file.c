
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

static int lines[21];
static char *dir;
void Usage(char *filename) {
    printf("Usage: %s <file> <dir>\n", filename);
    printf("%s version 1.0 \nCopyright(c) CodingUnit.com\n", filename);
}


int split_file(char *source){
    int csize, line_num;
    int i = 0,j = 1;
    int start,end;
    FILE *fpin,*fpout;
    char buffer[32];
    char line[64];
    csize = 1024;
    

    if((fpin = fopen(source, "r")) == NULL){
        return (-1);
    }
    while(i < 20){
        sprintf(buffer, "%s/%d.dat", dir,csize);
        if((fpout = fopen(buffer, "w")) == NULL){
            return(-1);
        }
        //printf("Filepath: %s\n", buffer);
        start = lines[i];
        end = lines[i+1];
        fputc('#', fpout);
        while(start < end){
            if((fgets(line,sizeof(line), fpin)) == NULL){
                return (-1);
            }else{
                if(j == start){
                    //fgets(line, 64, fpin);
                    fputs(line, fpout);
                    start++;        
                }
                j++;
            }
        } 
        csize *= 2;
        i++;
        fclose(fpout);
    }
}

int Search_in_File(char *fname, char *str) {
    FILE *fp;
    int line_num = 1;
    int find_result = 0;
    char temp[512];
    //gcc users
    if((fp = fopen(fname, "r")) == NULL) {
      return(-1);
    }
    int num = 21;
    
    while(fgets(temp, 512, fp) != NULL) {
        if((strstr(temp, str)) != NULL) {
            //printf("A match found on line: %d\n", line_num);
            //printf("\n%s\n", temp);
            lines[find_result] = line_num;
            find_result++;
        }
        line_num++;
    }
    lines[find_result] = line_num;
    printf("line_num: %d, find_result: %d\n", line_num, find_result);
    int i = 0;
    while(i<num){
        printf("%d, ",lines[i]);
        i++;
    }
    i=0;
    if(find_result == 0) {
        printf("\nSorry, couldn't find a match.\n");
    }
    printf("\nNum of results: %d\n",find_result); 
    //Close the file if still open.
    if(fp) {
        fclose(fp);
    }
    split_file(fname);
    return(0);
}

//Our main function.
int main(int argc, char *argv[]) {
    int result, errno;

    if(argc < 3 || argc > 3) {
        Usage(argv[0]);
        exit(1);
    }

    //Use system("cls") on windows
    //Use system("clear") on Unix/Linux
    system("clear");
    dir = argv[2];
    result = Search_in_File(argv[1], "Size");
    if(result == -1) {
        perror("Error");
        printf("Error number = %d\n", errno);
        exit(1);
    }
    return(0);
}


