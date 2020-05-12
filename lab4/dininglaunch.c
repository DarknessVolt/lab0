#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>

#define SEM_CHOPSTICKS "/actuallyForks1"

int loop = 1;
void sighandler(int sig)
{
    //send signal to all children
    if(sig == SIGTERM)
    {
        sigset(SIGTERM, SIG_IGN);
        kill(0, sig);
        loop = 0;
    }
    
}

int fork_and_exec(int seats, int philNum, pid_t* pid)
{
    pid[philNum] = fork();


    if(pid[philNum] == 0)
    {
        //child process
        char buffer[3][15];

        //setup argv
        sprintf(buffer[0], "/dining-p-%d", philNum);
        sprintf(buffer[1], "%d", seats);
        sprintf(buffer[2], "%d", philNum);
        
        char* argv[4] = {buffer[0], buffer[1], buffer[2], NULL};

        execv("./dining-p", argv);

        printf("Exec Failed\n");
    }
    else if(pid[philNum] < 0)
    {
        printf("Fork failed");
        return -1;
    }
    else
    {
        return 0;
    }
    return -1;
}

void make_philosophers(int seats, pid_t* pid)
{
    
    int i;
    for(i = 0; i < seats; i++)
    {
        if(fork_and_exec(seats, i, pid) == -1)
        {
            printf("Forking and exec failure");
            
            break;
        }
    }
}

int main(int argc, char** argv)
{
    int seats, status, i;

    sscanf(argv[1], "%d", &seats);
    
    pid_t pid[seats];
    pid_t wpid;

    //create new process group
    setpgid(0,0);

    //allocate semaphores
    int fd = shm_open(SEM_CHOPSTICKS, O_RDWR | O_CREAT, 0664);

    if(fd == -1)
    {
        printf("shm_open Failed");
        return 1;
    }
    ftruncate(fd, sizeof(sem_t));

    sem_t* chopsticks = mmap(NULL, seats*sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    for(i = 0; i < seats; i++)
    {
        sem_init(&chopsticks[i], 0666, 1);
    }

    //allocate signal handler
    signal(SIGTERM, sighandler);
    //signal(SIGCHLD, sighandler);
    //create seats
    make_philosophers(seats, pid);

    //wait for sigterm
    pause();
    //while(loop);

    //wait for children
    while(wait(0) >= 0);
    //cleanup
    shm_unlink(SEM_CHOPSTICKS);

    for(i = 0; i < seats; i++)
    {
        sem_destroy(&chopsticks[i]);
    }
    //return success
    return 0;
}