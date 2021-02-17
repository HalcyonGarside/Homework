
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
 * Calls the system call specified by call and returns 
 * that process's pid.
*/

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
		scanf("%s", command);
		
		//Parse command
		int cmdptr = 0;
		int argptr = 0;
		while(cmdptr < strlen(command) && command[cmdptr] != ' ')
		{
			arg[argptr] = command[cmdptr];
			cmdptr++;
			argptr++;
		}
		arg[argptr] = '\0';
		argptr = 0;

		printf("%s\n", arg); //DEBUG


		//Begin command definitions...
		//pid
		if(strcmp(arg, "pid") == 0)
		{
			printf("%d\n", getpid());
		}
		
		//ppid
		else if(strcmp(arg, "ppid") == 0)
		{
			printf("%d\n", getppid());
		}
		
		//cd <dir>
		else if(strcmp(arg, "cd") == 0)
		{
			cmdptr++;
			while(cmdptr < strlen(command) && command[cmdptr] != ' ')
			{
				arg[argptr] = command[cmdptr];
				cmdptr++;
				argptr++;
			}
			arg[argptr] = '\0';
			argptr = 0;

			printf("%s\n", arg); //DEBUG

			int error = chdir(arg);

			if(error == -1)
			{
				printf("Could not find path %s\n", arg);
			}
		}
		
		//pwd
		else if(strcmp(arg, "pwd") == 0)
		{
			pid_t proc = fork();
			int status;

			if(proc == 0)
			{
				execl("/bin/pwd", "pwd", (char*)NULL);
			}
			else
			{
				waitpid(proc, &status, 0);
			}
		}
		
		//exit
		else if(strcmp(arg, "exit") == 0)
		{
			break;
		}
		
		//Called if no other case is taken
		else
		{
			printf("Cannot exec %s: No such file or directory\n", arg);
		}

	}

	return 0;
}
