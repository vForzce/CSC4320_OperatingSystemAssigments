#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

const char* path = "Intger.txt"; //Creating a File

int main() {
    if(fork() == 0){
        printf("Starting process C\n");
        if(fork() == 0){
            printf("Staring process B\n");
            if(fork()== 0){
                printf("Starting process A\n");
            }
        }
    }

    pid_t processid = getpid();
    
    for(int i = 0; i <=200; i++) {
        FILE* fp = fopen(path, "r"); //Open the File 
        int num;
        fscanf (fp, "%d", &num); //Read Number
        rewind(fp);
        fclose (fp); 
        printf("N: %d Process ID: %d\n", num, processid);
        num++;
        fp = fopen(path, "w");
        fprintf(fp, "%d", num);
        rewind(fp);
        fclose(fp);
    }  
}

    
