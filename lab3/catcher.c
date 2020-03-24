#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <string.h>


int maxTermCount = 3;
static int totalSignals = 64;

enum signals{
SIGHU = 1, SIGINT, SIGQUIT, SIGILL, SIGTRAP,
SIGABRT, SIGBUS, SIGFPE, SIGKILL, SIGUSR1,
SIGSEGV, SIGUSR2, SIGPIPE, SIGALRM, SIGTERM,
SIGSTKFLT, SIGCHLD, SIGCONT, SIGSTOP, SIGTSTP,
SIGTTIN, SIGTTOU, SIGURG, SIGXCPU, SIGXFSZ,
SIGVTALRM, SIGPROF, SIGWINCH, SIGIO, SIGPWR,
SIGSYS, SIGRTMIN, SIGRTMIN1, SIGRTMIN2, SIGRTMIN3,
SIGRTMIN4, SIGRTMIN5, SIGRTMIN6, SIGRTMIN7, SIGRTMIN8,
SIGRTMIN9, SIGRTMIN10, SIGRTMIN11, SIGRTMIN12, SIGRTMIN13,
SIGRTMIN14, SIGRTMIN15, SIGRTMAX14, SIGRTMAX13, SIGRTMAX12,
SIGRTMAX11, SIGRTMAX10, SIGRTMAX9, SIGRTMAX8, SIGRTMAX7,
SIGRTMAX6, SIGRTMAX5, SIGRTMAX4, SIGRTMAX3, SIGRTMAX2,
SIGRTMAX1, SIGRTMAX
};

static char csignals[totalSignals][11] = {
"SIGHU", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP",
"SIGABRT", "SIGBUS", "SIGFPE", "SIGKILL", "SIGUSR1",
"SIGSEGV", "SIGUSR2", "SIGPIPE", "SIGALRM", "SIGTERM",
"SIGSTKFLT", "SIGCHLD", "SIGCONT", "SIGSTOP", "SIGTSTP",
"SIGTTIN", "SIGTTOU", "SIGURG", "SIGXCPU", "SIGXFSZ",
"SIGVTALRM", "SIGPROF", "SIGWINCH", "SIGIO", "SIGPWR",
"SIGSYS", "SIGRTMIN", "SIGRTMIN+1", "SIGRTMIN+2", "SIGRTMIN+3",
"SIGRTMIN+4", "SIGRTMIN+5", "SIGRTMIN+6", "SIGRTMIN+7", "SIGRTMIN+8",
"SIGRTMIN+9", "SIGRTMIN+10", "SIGRTMIN+11", "SIGRTMIN+12", "SIGRTMIN+13",
"SIGRTMIN+14", "SIGRTMIN+15", "SIGRTMAX-14", "SIGRTMAX-13", "SIGRTMAX-12",
"SIGRTMAX-11", "SIGRTMAX-10", "SIGRTMAX-9", "SIGRTMAX-8", "SIGRTMAX-7",
"SIGRTMAX-6", "SIGRTMAX-5", "SIGRTMAX-4", "SIGRTMAX-3", "SIGRTMAX-2",
"SIGRTMAX-1", "SIGRTMAX"
};

int termCount = 0;
int sigCount = 0;

void sigHandler(int sig)
{
    //add to termcount
    if(sig == SIGTERM)
    {
        termCount++;
    }
    else
    {
        termCount = 0;
    }

    sigCount++;

    //report signal caught
    printf("%s caught at %d\n", sig, time());
}

int main(int argc, char** argv)
{
    //process command line
    if(argc < 2)
    {
        fprintf(stderr, "INSUFFICIENT ARGUMENTS\n");
    }

    int sigSize = argc - 1;
    int sig[sigSize];
    int keepLooping = 1;
    int i;
    int j;

    for(i = 1; i < argc; i++)
    {
        for(j = SIGHU; j < SIGRTMAX, j++)
        {
            if(strcmp(csignals[j-1], argc[i]) == 0)
            {
                sig[i-1] = j;
                break;
            }
        }
    }

    //report pid to stderr
    fprintf(stderr, "catcher: $$ = %d\n", getpid());

    while(keepLooping)
    {
        //register handler for each arg
        for(i = 0; i < sigSize; i++)
        {
            singal(sig[i], sigHandler);
        }
        //pause
        pause();

        //if 3 successive SIGTERM, terminate loop
        if(termCount >= maxTermCount)
        {
            break;
        }
    }
    //final status report
    fprintf(stderr, "catcher: Total signals count = %d\n", sigCount);
}