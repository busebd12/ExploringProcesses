#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>

int main()
{
	FILE *fileToBeRead;
	char fileContents;
	char *line=NULL;
	size_t length=0;
	int int1, int2;
	int1=int2=0;
	

	//pid_t is a signed integer type which is capable of representing a process ID 
	pid_t childPid;

	//The "+r " means the file is open for reading and writing, start at beginning
	fileToBeRead=fopen("./fileToBeRead.txt", "r+");

	if(fileToBeRead==NULL)
	{
		printf("Cannot open file.");
		exit(1);
	}

	//creating a new process
	//fork represents the parent process
	childPid=fork();

	
	//checks for fork failure
	if(childPid < 0)
	{
		printf("fork failed...");
		exit(1);
	}

	//Do child process action
	if(childPid==0)
	{	
		//exit(1);
		pid_t id=getpid();
		while(getline(&line,&length,fileToBeRead)!=-1)
		{
			int1++;
			printf("Child: ");
			printf("ID is: %d ", id);
			printf("%s",line);
		}
		fclose(fileToBeRead);
		printf("\nChild number of lines read: %d\n",int1);
		exit(1);
	}

	//Do the parent process action
	else
	{
		//int returnStatus;    
    		//waitpid(childPid, &returnStatus, 0);
		printf("Parent: ");
		pid_t id=getpid();
		while(getline(&line,&length,fileToBeRead)!=-1)
		{
			int2++;
			printf("ID is: %d ", id);
			printf("%s",line);
		}
		fclose(fileToBeRead);
		printf("\nParent number of lines read: %d\n",int2);
		exit(1);
	}
	
}