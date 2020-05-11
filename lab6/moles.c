#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
{
    FILE* logfile;
    char* home = getenv("HOME");
    
    //printf("%s\n", home);
    
    chdir(home);
    
    logfile = fopen("lab6.log", "a");

    fprintf(logfile, "Pop %s\n", argv[0]);

    fclose(logfile);
    
    //pause();

    return 0;
}