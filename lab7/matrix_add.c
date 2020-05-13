#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <aio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>

#define RANGE 101
#define WORD_SIZE 29
#define VALUE_OFFSET 24

int generate_rand_int(int* scalar)
{
    int randPositive = rand()%RANGE;
    int randNegative = -1 * rand()%RANGE;
    *scalar = randPositive + randNegative;
}

void matrix_add(char* block, int size, int scalar)
{
    int i;

    for(i = 0; i < size * size * WORD_SIZE; i += WORD_SIZE)
    {
        //prepare integer
        int valueatpos = 0;
        char stringInt[5];
        memcpy(stringInt, &block[i + VALUE_OFFSET], 4);
        stringInt[4] = '\0';
        sscanf(stringInt, "%d", &valueatpos);

        //printf("%d\n",valueatpos);

        //add scalar
        valueatpos += scalar;
        //printf("%d\n",valueatpos);

        //save in block
        sprintf(stringInt, "%4d ", valueatpos);
        //printf("%d %s %d\n", valueatpos, stringInt, scalar);
        memcpy(&block[i + VALUE_OFFSET], stringInt, 4);
    }
}
/*
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
}*/
int main(int argc, char** argv)
{
    //declarations
    int size, blocks, block_size;
    int scalar;
    int i;
    time_t st_time, en_time;

    sscanf(argv[1], "%d", &size);
    sscanf(argv[2], "%d", &blocks);

    block_size = size/blocks;

    srand(time(NULL));
    generate_rand_int(&scalar);

    //block setup
    char* prevBlock;
    char* currBlock;
    char* nextBlock;

    prevBlock = (char*)malloc(WORD_SIZE * block_size * block_size * sizeof(char*));
	/*for(i = 0; i < block_size; i++)
    {
		prevBlock[i] = malloc(block_size * sizeof(int));
    }*/

    currBlock = (char*)calloc(WORD_SIZE * block_size * block_size, sizeof(char));
	/*for(i = 0; i < block_size; i++)
    {
		currBlock[i] = malloc(block_size * sizeof(int));
    }*/

    nextBlock = (char*)calloc(WORD_SIZE * block_size * block_size, sizeof(char));
	/*for(i = 0; i < block_size; i++)
    {
		nextBlock[i] = malloc(block_size * sizeof(int));
    }*/

    struct aiocb* aiocb_read;
    struct aiocb* aiocb_write;

    aiocb_read = (struct aiocb*)calloc(1, sizeof(struct aiocb));
    aiocb_write = (struct aiocb*)calloc(1, sizeof(struct aiocb));

    memset(aiocb_read, 0, sizeof(struct aiocb));
    memset(aiocb_write, 0, sizeof(struct aiocb));

    aiocb_write->aio_fildes = 1;
    aiocb_write->aio_offset = 0;
    aiocb_write->aio_buf = prevBlock;
    aiocb_write->aio_nbytes = WORD_SIZE * block_size * block_size;
    aiocb_write->aio_reqprio = 0;
    
    aiocb_read->aio_fildes = 0;
    aiocb_read->aio_offset = 0;
    aiocb_read->aio_buf = currBlock;
    aiocb_read->aio_nbytes = WORD_SIZE * block_size * block_size;
    aiocb_read->aio_reqprio = 0;
    
    //get start time
    time(&st_time);

    //prime pump
    aio_read(aiocb_read);
    while(aio_error(aiocb_read) == EINPROGRESS);
    aio_return(aiocb_read);
    //printf("=%s=", (char*)aiocb_read->aio_buf);
    aiocb_read->aio_buf = nextBlock;

    for(i = 0; i < block_size * block_size - 2; i++)
    {
        //read request
        aio_read(aiocb_read);
        
        matrix_add(currBlock, block_size, scalar);

        //printf("=%s=\n", currBlock);

        //write request and return
        aio_write(aiocb_write);
        while(aio_error(aiocb_write) == EINPROGRESS);
        aio_return(aiocb_write);
        memcpy(prevBlock, currBlock, block_size);
        //printf("%s\n", prevBlock);
        //read return
        while(aio_error(aiocb_read) == EINPROGRESS);
        aio_return(aiocb_read);
        memcpy(currBlock, nextBlock, block_size);
    }
    //drain pump
    matrix_add(currBlock, block_size, scalar);
    aio_write(aiocb_write);
    aio_return(aiocb_write);
    //get end time
    time(&en_time);

    printf("Allotted time: %d\n", en_time - st_time);

}