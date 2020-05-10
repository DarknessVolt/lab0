#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/resource.h>
#include <unistd.h>

int main(int argc, char** argv)
{
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
        char** newDir = "/";

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

    }
    else if(pid == 0)
    {
        //fork error
        printf("FETUS WAS YEETUS");
    }
    else
    {
        //parent process // parent exits // child orphaned
    }
    return 0;
}