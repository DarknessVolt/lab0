#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <sys/mman.h>


#define SEM_CHOPSTICKS "/actuallyFork"

int RAND_UPPER = 1000000;

int cycles = 0;
int loop = 1;

int seats;
int philNum;
int numOfForks;

void sighandler(int sig)
{
    loop = 0;

    fprintf(stderr, "Philosopher %d completed %d cycles.", chopstick[i], cycles);
}


int rand_time()
{
    srand(time(NULL));
    int rand_val = rand() % RAND_UPPER + 1;
    return rand_val;
}

int eat(phil_num)
{
    printf("Philosopher %d is eating.", phil_num);

    //consume random amount of time
    usleep(rand_time(phil_num));
}

int think(int phil_num)
{
    printf("Philosopher %d is thinking.", phil_num);
    
    //consume random amount of time
    usleep(rand_time(phil_num));
}

int main(int argc, char** argv)
{
    int i;

    //process args
    sscanf(argv[1], "%d", seats);
    sscanf(argv[2], "%d", philNum);
    numOfForks = seats-1;

    //initialize shared memory
    int fd = shm_open(SEM_CHOPSTICKS, O_RDWR | O_CREAT | O_EXCL, 0664);
    if(fd == EEXIST)
    {
        PERROR(NULL);
        fd = shm_open(SEM_CHOPSTICKS);
    }

    ftruncate(fd, seats*sizeof(sem_t));

    sem_t forks = (sem_t)mmap(NULL, numOfForks*sizeof(sem_t), PROT_EXEC | PROT_WRITE, MAP_SHARED, fd, 0);

    if(forks == MAP_FAILED)
    {
        fprintf(stderr, "Map failed");
        return 1;
    }

    for(i = 0; i < numOfForks; i++)
    {
        sem_init(forks[i], 0666, 0);
    }
    
    
    
    signal(SIGTERM, sighandler);

    

    int cycles = 0;

    do
    {
        sem_wait(forks[philNum]);
        sem_wait(fork[(philNum+1) % numOfForks]);

        //use eat
        eat(i);

        sem_post(forks[philNum]);
        sem_post(fork[(philNum+1) % numOfForks]);

        //use think
        think(i);

        cycles++;

    }while(loop);

    
    sem_close();
    
    for(i = 0; i < numOfForks; i++)
    {
        sem_destroy(fork[i]);
    }
    return 1;
}