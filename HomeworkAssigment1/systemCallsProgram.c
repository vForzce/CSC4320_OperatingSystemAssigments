#include<stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main () {
	//getting and storing the process id in a variable
	int pid_child =getpid();
	//getting and storing the process id of the parent in a variable
	int pid_parent =getppid();

	printf("process id is: %d/n", pid_child);
	printf("process id is: %d/n", pid_parent);
	return 0;
}

