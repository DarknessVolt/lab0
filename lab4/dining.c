#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <signal.h>
#include <sys/mman.h>


#define SEM_CHOPSTICKS "/actuallyForks1"

int RAND_UPPER = 1000000;

int cycles = 0;
int loop = 1;

int seats = 0;
int philNum = 0;
int numOfChopsticks;

void sighandler(int sig)
{
    loop = 0;

    fprintf(stderr, "Philosopher %d completed %d cycles.\n", philNum, cycles);
}


int rand_time()
{
    srand(time(NULL) + philNum);
    int rand_val = rand() % RAND_UPPER + 1;
    return rand_val;
}

int eat()
{
    printf("Philosopher %d is eating.\n", philNum);

    //consume random amount of time
    usleep(rand_time());
}

int think()
{
    printf("Philosopher %d is thinking.\n", philNum);
    
    //consume random amount of time
    usleep(rand_time());
}

int main(int argc, char** argv)
{
    int i;

    //process args
    sscanf(argv[1], "%d", &seats);
    sscanf(argv[2], "%d", &philNum);

    numOfChopsticks = seats;

    int fd = shm_open(SEM_CHOPSTICKS, O_RDWR | O_CREAT, 0664);

    if(fd == -1)
    {
        printf("shm_open Failed");
        return 1;
    }
    ftruncate(fd, sizeof(sem_t));

    sem_t* chopsticks = mmap(NULL, seats*sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    

    //sem_t* chopstick_address = (sem_t*)calloc(numOfChopsticks, sizeof(sem_t));
    //
    //printf("yeet1\n");
    /*if(forks == MAP_FAILED)
    {
        fprintf(stderr, "Map failed");
        return 1;
    }*/


    for(i = 0; i < seats; i++)
    {
        
        //&chopstick_address[i] = chopsticks + i;
        //printf("yeet%d %d\n", i, chopsticks[i]);
        sem_init(&chopsticks[i], 0666, 1);
    }
    
    printf("yeetsuccess\n");
    
    signal(SIGTERM, sighandler);

    
    cycles = 0;

    while(loop)
    {
        //printf("Loop %d, %d", );
        
        sem_wait(&chopsticks[philNum]);
        sem_wait(&chopsticks[(philNum+1) % numOfChopsticks]);
        
        //use eat
        eat(i);

        sem_post(&chopsticks[philNum]);
        sem_post(&chopsticks[(philNum+1) % numOfChopsticks]);
        //use think
        think(i);

        cycles++;

    }
    
    
    for(i = 0; i < seats; i++)
    {
        sem_destroy(&chopsticks[i]);
    }
    shm_unlink(SEM_CHOPSTICKS);
    return 0;
}