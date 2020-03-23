#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static int count = 3;

void sigHandler(int sig)
{
    printf("%d\n", sig);
}
int main(int argc, char* argv[])
{
    //process command line
    if(arc < 2)
    {
        fprintf(stderr, "INSUFFICIENT ARGUMENTS\n");
    }

    //report pid to stderr
    fprintf(stderr, "catcher: $$ = %d", getpid());

    //register handler for each arg

    //pause
    pause();
    //report signal caught

    //add to the count

    //if 3 successive SIGTERM, terminate loop

    //final status report

}