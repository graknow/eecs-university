/**
 *
 * Round robin scheduling
 */

#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

struct node *head = NULL;
struct node *cursor = NULL;

// sequence counter of next available thread identifier
int nextTid = 0;

Task *pickNextTask();

// add a new task to the list of tasks
void add(char *name, int priority, int burst) {
    // first create the new task
    Task *newTask = (Task *) malloc(sizeof(Task));
    
    newTask->name = name;
    newTask->tid = nextTid++;
    newTask->priority = priority;
    newTask->burst = burst;

    // insert the new task into the list of tasks 
    insert(&head, newTask);
}

/**
 * Run the RR scheduler
 */
void schedule() 
{
    Task *current;

    cursor = head;

    while (head != NULL) {
        current = pickNextTask();

        int effective_burst_time = QUANTUM > current->burst ? current->burst : QUANTUM;
        
        run(current, effective_burst_time);

        current->burst -= effective_burst_time;

        if (current->burst == 0)
        {
            printf("Task %s finished.\n", current->name);
            delete(&head, current);
        }
    }
}

/**
 * Returns the next task selected to run.
 */
Task *pickNextTask()
{
    Task *current = NULL;
    current = cursor->task;

    if (cursor->next)
    {
        cursor = cursor->next;
    }
    else
    {
        cursor = head;
    }

    return current;
}
