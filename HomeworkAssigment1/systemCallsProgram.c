#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>


int main () {
	//getting and storing the process id in a variable
	int pid_process =getpid();
	//getting and storing the process id of the parent in a variable
	int pid_parent =getppid();

	printf("process id is: %d\n", pid_process);
	printf("process id is: %d\n", pid_parent);
	
	//Taking user input for the number of cycles to run for the for loop
	int cycles;
	printf("Enter a number from [1 - 5] to for the number of cylces to run>>> ");
	scanf("%d", &cycles);

	for(int i = 1; i <= cycles; i++) {
		int sum = pid_process + pid_parent;
		printf("The sum total of the process and its parent process>>>%d\n", sum);

		pid_t pid = fork();
		if(pid == 0) {
			printf("This is the child process id>>>%d\n", getpid());
			exit(0);
		} else {
			printf("This is the parent process id>>>%d\n", getppid());
			printf("Wait for the cild process to finish!!!\n");
			wait(0);
			printf("The child process finished.\n");
		}
	}
	return 0;
}

