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
    char *buf = alloc
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


    int i;
    int j;
    int parity;
    char curr;
    int dec;
    //loop read 8 bits
    while(/*end condition*/)
    {
        for(i = 0; i < 8; i++)
        {
            //save "bit" to string
            
            //calculate the shtuffs
            if(curr == '1')
            {
                dec += pow(2, i);
                parity += 1;
            }
        }
        //check if there are any more chars+
        //read a char
        //add char to string
        //convert to int
        //print and formatting
    }
    //
}