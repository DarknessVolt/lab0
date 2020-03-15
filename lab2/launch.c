#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int forkAndLaunch(int argc, char** argv, pid_t pid)
{
    if(pid == 0)
    {
        //child process
        execve()
    }
    else if(pid < 0)
    {
        
        //error
        printf("FORKING ERROR")
    }
    else
    {
        //parent process
        printf("%s: %d", argv[1], pid);
        
    }
}

int main(int argc, char** argv)
{
    pid_t pid;
    forkAndLaunch(argc, argv, pid);
}