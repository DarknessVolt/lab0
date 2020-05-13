#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define RANGE 101

int generate_rand_int()
{
    int randPositive = rand()%RANGE;
    int randNegative = -1 * rand()%RANGE;
    return randPositive + randNegative;
}

int main(int argc, char** argv)
{
    int size, i, j;
    sscanf(argv[1], "%d", &size);
    
    srand(time(NULL));

    for(j = 0; j < size; j++)
    {

        for(i = 0; i < size; i++)
        {
            //[x,y]:value        |23  |28
            printf("[%010d,%010d]:%4d ", j, i, generate_rand_int());
        }
    }
    return 0;
}