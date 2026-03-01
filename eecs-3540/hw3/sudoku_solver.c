#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

#define GRID_SIZE (9)
#define MAX_LINE_LENGTH (25)
#define MAX_THREAD_COUNT (27)
#define INPUT_FILE_PATH ("puzzles.txt")

// --- CONTROL DEFINITIONS FOR TEST CASES ---

// Undefine for no max puzzle count
//#define MAX_PUZZLE_COUNT (1)

//#define LOG_THREAD_PROGRESS
//#define BENCHMARK

// --- END CONTROL DEFINITIONS FOR TEST CASES ---

typedef struct
{
    int thread_number;
    int puzzle_row;
    int puzzle_column;
} thread_parameter_t;

bool thread_result[MAX_THREAD_COUNT];
int puzzle[GRID_SIZE][GRID_SIZE];

int read_puzzle(FILE *fp_in)
{
    for (int row = 0; row < GRID_SIZE; row++)
    {
        char line[MAX_LINE_LENGTH];

        if (fgets(line, MAX_LINE_LENGTH, fp_in) == NULL)
        {
            fprintf(stderr, "File ended during the parsing of a puzzle");
            return 1;
        }

        char *split;
        split = strtok(line, " ");

        for (int col = 0; col < GRID_SIZE; col++)
        {
            if (split == NULL)
            {
                fprintf(stderr, "Line ended prematurely");
                return 2;
            }

            sscanf(split, "%d", &puzzle[row][col]);
            split = strtok(NULL, " ");

        }
    }

    return 0;
}


void *row_runner(void *param)
{
    thread_parameter_t *params = (thread_parameter_t *) param;

    bool present[GRID_SIZE] = { false };
    int row = params->puzzle_row;
    thread_result[params->thread_number] = true;

    for (int i = 0; i < GRID_SIZE; i++)
    {
        int value = puzzle[row][i];

        if (present[value])
        {
            thread_result[params->thread_number] = false;
            break;
        }

        present[value] = true;
    }

#ifdef LOG_THREAD_PROGRESS
    printf("Thread %d: Row validation %s\n",
            params->thread_number,
            thread_result[params->thread_number] ? "Valid" : "Invalid"
          );
#endif

    pthread_exit(NULL);
}


void *col_runner(void *param)
{
    thread_parameter_t *params = (thread_parameter_t *) param;

    bool present[GRID_SIZE] = { false };
    int col = params->puzzle_column;
    thread_result[params->thread_number] = true;

    for (int i = 0; i < GRID_SIZE; i++)
    {
        int value = puzzle[i][col];

        if (present[value])
        {
            thread_result[params->thread_number] = false;
            break;
        }

        present[value] = true;
    }

#ifdef LOG_THREAD_PROGRESS
    printf("Thread %d: Coumn validation %s\n",
            params->thread_number,
            thread_result[params->thread_number] ? "Valid" : "Invalid"
          );
#endif

    pthread_exit(NULL);
}


void *sub_grid_runner(void *param)
{
    thread_parameter_t *params = (thread_parameter_t *) param;

    bool present[GRID_SIZE] = { false };
    int row = params->puzzle_row;
    int col = params->puzzle_column;
    thread_result[params->thread_number] = true;

    for (int i = 0; i < GRID_SIZE; i++)
    {
        int value = puzzle[row + (i / 3)][col + (i % 3)];

        if (present[value])
        {
            thread_result[params->thread_number] = false;
            break;
        }

        present[value] = true;
    }

#ifdef LOG_THREAD_PROGRESS
    printf("Thread %d: Subgrid validation %s\n",
            params->thread_number,
            thread_result[params->thread_number] ? "Valid" : "Invalid"
          );
#endif

    pthread_exit(NULL);
}


