#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<semaphore.h>
#include <sys/stat.h>
#include <fcntl.h>

const char* path = "rewrite.txt";
sem_t *sem_read;
sem_t *sem_write;

int main (int argc, char *argv[]) {
    sem_unlink("/reader_sempahore");
    sem_unlink("/write_semphore");
    sem_read = sem_open("/reader_sempahore", O_CREAT, S_IRUSR, 1);
    sem_write = sem_open("/write_semaphore", O_CREAT, S_IWUSR, 0);
    if(fork() == 0){
        printf("Starting process B\n");
        if(fork() == 0){
            printf("Staring process A\n");
        }
    }
    if(sem_read = SEM_FAILED){
        perror("sem_open/reeader_semphore");
        exit(EXIT_FAILURE);
    }

    if(sem_write = SEM_FAILED){
        perror("sem_open/reeader_semphore");
        exit(EXIT_FAILURE);
    }

    pid_t pid = getpid();

    for(int i = 0; i < 200; i++) {
        sem_wait(sem_read);
        FILE* fp = fopen(path, "r"); //Open the File 
        int num;
        fscanf (fp, "%d", &num); //Read Number
        rewind(fp);
        fclose (fp); 
        sem_post(sem_read);
        printf("N: %d Process ID: %d\n", num, pid);
        num++;
        sem_close(sem_read);
        sem_wait(sem_write);
        fp = fopen(path, "w");
        fprintf(fp, "%d", num);
        rewind(fp);
        fclose(fp);
        sem_post(sem_write);
        sem_close(sem_write);
    }


}