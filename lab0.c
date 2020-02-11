#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define STR_LEN 200

typedef struct out
{
    int decimal;
    int parity;
    char c;
    char byte[8];
}Out;

char readChar(int* offset, char* stringOfBits)
{
    char c = stringOfBits[*offset];
    *offset++;
    return c;
}

int readBit(int* offset, char* stringOfBits)
{
    char c;
    do
    {
        c = readChar(offset, stringOfBits);

        if(c == '1' || c == '0')
        {
            return (int)(c - '0');
        }
        else if(c == '\0')
        {
            return -1;
        }

    }while(*offset < STR_LEN);

    return -1;
}

Out readByte(int* offset, char* stringOfBits)
{
    int i;
    int bit;
    Out out;
    
    out.decimal = 0;
    out.parity = 0;
    
    for(i = 7; i >= 0; i++)
    {

        bit = readBit(offset, stringOfBits);

        if(bit == -1 && i == 7)
        {
            out.decimal = -1;
            return out;
        }
        else if(bit == -1)
        {
            for(i; i>=0; i++)
            {
                out.byte[7-i] = '0';
            }
        }
        else
        {
            out.parity += bit;
            out.decimal += bit * pow(2, i);
            out.byte[7-i] = bit + '0';
        }
    }
    out.c = (char)out.decimal;
    return out;
}

int main(int argc, char** argv)
{
    char *fileName = malloc(100*sizeof(char));
    char stringOfBits[STR_LEN];
    int *offset;
    //check for command line arguments
    if(argc == 1 || strcmp(argv[1], "-"))
    {
        //use stdin
        
    }
    else
    {
        strcpy(fileName, argv[1]);
    }

    //open thee file
    int file = open(fileName, O_RDONLY);

    if(file == -1)
    {
        printf("ERROR: File Not Found");
        exit(1);
    }
    
    int i = 0;
    int j;
    Out out;

    int loop = 1;
    *offset = 0;

    printf("Original ASCII    Decimal  Parity  \n");
    printf("-------- -------- -------- --------\n");
    //loop read 8 bits
    while(loop)
    {
        out = readByte(offset, stringOfBits);

        if(out.decimal = -1)
        {
            break;
        }
        else
        {
            printf("%s %8c %8d ", out.byte, out.c, out.decimal);
            if(out.parity%2)
            {
                printf("ODD\n");
            }
            else
            {
                printf("EVEN\n");
            }
            
        }
    }
    /*
    while(readReturn)
    {
        while(i < 8)
        {
            //save "bit" to string
            readReturn = (int)read(file, &curr, 1);
            if(curr == ' ' || curr == '\n' || curr == '\t' || curr ='\0')
            {
                continue;
            }
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
    }*/
    //
    return 0;
}