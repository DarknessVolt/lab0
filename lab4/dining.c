#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <signal.h>


#define SEM_CHOPSTICK1 "/chopstick"

int RAND_UPPER = 1000000;

int cycles = 0;


void sighandler(int sig)
{


    
}


int rand_time(int phil_num)
{
    srand(time(NULL));
    int rand_val = rand() % RAND_UPPER + 1;
    return rand_val;
}

int eat(phil_num)
{
    printf("Philosopher %d is eating.", phil_num);
    usleep(rand_time(phil_num));
}

int think(int phil_num)
{
    printf("Philosopher %d is thinking.", phil_num);
    usleep(rand_time(phil_num));
}

int main(int argc, char** argv)
{

    int chopstick[argv[1] - 1];
    signal(SIGTERM, sighandler);

    if(sem_open(SEM_CHOPSTICK, O_CREAT|O_EXCL, 0666, 1) == SEM_FAILED)
    {
        perror(NULL);
        
    }

    int cycles = 0;
    int loop = 1;

    do
    {
        wait(chopstick[i]);
        wait(chopstick[(i+1)%5]);

        eat(i);

        signal(chopstick[i]);
        signal(chopstick[(i+1)%5]);

        think(i);

        cycles++;
    }while(loop);

    fprintf(stderr, "Philosopher %d completed %d cycles.", chopstick[i], cycles);
    sem_close()
    
    return 1;
}