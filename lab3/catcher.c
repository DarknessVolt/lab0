#include <stdio.h>
#include <signal.h>
#include <unistd.h>

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
}
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