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
    int numberOfProcess;
    int totalOfCyles;
    int totalOfMemory;
    struct Node *head;
    struct Node *tail;
};

//Generate a number between 1,000 and 11,000 with a mean of 6,000
int generateNumberCycles(){
    int cycles = (rand()%(HIGH_CYCLES - LOW_CYCLES)) + LOW_CYCLES;
    return cycles;
}

//Generate a number within a range of 1KB and 100KB  with a mean of 20KB
int generateMemorySize(){
    int upperbound = HIGH_KB;
    int lowerbound = LOW_CYCLES;
    int average = MEAN_KB;
    
    //Generates a number under the mean
    if((rand()% (upperbound - lowerbound)) > (average - lowerbound)) {
        return (rand()% (average - lowerbound)) + average;
    } else {
        //Generate a number over the mean
        return (rand()%(upperbound - average)) + average;
    }
}

int DataTable_GeneratingProcess(struct dataTable *pointer) {
    if(!pointer) {
        return -1;
    }
    //Creates a new node
    struct Node *newNode =  (struct Node*)calloc(1, sizeof(struct Node));
    if(!newNode) {
        return -1;
    }
    //The datatable is empty
    if(pointer -> head == NULL && pointer -> tail ==NULL) {
        //Creates a Process
        struct PCM *newPCM = pcmObject(1, generateNumberCycles(), generateMemorySize());
        
        if(!newPCM){
            return -1;
        
        }
        //Set values within the node
        newNode->data = newPCM;
        newNode->next = NULL;
        //Add the node to the datatable
        pointer->head =newNode;
        pointer->tail = newNode;
        pointer->totalOfCyles += pcm_getNumCycles(newPCM);
        pointer->totalOfMemory += pcm_getMemSize(newPCM);
        //Returns the process id
        return pcm_getPID(newPCM);
    } else if (pointer->tail) {
         //Creates a Process
        struct PCM *newPCM = pcmObject(pcm_getPID(pointer->tail->data), generateNumberCycles(), generateMemorySize());
         
         if(!newPCM){
            return -1;
        }
         //Set values within the node
        newNode->data = newPCM;
        newNode->next = NULL;
         //Add the node to the datatable
        pointer->tail->next = newNode;
        pointer->tail = newNode;
        pointer->totalOfCyles += pcm_getNumCycles(newPCM);
        pointer->totalOfMemory += pcm_getMemSize(newPCM);
        //Return the new process
        return pcm_getPID(newPCM); 
    } else {
        return -1;
    }

    return -1;
}

struct dataTable *newDataTable(int numberOfProcess) {
    struct dataTable *table = (struct dataTable *)calloc(1, sizeof(struct dataTable));
    
    for(int i = 0; i < numberOfProcess; i++) {
        if(DataTable_GeneratingProcess(table)) {
            table->numberOfProcess++;
        } else {
            printf("Error creating process %d\n", i);
        }
    }
    return table;
}

//Deletes process table
void delete_dataTable(struct dataTable *pointer) {
    if(pointer){
        free(pointer);
    }
    return;
}

//Looks for process within the dataTable
struct PCM *dataTable_getPID(struct dataTable *pointer, int processID) {
    if(!pointer) {
        return NULL;
    }
    struct Node *ptr;
    for(ptr = pointer->head; ptr != NULL; ptr = ptr->next){
        if(pcm_getPID(ptr->data) == processID){
            return ptr->data;
        }
        if(pcm_getPID(ptr->data) > processID) {
            return NULL;
        }
    }
    return NULL;
}

int dataTable_removeProcessByPID(struct dataTable *pointer, int pid) {
    
}


int main () {
    int k;
    printf("Enter the number of process k: ");
    scanf("%d", &k);

}