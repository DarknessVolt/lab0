#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>


int reportProcess(pid_t pid)
{
    if(pid == 0)
    {
        //child process
    }
    else if(pid == -1)
    {
        //forkerror
    }
    else
    {
        //parent process
    }
    
}

int printTime(int i)
{
    int currTime = time(NULL);

    if(i == 0)
    {
        printf("%s", "START: ");
    }
    else
    {
        printf("%s", "STOP: ");
    }

    printf("%d\n", currTime);
    
}

int main()
{
    pid_t pid;
    printTime(0);
    
    pid = fork();
    reportProcess(pid);
    

    printTime(1);
}