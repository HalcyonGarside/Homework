
//std
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

//local
//#include <process_helper.h> 

const char delim[4] = " \n";

/*
 * Calls the system call specified by arg and returns 
 * the child process's status after it's run.
*/
int runChildProc(char* cmd)
{
	int status;
	int proc = fork();
	if(proc == 0)
	{
		//Get the next token
		char* arg0 = strtok(NULL, delim);

		//Initialize while loop/args array
		int i = 1;
		char* args[11];
		args[0] = cmd;

		//Load args array with command line arguments
		while(arg0 != NULL && i < 10)
		{
			args[i] = arg0;
			i++;
			arg0 = strtok(NULL, delim);
		}
		
		//Run command with given arguments
		int error = execvp(cmd, args); 
		
		//If the command wasn't run, exit with failure
		if(error == -1)
		{
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		//Print child ID, command name
		printf("[%d] %s\n", proc, cmd);

		//Wait for the child process to end
		wait(&status);

		//Catch errors from child
		if(status == EXIT_FAILURE)
		{
			printf("Failed to execute\n");
		}
		else if(status != 0)
		{
			char* msg = (char*)malloc(50 * sizeof(char));
			sprintf(msg, "Cannot execute command %s", cmd);
			perror(msg);
		}


		//Print exit dialogue
		printf("[%d] %s Exit %d\n", proc, cmd, status);
	}

	return status;
}

int main(int argc, char* argv[])
{
	char* prompt = NULL;
	int i;

	//Check for prompt name argument
	for(i = 1; i < argc; i++)
	{
		//If the prompt flag is found and there's still an argument left
		if(strcmp(argv[i], "-p") == 0 && i + 1 < argc)
		{
			//Assign the name
			i++;
			prompt = argv[i];
			break;
		}
	}

	//If prompt flag is not found, default
	if(prompt == NULL)
		prompt = "308sh";
	
	//Create string for command input
	char* command = (char*)malloc(100 * sizeof(char));
	char* arg = (char*)malloc(50 * sizeof(char));

	//Main shell loop
	while(1)
	{
		//Print command line
		printf("%s> ", prompt);
		fgets(command, 50, stdin);
		
		//Parse command
		arg = strtok(command, delim);
		

		//Begin command definitions...
		//pid
		if(strcmp(arg, "pid") == 0)
		{
			printf("%d\n", getpid());
			continue;
		}
		
		//ppid
		else if(strcmp(arg, "ppid") == 0)
		{
			printf("%d\n", getppid());
			continue;
		}
		
		//cd <dir>
		else if(strcmp(arg, "cd") == 0)
		{
			arg = strtok(NULL, " \n");
			

			int error;
			if(arg != NULL)
				error = chdir(arg);
			else
				error = chdir(getenv("HOME"));

			if(error == -1)
			{
				printf("Could not find path %s\n", arg);
			}
			continue;
		}
		
		//pwd
		else if(strcmp(arg, "pwd") == 0)
		{
			getcwd(arg, 50);
			printf("%s\n", arg);
			continue;
		}
		
		//exit
		else if(strcmp(arg, "exit") == 0)
		{
			break;
		}
		
		//Called if no other case is taken
		else
		{
			runChildProc(command);
			//printf("Cannot exec %s: No such file or directory\n", arg);
			continue;
		}

	}

	return 0;
}
