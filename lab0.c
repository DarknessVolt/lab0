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

char iascii[34][6] = {"NULL", "SOH", "STX", "ETX",  "EOT", "ENQ", "ACK", "BEL", "BS", "TAB", "LF", "VT", "FF", "CR", "SO", "SI", "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", "SYN", "ETB", "CAN", "EM", "SUB", "ESC", "FS", "GS", "RS", "US", "Space", "DEL"};

int buffer(char** input, int size)
{
    int i;
    int j;
    for(i=0; i < size; i++)
    {
        for(j = 0; j < 8; j++)
        {
            if(!(input[i][j] == '1' || input[i][j] == '0'))
            {
                input[i][j] = '0';
            }
        }
    }
}

/*
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
}*/

int readBit(char* stringOfBits, int loc)
{
    return (int)(stringOfBits[loc] - '0');
}   

Out readByte(char* stringOfBits)
{
    int i;
    int bit;
    Out out;
    
    out.decimal = 0;
    out.parity = 0;
    
    for(i = 7; i >= 0; i++)
    {

        bit = readBit(stringOfBits, 7-i);

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
    char input[STR_LEN][8];
    int fileHandle;
    int *offset;
    char mode = '0';
    char buffer;
    int size = 0;

    //check for command line arguments
    /*if(argc <= 1)
    {
        //use stdin
        //printf("0: INPUT FILE NAME 1: ENTER INPUT MANUALLY");
        printf("ERROR: Insufficient Arguments");
        exit(0);
    }
    else
    {
        if(strcmp(argv[1], "-"))
        {
            mode = 1;
        }
        strcpy(input, argv[1]);
    }*/

    //open thee file

    if(argc <= 1)
    {
        printf("ERROR: Insufficient Arguments");
        exit(1);
    }
    else if(argv[1][0] == '-')
    {
        int i;
        for(i = 2; i < argc; i++)
        {
            *input[i-2] = (char*)realloc(argv[i], sizeof(char)*8);
        }
        size = argc - 2;
    }
    else if(argv[1][0] == '1' || argv[1][0] == '0')
    {
        int i;
        for(i = 1; i < argc; i++)
        {
            *input[i-1] = (char*)realloc(argv[i], sizeof(char)*8);
        }
        size = argc - 1;
    }
    else
    {
        fileHandle = open(argv[1], O_RDONLY);

        if(fileHandle == -1)
        {
            printf("ERROR: File Not Found");
            exit(1);
        }

        int loop = 1;
        int j = 0;
        int i = 0;
        while(1)
        {
            int i;
            loop = read(fileHandle, buffer, 1);
            if(loop == 0)
            {
                break;
            }
            else if(input[i] == " ")
            {
                j++;
                size++;
            }
            else
            {
                if(buffer == '1' || buffer == '0')
                {
                    input[j][i] = buffer;
                    i++;
                }
            }
        }
    }
    size++;

    

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
        out = readByte(offset, input);

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