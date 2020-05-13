#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <aio.h>
#include <string.h>

#define RANGE 101

int generate_rand_int(int* scalar)
{
    int randPositive = rand()%RANGE;
    int randNegative = -1 * rand()%RANGE;
    *scalar = randPositive + randNegative;
}

void matrix_add(char* block, int size)
{
    int scalar;
    int i;

    generate_rand_int(&scalar);

    for(i = 0; i < size * size; i++)
    {
            block[i] += scalar;
    }
}

void block_read(int** block, int size, int scalar)
{
    int i, j;

    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {

        }
    }
}

void block_write(int** block, int size, int scalar)
{
    int i, j;
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {

        }
    }
}
int main(int argc, char** argv)
{
    //declarations
    int size, blocks, block_size;
    int i;
    time_t st_time, en_time;

    sscanf(argv[1], "%d", &size);
    sscanf(argv[2], "%d", &blocks);

    block_size = size/blocks;

    //block setup
    char* prevBlock;
    char* currBlock;
    char* nextBlock;

    prevBlock = malloc(block_size * block_size * sizeof(int*));
	/*for(i = 0; i < block_size; i++)
    {
		prevBlock[i] = malloc(block_size * sizeof(int));
    }*/

    currBlock = malloc(block_size * block_size * sizeof(int*));
	/*for(i = 0; i < block_size; i++)
    {
		currBlock[i] = malloc(block_size * sizeof(int));
    }*/

    nextBlock = malloc(block_size * block_size * sizeof(int*));
	/*for(i = 0; i < block_size; i++)
    {
		nextBlock[i] = malloc(block_size * sizeof(int));
    }*/

    struct aiocb* aiocb_read;
    struct aiocb* aiocb_write;

    memset(aiocb_read, 0, sizeof(struct aiocb));
    memset(aiocb_write, 0, sizeof(struct aiocb));

    aiocb_write->aio_fildes = 0;
    aiocb_write->aio_offset = 0;
    aiocb_write->aio_buf = prevBlock;
    aiocb_write->aio_nbytes = block_size * block_size;
    aiocb_write->aio_reqprio = 0;
    
    aiocb_write->aio_fildes = 1;
    aiocb_write->aio_offset = 0;
    aiocb_write->aio_buf = prevBlock;
    aiocb_write->aio_nbytes = block_size * block_size;
    aiocb_write->aio_reqprio = 0;
    //get start time
    time(&st_time);

    for(i = 0; i < block_size * block_size - 2; i++)
    {
        //read request
        aio_read(aiocb_read);

        matrix_add(currBlock, block_size);

        //write request and return
        aio_write(aiocb_write);
        aio_return(aiocb_write);
        memcpy(&prevBlock[i], &currBlock[i], block_size);

        //read return
        aio_return(aiocb_read);
        memcpy(&currBlock[i], &nextBlock[i], block_size);
    }

    //get end time
    time(&en_time);

    printf("Allotted time: %d\n", en_time - st_time);

}