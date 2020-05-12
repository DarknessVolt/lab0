#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void matrix_add(int** block, int size, int scalar)
{
    int i,j;
    for(i = 0; i < size; i++)
    {
        for(j = 0; j < size; j++)
        {
            block[i][j] += scalar;
        }
    }
}
int main(int argc, char** argv)
{
    int size, blocks, block_size;
    time_t st_time, en_time;

    sscanf(argv[1], "%d", size);
    sscanf(argv[2], "%d", blocks);

    block_size = size/blocks;

    time(&st_time);


    time(&en_time);

    printf("Allotted time: %d", en_time - st_time);

}