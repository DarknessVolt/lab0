#include <stdlib.h>
#include <stdio.h>


int main(int argc, char** argv)
{
    FILE* logfile;
    char* home = getenv("HOME");

    chdir(home);
    
    logfile = fopen("lab6.log", "a");

    fprintf(logfile, "Pop %s\n", argv[0]);

    fclose(logfile);
    
    pause();

    return 0;
}