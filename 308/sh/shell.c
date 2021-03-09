
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
char* prompt;

/*
 * Calls the system call specified by arg and returns 
 * the child process's status after it's run.
*/
int runChildProc(char* cmd, int bg)
{
	int status;

	//Get the next token
	char* arg0 = strtok(NULL, delim);

	//Initialize while loop/args array
	int i = 1, bgproc = 0;
	char* args[11];

	args[0] = cmd;

	//Load args array with command line arguments
	while(arg0 != NULL && i < 10)
	{
		args[i] = arg0;
		i++;
		arg0 = strtok(NULL, delim);
	}
	args[i] = NULL;

	//Fork into main process (id) and bg process (0)
	if(bg == 1)
	{
		bgproc = fork();
		if(bgproc != 0)
		{
			usleep(1000);
			return bgproc;
		}
	}

	int proc = fork();

	//If this process is going to execute the command
	if(proc == 0)
	{	
		//Run command with given arguments
		int error = execvp(cmd, args); 
		
		//If the command wasn't run, exit with failure
		if(error == -1)
		{
			char* errstr = (char*)malloc(50 * sizeof(char));
			sprintf(errstr, "\nCannot exec %s", cmd);
			perror(errstr);
			kill(getpid(), SIGTERM);
		}
	}

	//If this process is waiting for the command to finish executing
	else
	{
		printf("[%d] %s\n", proc, cmd);

		int err = waitpid(proc, &status, 0);

		printf("\n[%d] %s Exit (%d)\n", proc, cmd, status);

		if(bg > 0)
		{
			printf("%s> ", prompt);
			usleep(1000);
			kill(getpid(), SIGTERM);
		}
	}

	return status;
}

int main(int argc, char* argv[])
{
	prompt = NULL;
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
	int bg;
	//Main shell loop
	while(1)
	{
		bg = 0;
		//Print command line
		printf("%s> ", prompt);
		fgets(command, 50, stdin);

		if(command[strlen(command)-2] == '&')
		{
			bg = 1;
			command[strlen(command)-2] = '\0';
		}
			
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
			runChildProc(command, bg);
			continue;
		}

	}

	return 0;
}
