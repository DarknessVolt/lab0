#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <unistd.h>

pid_t child1 = 0;
pid_t child2 = 0;
char* cwd;

void createChild();

void sigHandler(int sig)
{
    if(sig == SIGTERM)
    {
        kill(0, sig);
    }
    else if(sig == 10)//sigusr1
    {
        
        //kill process #
        if(child1 != 0)
            kill(child1, SIGTERM);
        //randomly create mole1 or mole 2
        createChild();

    }
    else if(sig == 12)//sigusr2
    {
        //kill process #2
        if(child2 != 0)
            kill(child2, SIGTERM);
        //randomly create mole1 or mole 2
        createChild();
    }

    //reset signal
    signal(sig, sigHandler);
}

int childrng(int* childnum)
{
    if(child1 == 0 && child2 == 0)
    {
        srand(time(NULL));
        childNum = rand() % 2 + 1;
    }
    else if(child1 == 0)
    {
        childnum = 1;
    }
    else
    {
        childnum = 2;
    }
}

int createChild()
{
    
    //fork a new process
    *pid = fork();
    if(pid == 0)
    {
        //child process
        //randomly determine the child process number
        int childnum;
        childrng(*childnum);

        if(childnum == 1)
        {

        }
        else
        {
        
        }

        //exec the program mole, arg[0] == to mole1 or mole2
        execve()
    }
    else if(pid < 0)
    {
        //forking error
        return -1;
    }
    else
    {
        //parent process
        return pid;
    }
    
}

void daemon()
{
    while(1)
    {
        pause();
    }
}

int main(int argc, char** argv)
{
    //get current working directory
    getcwd(cwd, 500);

    //set creation mask to 0
    umask(0);

    //fork and have parent exit
    pid_t pid = fork();
    struct rlimit rl;

    if(pid == 0)
    {
        //child process aka daemon
        int i;
        int fd0;
        int fd1;
        int fd2;
        pid_t sessionID;
        char* newDir = "/";

        //create a new session //create a new process group
        sessionID = setsid();

        //change directory to "/"
        chdir(newDir);
        //close all unneeded file descriptors
        getrlimit(RLIMIT_NOFILE, &rl);

        for(i = 0; i < rl.rlim_max)
        {
            close(i);
        }
        //reopen the standard file descriptors to map to /dev/null
        fd0 = open("/dev/null", O_RDRW);
        fd1 = dup(0);
        fd2 = dup(0);
        
        //register signal handlers
        signal(SIGTERM, sigHandler);
        signal(10, sigHandler);
        signal(12, sigHandler);
        
        daemon();

    }
    else if(pid == 0)
    {
        //fork error
        printf("FETUS WAS YEETUS");
    }
    else
    {
        //parent process // parent exits // child orphaned
        printf("Daemon PID: %d", pid);
    }
     
    return 0;
}