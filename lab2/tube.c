#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

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

char** prepArgv(int start, int argc, char** argv, char** argv2, int size)
{
    
    int i;

    for(i = 0; i < size; i++)
    {
        strcpy(argv2[i], argv[i + start]);
    }
    argv2[argc-1] = (char*)0;

}

int forkAndLaunch(int argc, char** argv)
{
    int fd1[2];
    //int fd2[2];

    if(pipe(fd1) == -1)
    {
        fprintf(stderr, "PIPE ERROR\n");
        return 1;
    }
    

    int secondArgPos = commaPos(argc, argv);
    if(secondArgPos == -1)
    {
        fprintf(stderr, "ARGUMENTS REJECTED\n");
        return 1;
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
            close(fd1[0]);
            
            if(dup2(fd1[1], 1) == -1)
            {
                fprintf(stderr, "DUP FAILURE\n");
                return 1;
            }

            close(fd1[1]);
            
            int start = 1;

            int size = argc - start + 1;
            char* argv2[size];

            prepArgv(start, argc, argv, argv2, size);

            execve(argv[start], argv2, NULL);
        }
        else
        {
            close(fd1[1]);

            if(dup2(fd1[0], 0) == -1)
            {
                fprintf(stderr, "DUP FAILURE\n");
                return 1;
            }

            close (fd1[0]);
            
            int start = secondArgPos + 1;
            int size = argc - start + 1;
            char* argv2[size];

            prepArgv(start, argc, argv, argv2, size);

            execve(argv[start], argv2, NULL);
        }

        fprintf(stderr, "EXEC ERROR\n");
        return 1;
    }
    else if(pid < 0)
    {
        //error
        fprintf(stderr, "FORKING ERROR\n");
        return 1;
    }
    else
    {
        //parent process

        int status1;
        int status2;

        fprintf(stderr, "%s: $$ = %d\n", argv[1], pid[0]);
        fprintf(stderr, "%s: $$ = %d\n", argv[secondArgPos + 1], pid[1]);

        close(fd1[0]);
        close(fd1[1]);

        waitpid(pid[0], &status1, 0);
        waitpid(pid[1], &status2, 0);

        fprintf(stderr, "%s: $? = %d\n", argv[1], status1);
        fprintf(stderr, "%s: $? = %d\n", argv[secondArgPos + 1], status2);
    }

    return 0;
}

int main(int argc, char** argv)
{
    if(argc <=2)
    {
        fprintf(stderr, "INSUFFICIENT ARGUMENTS\n");
        return 1;
    }

    return forkAndLaunch(argc, argv);

}