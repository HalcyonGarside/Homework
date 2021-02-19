
//std
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

//local
//#include <process_helper.h> 

/*
 * Calls the system call specified by arg and returns 
 * the child process's status after it's run.
*/
int runChildProc(char* arg)
{
	int status;
	int proc = fork();
	if(proc == 0)
	{
		char* arg0 = strtok(arg, " \n");
		char* file = (char*)malloc(20 * sizeof(char));
		sprintf(file, "/bin/%s", arg0);

		int i = 1;
		char* args[11];
		args[0] = arg0;
		while(arg0 != NULL && i < 10)
		{
			arg0 = strtok(NULL, " \n");
			printf("%s ", arg0);
			args[i] = arg0;
			i++;
		}
		printf("\n");

		int error = execvp(file, args); 

		if(error == -1)
		{
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		wait(&status);
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
		/*
		int cmdptr = 0;
		int argptr = 0;
		while(cmdptr < strlen(command) && command[cmdptr] != ' ' && command[cmdptr] != '\n')
		{
			arg[argptr] = command[cmdptr];
			cmdptr++;
			argptr++;
		}
		arg[argptr] = '\0';
		argptr = 0;
		*/
		arg = strtok(command, " \n");

		//printf("%s\n", arg); //DEBUG
		

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
			/*
			cmdptr++;
			while(cmdptr < strlen(command) && command[cmdptr] != ' ' && command[cmdptr] != '\n')
			{
				arg[argptr] = command[cmdptr];
				cmdptr++;
				argptr++;
			}
			arg[argptr] = '\0';
			argptr = 0;
			*/

			arg = strtok(NULL, " \n");
			int error = chdir(arg);

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
