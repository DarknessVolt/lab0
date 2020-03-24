#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <string.h>


int maxTermCount = 3;

/*enum signals{
SIGHU = 1, SIGINT_, SIGQUIT, SIGILL_, SIGTRAP,
SIGABRT_, SIGBUS, SIGFPE_, SIGKILL, SIGUSR1,
SIGSEGV_, SIGUSR2, SIGPIPE, SIGALRM, SIGTERM_,
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
};*/

static char csignals[64][12] = {
"HU", "INT", "QUIT", "ILL", "TRAP",
"ABRT", "BUS", "FPE", "KILL", "USR1",
"SEGV", "USR2", "PIPE", "ALRM", "TERM",
"STKFLT", "CHLD", "CONT", "STOP", "TSTP",
"TTIN", "TTOU", "URG", "XCPU", "XFSZ",
"VTALRM", "PROF", "WINCH", "IO", "PWR",
"SYS", "RTMIN", "RTMIN+1", "RTMIN+2", "RTMIN+3",
"RTMIN+4", "RTMIN+5", "RTMIN+6", "RTMIN+7", "RTMIN+8",
"RTMIN+9", "RTMIN+10", "RTMIN+11", "RTMIN+12", "RTMIN+13",
"RTMIN+14", "RTMIN+15", "RTMAX-14", "RTMAX-13", "RTMAX-12",
"RTMAX-11", "RTMAX-10", "RTMAX-9", "RTMAX-8", "RTMAX-7",
"RTMAX-6", "RTMAX-5", "RTMAX-4", "RTMAX-3", "RTMAX-2",
"RTMAX-1", "RTMAX"
};

int termCount = 0;
int sigCount = 0;

void sighandler(int sig)
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
    printf("SIG%s caught at %d\n", csignals[sig-1], time(NULL));

    //reset signal
    signal(sig, sighandler);
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
        for(j = 1; j < 64; j++)
        {
            if(strcmp(csignals[j-1], argv[i]) == 0)
            {
                sig[i-1] = j;
                //printf("%d\n", sig[i-1]);
                break;
            }
        }
    }

    //register handler for each arg
    for(i = 0; i < sigSize; i++)
    {
        signal(sig[i], sighandler);
    }
    //report pid to stderr
    fprintf(stderr, "catcher: $$ = %d\n", getpid());

    while(keepLooping)
    {
        //pause
        pause();
        //printf("yeet");
        //if 3 successive SIGTERM, terminate loop
        if(termCount >= maxTermCount)
        {
            break;
        }
    }
    //final status report
    fprintf(stderr, "catcher: Total signals count = %d\n", sigCount);
}