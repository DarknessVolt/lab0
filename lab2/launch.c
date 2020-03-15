#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

char** prepArgv(int argc, char** argv)
{
    char* argv2[argc];
    int i;

    for(i = 1; i < argc; i++)
    {
        strcpy(argv2[i-1], argv[i]);
    }
    argv2[argc-1] = (char*)0;
    
    return argv2;
}

int forkAndLaunch(int argc, char** argv, pid_t pid)
{
    if(pid == 0)
    {
        //child process
        
        execve(argv[1], prepArgv(argc, argv), NULL);

        printf("EXEC ERROR\n");
    }
    else if(pid < 0)
    {
        //error
        printf("FORKING ERROR\n");
    }
    else
    {
        //parent process

        int status;

        printf("%s: $$ = %d", argv[1], pid);

        waitpid(pid, &status, 0);

        printf("%s: $? = %d", argv[1], status);
        
    }
}

int main(int argc, char** argv)
{
    if(argc <= 2)
    {
        printf("INSUFFICIENT ARGUMENTS\n");
        return 1;
    }
    pid_t pid = fork();

    forkAndLaunch(argc, argv, pid);
    
    return 0;
}