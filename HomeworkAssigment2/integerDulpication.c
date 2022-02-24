#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<unistd.h>


int main () {
	char *path = "IntegerLogs.txt";
	FILE *fp;
	int number;
	
	for(int i = 0; i < 200; i++) {
		for(int j =1; j < 4; j++) {
			fp = fopen("IntegerLogs.txt", "r");
			fscanf(fp, "%d", &number);
			printf("number = %d Processid=P%d\n", number, j);
			fclose(fp);
			number++;
			fp = fopen("IntegerLogs.txt", "w");
			fprintf(fp, "%d", number);
			fclose(fp);
		}
	}
	return 0;
}
