#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

char *fileName;

//read input
int readInput(char* in)
{
    int pos = 0;
    
    while(1)
    {

    }
}

int main(int argc, char** argv)
{
    char *fileName = malloc(10*sizeof(char));
    //check for command line arguments
    if(argc == 1 || argv[1] == "-")
    {
        //use stdin
        readInput(fileName);
    }
    else
    {
        fileName = argv[1];
    }

    //open thee file
    int file = open(fileName, O_RDONLY);

    if(file == -1)
    {
        printf("ERROR: File Not Found");
        exit(1);
    }

    int i;
    int j;
    int parity;
    char curr;
    int dec;
    int *stringOfBits = calloc(8, sizeof(char));

    int readReturn = 1;
    //loop read 8 bits
    while(readReturn)
    {
        for(i = 0; i < 8; i++)
        {
            //save "bit" to string
            readReturn = (int)read(file, &curr, 1);
            if(readReturn == 0)
            {
                for(i; i < 8; i++)
                {
                    printf("0");
                }
                break;
            }
            stringOfBits[i] = curr;

            //calculate the shtuffs
            if(curr == '1')
            {
                dec += pow(2, i);
                parity += 1;
            }
        }
        //print and formatting
        printf("%s %8c %8d %8s", stringOfBits, (char)dec, dec, parity);
    }
    //
    return 0;
}