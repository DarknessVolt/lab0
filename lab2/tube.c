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
        argv2[i] = argv[i + start];
        //printf("%s\n", argv2[i]);
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


    int start1 = 1;
    int start2 = secondArgPos + 1;

    int size2 = argc - start2 + 1;
    int size1 = argc - size2;

    char* argv2[size1];
    char* argv3[size2];

    printf("%d: %d: %d\n", size1, size2, argc);
    pid_t pidt[2];
    int i;

    for(i = 0; i < 2; i++)
    {
        pidt[i] = fork();
        if(pidt[i] <= 0)
        {
            break;
        }
    }
    
    int pid;
    int childNum = i;
    if(childNum == 0 || childNum == 1)
    {
        pid = pidt[childNum];
    }
    else
    {
        pid = pidt[0];
    }
    

    //printf("%d\n", childNum);
    if(pid == 0)
    {
        //child process

        if(childNum == 0)
        {
            prepArgv(start1, argc, argv, argv2, size1);
            printf("%s\n", argv2[0]);

            close(fd1[0]);
            
            if(dup2(fd1[1], 1) == -1)
            {
                fprintf(stderr, "DUP FAILURE\n");
                return 1;
            }

            close(fd1[1]);
        

            execve(argv2[0], argv2, NULL);
        }
        else
        {
            prepArgv(start2, argc, argv, argv3, size2);
            printf("%s\n", argv3[0]);
            close(fd1[1]);

            if(dup2(fd1[0], 0) == -1)
            {
                fprintf(stderr, "DUP FAILURE\n");
                return 1;
            }

            close (fd1[0]);


            execve(argv3[0], argv3, NULL);
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

        fprintf(stderr, "%s: $$ = %d\n", argv[1], pidt[0]);
        fprintf(stderr, "%s: $$ = %d\n", argv[secondArgPos + 1], pidt[1]);

        close(fd1[0]);
        close(fd1[1]);

        waitpid(pidt[0], &status1, 0);
        waitpid(pidt[1], &status2, 0);

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