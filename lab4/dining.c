#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <time.h>

RAND_UPPER = 1000000;

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
    
}