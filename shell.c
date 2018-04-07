//Major Project 1
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<cstring>

int main(int argc char* argv[])
{
  int i;
  int clength;
  int currentArg;
  char* arg;
  pid_t pid;
  
  //cycle through command-line args
  for(i = 0; i < argc; ++i)
  { 
    clength = strlen(argv[i]);
    //if ';' follows command, fork the process    
    if(argv[i][clength] == ';')
    {
      pid = fork();
      if(pid == -1)
      {
        printf("%s", "Error: pid = -1");
        exit(1);
      }
      printf("%s %d", "My pid = ", getpid());
      arg = argv[argc]
      exec(arg);
    }
    //if ';' does not follow command, run new image
    else
    {
      char* path = "/bin/";
      strcat(path, argv[argc]);
      execv(path, argv[]);
      printf("Something went wrong with execv() command");
    }
  }
  return 0;
}
