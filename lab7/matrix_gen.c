#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define RANGE 101

int generate_rand_int()
{
    return rand()%RANGE;
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
            printf("%03d ", generate_rand_int());
        }
        printf("\n");
    }
    return 0;
}