#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
 

void process() {
    char *path = "IngterFile.txt"; //Creating a File
    FILE *fp = fopen(path, "r"); //Open the File 
    int num;
    pid_t pid; // Get Process Id
    fscanf (fp, "%d", &num); //Read Number
    fclose (fp); //Close file
    if ((pid = getpid()) < 0) { //Get Process ID
       printf("unable to get pid");
    } else {
       printf("N: %d Process ID: %d\n",num,pid);
    }
    fp = fopen(path, "w");
    num++;
    // putw(num,fp);
    fprintf(fp, "%d", num);
    fflush(fp);
    fclose(fp);
}

int main(void) {
     if (fork() == 0) {
       printf("Starting Process A\n");
       process();
   }
   if (fork() == 0) {
       printf("Starting Process B\n");
       process();
   }
   if (fork() == 0){
       printf("Starting Process C\n");
       process();
   }
   return 0;
}

    
