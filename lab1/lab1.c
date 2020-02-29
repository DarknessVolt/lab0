#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/times.h>

struct tms timeTracker;

int reportProcess(pid_t pid)
{
    if(pid == 0)
    {
        int i;
        //child process
        printf("PPID: %d, PID: %d\n", getppid(), getpid());
        exit(0);
    }
    else if(pid == -1)
    {
        //forkerror
        printf("FETUS WAS YEETUS");
    }
    else
    {
        //parent process
        int status;
        pid_t child_status;
        
        

        child_status = wait(&status);
        printf("PPID: %d, PID: %d, CPID: %d, RETVAL: %d\n", getppid(), getpid(), pid, status);

        times(&timeTracker);
        printf("USER: %d, SYS: %d\nCUSER: %d CSYS: %d\n",timeTracker.tms_utime, timeTracker.tms_stime, timeTracker.tms_cutime, timeTracker.tms_cstime);


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