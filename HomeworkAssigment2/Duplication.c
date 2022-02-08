#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>


int main(void) {
    char *path = "IngterFile";
    FILE *fp = fopen(path, "r");
    int num;
    if(fork() == 0) {
        printf("Process A has started\n");
    }
    
}