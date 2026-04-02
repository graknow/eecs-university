#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "buffer.h"

#define MAX_THREAD_COUNT (BUFFER_SIZE * 4)

buffer_item buffer[BUFFER_SIZE];
int head = 0, tail = 0, cnt = 0;
int full, empty, mutex;

void wait(int *semaphore)
{
    while (*semaphore <= 0);

    *semaphore = *semaphore - 1;
}

void signal(int *semaphore)
{
    *semaphore = *semaphore + 1;
}

int insert_item(buffer_item item)
{
    if (cnt >= BUFFER_SIZE)
    {
        return -1;
    }

    buffer[head] = item;
    head = (head + 1) % BUFFER_SIZE;
    cnt++;

    return 0;
}

int remove_item(buffer_item *item)
{
    if (cnt <= 0)
    {
        return -1;
    }

    *item = buffer[tail];
    tail = (tail + 1) % BUFFER_SIZE;
    cnt--;

    return 0;
}

void *producer(void *param)
{
    buffer_item item;

    while (true)
    {
        sleep(rand() % 5);
        item = rand();

        wait(&empty);
        wait(&mutex);

        if (insert_item(item))
        {
            fprintf(stderr, "producer failed to insert produced item\n");
        }
        else
        {
            printf("producer produced %d\n", item);
        }

        signal(&mutex);
        signal(&full);
    }
}

void *consumer(void *param)
{
    buffer_item item;

    while (true)
    {
        sleep(rand() % 5);
        item = rand();

        wait(&full);
        wait(&mutex);

        if (remove_item(&item))
        {
            fprintf(stderr, "consumer failed to remove an item\n");
        }
        else
        {
            printf("consumer consumed %d\n", item);
        }

        signal(&mutex);
        signal(&empty);
    }
} 

int main(int argc, char *argv[])
{
    if (argc != 4)
    {
        fprintf(stderr, "Invalid arguments passed, usage should be: ./buffer [a1] [a2] [a3]");
        exit(1);
    }

    int sleep_time = atoi(argv[1]);
    int producer_cnt = atoi(argv[2]), consumer_cnt = atoi(argv[3]);
    pthread_t tid[MAX_THREAD_COUNT];
    int current_index = 0;
    full = 0, empty = 1, mutex = 1;

    for (int j = 0; j < producer_cnt; j++)
    {
        pthread_create(&tid[current_index], NULL, producer, &tid[current_index]);
        current_index++;
    }

    for (int j = 0; j < consumer_cnt; j++)
    {
        pthread_create(&tid[current_index], NULL, consumer, &tid[current_index]);
        current_index++;
    }

    sleep(sleep_time);

    for (int j = 0; j < current_index; j++)
    {
        pthread_cancel(tid[j]);
    }

    exit(0);
}
