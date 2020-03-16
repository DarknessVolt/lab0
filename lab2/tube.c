#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int commaPos(int argc, char** argv)
{
    int i;

    for(i = 1; i < argc; i++)
    {
        if(strcmp(",", argv[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

char** prepArgv(int start, int argc, char** argv)
{
    int size = argc - start + 1;
    char* argv2[size];
    int i;

    for(i = 0; i < size; i++)
    {
        strcpy(argv2[i], argv[i + start]);
    }
    argv2[argc-1] = (char*)0;
    
    return argv2;
}

int forkAndLaunch(int argc, char** argv, pid_t pid)
{
    int secondArgPos = commaPos(argc, argv);
    if(secondArgPos == -1)
    {
        printf("ARGUMENTS REJECTED\n");
    }

    pid_t pid[2];
    int i;

    for(i = 0; i < 2; i++)
    {
        pid[i] = fork();
        if(pid[i] <= 0)
        {
            break;
        }
    }
    int childNum = i;

    if(pid == 0)
    {
        //child process


        if(childNum == 0)
        {
            execve(argv[1], prepArgv(1, argc, argv), NULL);
        }
        else
        {
            execve(argv[secondArgPos + 1], prepArgv(secondArgPos + 1, argc, argv), NULL);
        }

        printf("EXEC ERROR");
    }
    else if(pid < 0)
    {
        //error
        printf("FORKING ERROR")
    }
    else
    {
        //parent process

        int status1;
        int status2;

        printf("%s: $$ = %d\n", argv[1], pid[0]);
        printf("%s: $$ = %d\n", argv[1], pid[1]);

        waitpid(pid[0], &status1, 0);
        waitpid(pid[1], &status2, 0);

        printf("%s: $? = %d\n", argv[1], status1);
        printf("%s: $? = %d\n", argv[2], status2);
    }
}

int main(int argc, char** argv)
{
    if(argc <=2)
    {
        printf("INSUFFICIENT ARGUMENTS\n");
    }
    
    forkAndLaunch(argc, argv);

    return 0;
}