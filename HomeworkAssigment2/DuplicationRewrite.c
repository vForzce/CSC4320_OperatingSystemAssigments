#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

const char* path = "rewrite.txt";
sem_t *sem_cons;

int main (int argc, char *argv[]) {
    sem_unlink("/rewritesemaphore");
    sem_cons = sem_open("/rewritesempahore", O_CREAT, S_IRUSR | S_IWUSR, 1);
    if(fork() == 0){
        printf("Starting process B\n");
        if(fork() == 0){
            printf("Staring process A\n");
        }
    }
    if(sem_cons = SEM_FAILED){
        perror("sem_open/rewritesemphore");
        exit(EXIT_FAILURE);
    }

    pid_t pid = getpid();

    for(int i = 0; i < 200; i++) {
        sem_wait(sem_cons);
        FILE* fp = fopen(path, "r"); //Open the File 
        int num;
        fscanf (fp, "%d", &num); //Read Number
        rewind(fp);
        fclose (fp); 
        printf("N: %d Process ID: %d\n", num, pid);
        sem_post(sem_cons);
        num++;
        fp = fopen(path, "w");
        fprintf(fp, "%d", num);
        rewind(fp);
        fclose(fp);
        sem_close(sem_cons);
    }


}