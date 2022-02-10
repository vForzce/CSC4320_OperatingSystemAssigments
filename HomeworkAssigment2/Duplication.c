#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
 


int main() {
    if(fork() == 0){
        printf("Starting process B\n");
        if(fork() == 0){
            printf("Staring process A\n");
        }
    }

    pid_t processid = getpid();
    char* path = "IngterFile.txt"; //Creating a File
    for(int i = 0; i < 200; i++) {
        FILE* fp = fopen(path, "r"); //Open the File 
        int num = 0;
        fscanf (fp, "%d", &num); //Read Number
        fclose (fp); 
        printf("N: %d Process ID: %d\n", num, processid);
        fp = fopen(path, "a");
        num++;
        fprintf(fp, "%d", num);
        fclose(fp);
    }  
}

    
