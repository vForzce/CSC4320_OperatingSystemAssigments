#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>


//Setting the interval for cycles
#define HIGH_CYCLES 11000
#define LOW_CYCLES 1000
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
    struct PCM *selfPCM = (struct PCM*)calloc(1, sizeof(struct PCM));
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
}
//Points the values in a PCM object
void print_PCM(struct PCM *p) {
    printf("PID=%d, Number of CPU Cycles=%d, Memory Size(KB)=%d\n", p->processID, p->numberCycles, p->memorySize);
}


void pcm_printCSV(struct PCM *p){
    printf("\t%d \t\t%d \t\t %d\n", p->processID, p->numberCycles, p->memorySize);
}

//Using  a linklist data structure to store the data

struct Node {
    struct PCM *data;
    struct Node *next;
};

struct dataTable {
    int numberOfProcess;
    int totalOfCycles;
    int totalOfMemory;
    struct Node *head;
    struct Node *tail;
};

//Generate a number between 1,000 and 11,000 with a mean of 6,000
int generateNumberCycles(){
    int cycles = (rand() % (HIGH_CYCLES - LOW_CYCLES)) + LOW_CYCLES;
    return cycles;
}

//Generate a number within a range of 1 KB and 100 KB  with a mean of 20 KB
int generateMemorySize(){
    int upperbound = HIGH_KB;
    int lowerbound = LOW_KB;
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
    int i = 1;
    //Creates a new node
    struct Node *newNode =  (struct Node*)calloc(i, sizeof(struct Node));
    if(!newNode) {
        return -1;
    }
    //The datatable is empty
    if(pointer -> head == NULL && pointer -> tail ==NULL) {
        //Creates a Process
        
        struct PCM *newPCM = pcmObject(i, generateNumberCycles(), generateMemorySize());
        //Set values within the node
        newNode->data = newPCM;
        newNode->next = NULL;
        //Add the node to the datatable
        pointer->head =newNode;
        pointer->tail = newNode;
        pointer->totalOfCycles += pcm_getNumCycles(newPCM);
        pointer->totalOfMemory += pcm_getMemSize(newPCM);
        //Returns the process id
        return pcm_getPID(newPCM);
    } else if (pointer->tail) {
        //Creates a Process
        struct PCM *newPCM = pcmObject(pcm_getPID(pointer->tail->data), generateNumberCycles(), generateMemorySize());

        //Set values within the node
        newNode->data = newPCM;
        newNode->next = NULL;
        //Add the node to the datatable
        pointer->tail->next = newNode;
        pointer->tail = newNode;
        pointer->totalOfCycles += pcm_getNumCycles(newPCM);
        pointer->totalOfMemory += pcm_getMemSize(newPCM);
        //Return the new process
        return pcm_getPID(newPCM);
    } else {
        return -1;
    }
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
}

int dataTable_removeProcessByPID(struct dataTable *pointer, int processID) {
    if(!pointer) {
        return 0;
    }
    if(pcm_getPID(pointer->head->data) == processID) {
        struct PCM *pcmDeletePtr = pointer->head->data;
        struct Node *nodeDeletePtr = pointer->head;
        pointer->head = nodeDeletePtr->next;

        if(pointer->head == NULL){
            pointer->tail = NULL;
        }
        pointer->numberOfProcess--;
        pointer->totalOfCycles = pcm_getNumCycles(pcmDeletePtr);
        pointer->totalOfMemory = pcm_getMemSize(pcmDeletePtr);

        delete_PCM(pcmDeletePtr);
        free(nodeDeletePtr);
        pcmDeletePtr = NULL;
        nodeDeletePtr = NULL;
        //Successful
        return 1;
    } else {
        struct Node *ptr;
        struct Node *ptrNext;
        for(ptr = pointer->head; ptr!=NULL; ptr = ptr->next) {
            //Checks the next node
            ptrNext = ptr->next;
            if(pcm_getPID(ptrNext->data) == processID) {
                struct PCM *pcmDeletePtr = ptrNext->data;
                ptr->next = ptrNext->next;

                if(ptr->next == NULL){
                    pointer->tail = ptr;
                }
                pointer->numberOfProcess--;
                pointer->totalOfCycles = pcm_getNumCycles(pcmDeletePtr);
                pointer->totalOfMemory = pcm_getMemSize(pcmDeletePtr);

                delete_PCM(pcmDeletePtr);
                pcmDeletePtr = NULL;
                return 1;

            } else if (pcm_getPID(ptr->data) > processID){
                return 0;
            }
        }
    }
    return 0;

}
//Prints the data of the process
void dataTable_pPrint(struct dataTable *pointer){
    if (!pointer) {
        return;
    }
    struct Node *ptr;
    for(ptr = pointer->head; ptr != NULL; ptr = ptr->next) {
        print_PCM(ptr->data);
    }

}
//Print Statistics
void dataTable_stats(struct dataTable *pointer) {
    if (!pointer) {
        return;
    }
    printf("Number of Process = %d, Average Number of CPU Cycles = %d, average Memory Size = %d\n", pointer->numberOfProcess, pointer->totalOfCycles, pointer->totalOfMemory);
}

void dataTable_print(struct dataTable *pointer){
    if (!pointer) {
        return;
    }
    dataTable_stats(pointer);
    dataTable_pPrint(pointer);
}

void printStatsCSVFormant (struct dataTable *pointer){
    printf("%d, %d, %d\n", pointer->numberOfProcess, pointer->totalOfCycles/pointer->numberOfProcess, pointer->totalOfMemory/pointer->numberOfProcess);
}

void printPCSVFormat (struct dataTable *pointer) {
    if (!pointer) {
        return;
    }
    struct Node *ptr;
    for(ptr = pointer->head; ptr != NULL; ptr = ptr->next) {
        pcm_printCSV(ptr->data);
    }

}

void printCSVFormat(struct dataTable *pointer){
    if (!pointer) {
        return;
    }
    printStatsCSVFormant(pointer);
    printPCSVFormat(pointer);
}



int main () {
    int k;
    printf("Enter the number of process k: ");
    scanf("%d", &k);
    struct dataTable *ptr = newDataTable(k);
    dataTable_print(ptr);
    printCSVFormat(ptr);
    delete_dataTable(ptr);
    return 0;

}
