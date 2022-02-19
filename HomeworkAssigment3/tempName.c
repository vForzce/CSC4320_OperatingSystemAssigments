#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<semaphore.h>
#include <sys/stat.h>
//Setting the interval for cycles
#define HIGH_CYCLES 11000
#define LOW_CYCLES 1000
#define MED_CYCLES 6000
//Setting the interval for the process memory footprint
#define HIGH_KB 100
#define LOW_KB 1



const char *path = "processLogs.txt";

int main () {
    pid_t pid = getid();
    int k;
    printf("Enter the number of process k: ");
    scanf("%d", &k);

}