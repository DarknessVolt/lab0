#include <stdlib.h>
#include <stdio.h>


int main(int argc, char** argv)
{
    char* logfile;
    char* home = getenv("HOME");

    fprintf(logfile, "Pop %s\n", argv[0]);

    pause();
    
    return 0;
}