#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>


int main () {
	//getting and storing the process id in a variable
	int pid_process = getpid();
	//getting and storing the process id of the parent in a variable
	int pid_parent = getppid();
	//Creating file for logs
	char *path = "logs.txt";
	FILE *fp = fopen(path, "a");
	//Taking user input for the number of cycles to run for the for loop
	int cycles;
	printf("Enter a number from [1 - 5] to for the number of cylces to run>>> ");
	scanf("%d", &cycles);
	rewind(fp);
	//Storing the operations on the integer of the process and its parent
	int sum = pid_process + pid_parent;
	int difference =  pid_process - pid_parent;
	int product =  pid_process * pid_parent;
	int quotient = pid_process/pid_parent;
	for(int i = 1; i <= cycles; i++) {
		pid_t process_id = fork();
		if(process_id == 0) {
			//Prints when child process runs
			printf("This is the CHILD process id>>>%d\n", pid_process);
			exit(0);
		} else {
			//Prints when the parent process runs
			printf("This is the PARENT process id>>>%d\n", pid_parent);
			printf("Wait for the CHILD process to finish!!!\n");
			wait(NULL);
			printf("The CHILD process has finished.\n");
		}
		printf("Open logs.txt to see the math operations done with the process run\n");
		fprintf(fp, "The sum total of the process and its parent process>>>%d\n", sum);
		fprintf(fp, "The difference of the process and its parent process>>>%d\n", difference);
		fprintf(fp, "The product of the process and its parent process>>>%d\n", product);
		fprintf(fp, "The quotient total of the process and its parent process>>>%d\n", quotient);
	}
	fprintf(fp, "\t<<<<<<<<<<<<<<<New logs>>>>>>>>>>>>>>>>>\n");
	fclose(fp);
	return 0;
}

