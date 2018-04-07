#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include<sys/wait.h>

//clears the screen
void cls() 
{
	printf("\033[H\033[J");
}

void startShell()
{
	char response;
	cls();
	printf("\n\n===========================================");
	printf("\n\n            ----WELCOME----");
	printf("\n\n===========================================");
	char* user = getenv("USER");
	printf("\n\nusername: %s", user);
	//sleep(2);
	do
	{	
		printf("\n\nEnter 'c' to continue: ");
		scanf("%c%*c", &response);

	} while(response != 'c');
	cls();
}

int main(int argc, char **argv)
{
	pid_t pid;
	int status;
	
	int i, x, temp, counter, arg;
	long size;
	char input[512];
	char *buffer, *cwd;
	char *command, **cmds, *argument, **args;
	char *endCmnd;
	

	startShell();	

	if(argc == 1)
	{
		while(1)
		{
			i       = 0;
			x       = 0;
			temp    = 0;
			counter = 0;
			printf("> ");
			fgets(input, 512, stdin);
			int length;
			length = strlen(input);	
			printf("\ninput = %s", input); 
			printf("\nlength = %d", length);
			printf("\n\nprinting elements of 'input': ");
			for(i = 0; i < length; ++i)
			{
				printf("\ninput[%d] = %c", i, input[i]);	
			}
			if(strncmp(input, ";", length-2)) 
			//if(input[length-2] != ';')
			{				
				counter++;
				printf("\ninput[length-2] = %c", input[length-2]);
				printf("\ncounter = %d", counter);
			}
			printf("\n\nprinting elements of 'input': ");
			for(i = 0; i < length; ++i)
			{
				printf("\ninput[%d] = %c", i, input[i]);	
			}
			printf("\njust before for loop");
			printf("\nlength = %d", length);
			for(i = 0; i < length - 1; ++i)
			{
				printf("\ni = %d", i);
				if(input[i] == ';')
				{
					printf("\ncounter = %d", counter);
					counter++;
				}
			}
			cmds = malloc(counter*sizeof(*cmds));
			printf("\ncounter * sizeof(*cmds) = %d", counter * sizeof(*cmds));
			//SEGMENTATION FAULT HAPPENS HERE
			//command = strtok_r(input, ";", &endCmnd);
			printf("\nmade it here");
			while(command != NULL)
			{
				pid = fork();
				char *endArg;
				cmds[i] = malloc((strlen(command)+1)*sizeof(char));
				strcpy(cmds[i], command);
				i++;
				arg = 1;
				for(x = 0; x < strlen(cmds[i]) + 1; x++)
				{
					if(cmds[i][x] == ' ')
					{
						if(x == 0)
						{}
						else
							arg++;
					}
				}
					args = malloc(arg*sizeof(char*));
					argument = strtok_r(command, " ", &endArg);
					while(argument != NULL)
					{
						args[temp] = malloc((strlen(argument) + 1)*sizeof(char));
						strcpy(args[temp], argument);
						temp++;
						argument = strtok_r(command, " ", &endArg);
					}
				if(pid == 0)
				{
					for(i = 0; i < counter; i++)
					{
						if(strcmp(cmds[i], "pwd") == 0)
						{
							cwd = getcwd(buffer, 0);
							printf("%s", cwd);
						}
						else if(strcmp(cmds[i], "cd") == 0)
						{
							chdir(getenv("HOME"));
						}
						else if(strcmp(cmds[i], "cd") > 0)
						{
							chdir(args[1]);
						}
						else
						{
							execvp(args[0], args);
						}
					}
				}
				else if(pid > 0)
				{
					if(strcmp(cmds[i], "exit") == 0)
					{
						wait(0);
						exit(0);
					}
				}
				else
				{
					perror("Fork");
					exit(1);
				}
				command = strtok_r(input, ";", &endCmnd);
			}
		}
	}
	else if(argc > 1)
	{
		// Read from batch file
	}
	else
	{
		printf("Invalid, too many arguments");
		exit(0);
	}
	
	return 0;
}
