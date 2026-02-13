#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>

#define MAX_LINE (80) /* Max command length */
#define MAX_ARGS (MAX_LINE/2 + 1)

int main(void)
{
    char *args[MAX_ARGS]; /* command line arguments */
    char *pipe_args[MAX_ARGS];
    char buffer[MAX_LINE + 1];
    int should_run = 1;

    for (int i = 0; i < MAX_ARGS; i++)
    {
        args[i] = NULL;
    }

    while (should_run)
    {
        printf("osh>");
        fflush(stdout);

        char c;
        int arglen = 0, argc = 0, total = 0;
        int should_repeat = 0;

        do
        {
            c = getchar();

            if (c == ' ' || c == '\n')
            {
                buffer[arglen] = '\0';

                if (strcmp(buffer, "!!") == 0 && argc == 0)
                {
                    should_repeat = 1;
                }
                else
                {
                    if (args[argc] == NULL)
                    {
                        args[argc] = (char *)malloc(arglen + 1);
                    }
                    else
                    {
                        args[argc] = (char *)realloc(args[argc], arglen + 1);
                    }

                    strncpy(args[argc], buffer, arglen + 1);

                    arglen = 0;
                    argc++;
                }

                continue;
            }

            buffer[arglen] = c;
            arglen++;
            total++;
        } while (c != '\n' && total < MAX_LINE && !should_repeat);

        if (should_repeat)
        {
            if (args[0] == NULL)
            {
                printf("No command history found.\n");
                continue;
            }

            for (int i = 0; args[i] != NULL; i++)
            {
                printf("%s ", args[i]);
                argc++;
            }
            putchar('\n');
            fflush(stdout);
        }
        else if (args[argc] != NULL)
        {
            free(args[argc]);
            args[argc] = NULL;
        }

        pid_t pid;

        if ((pid = fork()) < 0)
        {
            fprintf(stderr, "fork error");
            exit(1);
        }

        if (pid == 0) // child
        {
            for (int i = 0; i < argc; i++)
            {
                if (strcmp(args[i], ">") == 0 && i + 1 < argc)
                {
                    int ofile;

                    ofile = open(args[i + 1], O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);

                    dup2(ofile, STDOUT_FILENO);

                    free(args[i]);
                    args[i] = NULL;
                }
                else if (strcmp(args[i], "<") == 0 && i + 1 < argc)
                {
                    int ifile;

                    ifile = open(args[i + 1], O_RDONLY);

                    dup2(ifile, STDIN_FILENO);

                    free(args[i]);
                    args[i] = NULL;
                }
                else if (strcmp(args[i], "|") == 0 && i + 1 < argc)
                {
                    free(args[i]);
                    args[i] = NULL;
                    i++;

                    int pd[2];

                    for (int j = 0; i < argc; j++, i++)
                    {
                        pipe_args[j] = args[i];
                        pipe_args[j + 1] = NULL;
                    }

                    if (pipe(pd) < 0)
                    {
                        fprintf(stderr, "pipe error");
                        exit(4);
                    }

                    pid_t pipepid;

                    if ((pipepid = fork()) < 0)
                    {
                        fprintf(stderr, "fork error");
                        exit(1);
                    }


                    if (pipepid == 0)
                    {
                        dup2(pd[1], STDOUT_FILENO);
                        close(pd[0]);

                        execvp(args[0], args);
                        exit(2);
                    }
                    else
                    {
                        dup2(pd[0], STDIN_FILENO);
                        close(pd[1]);
                        wait(NULL);

                        execvp(pipe_args[0], pipe_args);
                        exit(2);
                    }
                
                }
            }

            execvp(args[0], args);
            exit(2);
        }
        else // parent
        {
            wait(NULL);
        }
    }

    for (int i = 0; i < MAX_ARGS; i++)
    {
        if (args[i] != NULL)
        {
            free(args[i]);
            args[i] = NULL;
        }
    }

    return 0;
}
