#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "schedulers.h"

#define MAX_LINE_LENGTH (30)

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        printf("No task schedule to execute.  Please specify a file path.\n");
        exit(1);
    }

    if (argc > 2)
    {
        printf("Specify only one scheduling file.\n");
        exit(1);
    }

    FILE *fp_in;
    char line[MAX_LINE_LENGTH];

    fp_in = fopen(argv[1], "r");
    if (!fp_in)
    {
        fprintf(stderr, "Unable to open the specified file.");
        exit(2);
    }

    while (fgets(line, MAX_LINE_LENGTH, fp_in))
    {
        char *name, *name_buf;
        int priority;
        int burst;

        name_buf = strtok(line, ", ");
        sscanf(strtok(NULL, ", "), "%d", &priority);
        sscanf(strtok(NULL, ", "), "%d", &burst);

        name = malloc((sizeof(char) * strlen(name_buf)) + 1);
        strcpy(name, name_buf);

        add(name, priority, burst);
    }

    fclose(fp_in);

    schedule();
}
