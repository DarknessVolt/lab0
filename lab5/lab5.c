#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

long unsigned int PAGESIZE = 4096; //4kb = 2^12
long unsigned int PAGETABLE = 1048576; // 2 ^ (32 - 12)

void findPage(long unsigned int inAddress, long unsigned int* page)
{
    *page = inAddress/PAGESIZE;
    *page = (long unsigned int)floor((double)*page);
}

void findOffset(long unsigned int inAddress, long unsigned int* offset)
{
    *offset = inAddress%PAGESIZE;
}

int main(int argc, char** argv)
{
    if(argc == 1)
    {
        printf("Not enough arguments\n");
        return 1;
    }
    long unsigned int addressIn;
    long unsigned int page = 0;
    long unsigned int offset;

    sscanf(argv[1], "%lu", &addressIn);
    //printf(%lu", addressIn);

    findPage(addressIn, &page);
    findOffset(addressIn, &offset);

    printf("The address %s contains:\n", argv[1]);
	printf("Page number = %lu\n", page);
	printf("Offset = %lu\n", offset);

    return 0;
}