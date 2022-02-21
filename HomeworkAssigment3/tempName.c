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
#define MEAN_KB 20
#define LOW_KB 1




//Structure to store a process info
struct PCM {
    int processID; //get process id
    int numberCycles; //number of CPU cycles for the process
    int memorySize;
};
/*Creates the PCM structure with parameters of process id, 
number cycles, and memory size */
struct PCM *pcmObject (int processID, int numberCycles, int memorySize) {
    struct PCM *selfPCM = NULL;
    selfPCM = (struct PCM*)calloc(1, sizeof(struct PCM));
    selfPCM -> processID = processID;
    selfPCM-> numberCycles = numberCycles;
    selfPCM -> memorySize = memorySize;
    return selfPCM;
}

int pcm_getPID(struct PCM *p){
    if(!p) {
        return -1;
    }
    return p -> processID;
}

int pcm_getNumCycles(struct PCM *p) {
    if(!p){
        return 0;
    }
    return p->numberCycles;
}

int pcm_getMemSize(struct PCM *p) {
    if(!p) {
        return 0;
    }
    return p -> memorySize;
}
//Delete the PCM object
void delete_PCM(struct PCM *p) {
    if(p) {
        free(p);
    }
    return;
}
//Peints the values in a PCM object
void print_PCM(struct PCM *p) {
     printf("PID=%d, Number of CPU Cycles=%d, Memory Size(KB)=%d\n", p->processID, p->numberCycles, p->memorySize);
}


void pcm_printCSV(struct PCM *p){
    printf("\t%d \t\t%d \t\t %d\n", p->processID, p->numberCycles, p->memorySize);
}

//Using the a linklist data structure to store the data

struct Node {
    struct PCM *data; 
    struct Node *next;
};

struct dataTable {
    int numberProcess;
    int totalOfCyles;
    int totalOfMemory;
    struct Node *head;
    struct Node *tail;
};

int generateNumberCycles(){
    int cycles = (rand()%(HIGH_CYCLES - LOW_CYCLES)) + LOW_CYCLES;
    return cycles;
}

// int generateMemorySize(){
//     int upperbound;
//     int lowerbound;
//     int average;

//     switch (MEM_MODE)
//     {
//     case 0:
//         upperbound = HIGH_KB;
//         lowerbound = LOW_KB;
//         average = MEAN_KB;
//         break;
//     case 1:
//         upperbound = 
//     default:
//         break;
//     }
// }


int main () {
    int k;
    printf("Enter the number of process k: ");
    scanf("%d", &k);

}