bool validate_puzzle(int thread_utilize_cnt)
{
    pthread_t tid[MAX_THREAD_COUNT];
    pthread_attr_t tattr[MAX_THREAD_COUNT];
    thread_parameter_t tparams[MAX_THREAD_COUNT];
    int cnt = 0, next_wait = 0, active_cnt = 0;

    // Create row threads.
    for (int i = 0; i < GRID_SIZE; i++)
    {
        tparams[cnt].thread_number = cnt;
        tparams[cnt].puzzle_row = i;
        tparams[cnt].puzzle_column = 0;

        pthread_attr_init(&tattr[cnt]);
        if (active_cnt >= thread_utilize_cnt)
        {
            pthread_join(tid[next_wait], NULL);
            next_wait++;
            active_cnt--;
        }
        pthread_create(&tid[cnt], &tattr[cnt], row_runner, &tparams[cnt]);
        
        active_cnt++;
        cnt++;
    }

    // Create column threads.
    for (int i = 0; i < GRID_SIZE; i++)
    {
        tparams[cnt].thread_number = cnt;
        tparams[cnt].puzzle_column = i;
        tparams[cnt].puzzle_row = 0;

        pthread_attr_init(&tattr[cnt]);
        if (active_cnt >= thread_utilize_cnt)
        {
            pthread_join(tid[next_wait], NULL);
            next_wait++;
            active_cnt--;
        }
        pthread_create(&tid[cnt], &tattr[cnt], col_runner, &tparams[cnt]);

        active_cnt++;
        cnt++;
    }

    // Create sub grid threads.
    for (int i = 0; i < GRID_SIZE; i++)
    {
        tparams[cnt].thread_number = cnt;
        tparams[cnt].puzzle_row = (i / 3) * 3;
        tparams[cnt].puzzle_column = (i % 3) * 3;

        pthread_attr_init(&tattr[cnt]);
        if (active_cnt >= thread_utilize_cnt)
        {
            pthread_join(tid[next_wait], NULL);
            next_wait++;
            active_cnt--;
        }
        pthread_create(&tid[cnt], &tattr[cnt], sub_grid_runner, &tparams[cnt]);

        active_cnt++;
        cnt++;
    }

    // Join threads.
    for (; next_wait < MAX_THREAD_COUNT; next_wait++)
    {
        pthread_join(tid[next_wait], NULL);
    }

    // Examine results.
    for (int i = 0; i < MAX_THREAD_COUNT; i++)
    {
        if (!thread_result[i])
        {
            return false;
        }
    }

    return true;
}


int main()
{
    FILE *fp_in;
    char line[MAX_LINE_LENGTH];
    ssize_t len = 0;
    int puzzle_num = 1;

    int requested_puzzles[3] = { 2, 3, 5 };

    fp_in = fopen(INPUT_FILE_PATH, "r");
    if (fp_in == NULL)
    {
        fprintf(stderr, "Unable to open file \"%s\"", INPUT_FILE_PATH);
        exit(1);
    }

    do
    {
        int result;

        if ((result = read_puzzle(fp_in)) != 0)
        {
            fprintf(stderr, "Puzzle parsing failed with error code \"%d\"", result);
            exit(2);
        }
    
        bool valid;

#ifdef BENCHMARK
        for (int i = 9; i <= 36; i += 9)
        {
            clock_t start = clock();
            valid = validate_puzzle(i);
            clock_t end = clock();

            double total_time = (double)(end - start) / CLOCKS_PER_SEC;

            printf("Execution time for Puzzle %d with %d threads: %f seconds\n",
                    puzzle_num,
                    i,
                    total_time
                  );
        }
#else
        valid = validate_puzzle(MAX_THREAD_COUNT);
#endif

        if (valid)
        {
            printf("Puzzle %d: Valid\n", puzzle_num);
        }
        else
        {
            printf("Puzzle %d: Invalid\n", puzzle_num);
        }

        puzzle_num++;
#ifdef MAX_PUZZLE_COUNT
    } while (fgets(line, MAX_LINE_LENGTH, fp_in) && (puzzle_num < MAX_PUZZLE_COUNT));
#else
    } while (fgets(line, MAX_LINE_LENGTH, fp_in));
#endif
}
