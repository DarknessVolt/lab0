#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <unistd.h>

pid_t child1 = 0;
pid_t child2 = 0;
char* pathToMole;

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
        if(child1 != 0)\
        {
            kill(child1, SIGTERM);
            child1 = 0;
        }
        
        //randomly create mole1 or mole 2
        createChild();

    }
    else if(sig == 12)//sigusr2
    {
        //kill process #2
        if(child2 != 0)
        {
            kill(child2, SIGTERM);
            child2 = 0;
        }
        //randomly create mole1 or mole 2
        createChild();
    }

    //reset signal
    signal(sig, sigHandler);
}

int childrng(int* childnum)
{
    //randomly determine the child process number

    if(child1 == 0 && child2 == 0)
    {
        srand(time(NULL));
        *childnum = rand() % 2 + 1;
    }
    else if(child1 == 0)
    {
        *childnum = 1;
    }
    else
    {
        *childnum = 2;
    }
}

int moleForkandExec(int childnum, pid_t* pid)
{
    //fork a new process

    *pid = fork();

    if(pid == 0)
    {
        char** argv;
        //child process
        if(childnum == 1)
        {
            char* argv = {"mole1"};
        }
        else
        {
            char* argv = {"mole2"};
        }
        

        //exec the program mole, argv[0] == to mole1 or mole2
        execve(pathToMole, argv, NULL);
    }
    else if(pid < 0)
    {
        //forking error
        return -1;
    }
    else
    {
        //parent process
        return 0;
    }
    //exec failed
    return -2;
}

void createChild()
{
    //randomly determine the child process number
    int childnum;
    childrng(&childnum);

    
    //fork a new process
    if(childnum == 1)
    {
        moleForkandExec(childnum, &child1);
    }
    else
    {
        moleForkandExec(childnum, &child2);
    }
    
}

void daemonFun()
{
    //RELEASE THE D(A)EMON
    while(1)
    {
        pause();
    }
}


int main(int argc, char** argv)
{
    //get current working directory and path to moles
    pathToMole = malloc(500*sizeof(char));
    getcwd(pathToMole, 500);
    strcat(pathToMole, "/moles");
    //printf("yeet\n");
    //set creation mask to 0
    umask(0);

    //fork and have parent exit
    pid_t pid = fork();
    struct rlimit rl;

    //printf("yeet\n");
    
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

        for(i = 0; i < rl.rlim_max; i++)
        {
            close(i);
        }
        //reopen the standard file descriptors to map to /dev/null
        fd0 = open("/dev/null", O_RDWR);
        fd1 = dup(0);
        fd2 = dup(0);
        
        //register signal handlers
        signal(SIGTERM, sigHandler);
        signal(10, sigHandler);
        signal(12, sigHandler);
        
        //RELEASE THE D(A)EMON
        daemonFun();

    }
    else if(pid == 0)
    {
        //fork error
        printf("FETUS WAS YEETUS");
    }
    else
    {
        //parent process // parent exits // child orphaned
        printf("Daemon PID: %d\n", pid);
    }
     
    return 0;
}