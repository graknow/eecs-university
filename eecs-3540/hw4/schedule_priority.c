/**
 *
 * Priority scheduling
 */

#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

struct node *head = NULL;

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
 * Run the priority scheduler
 */
void schedule() 
{
    Task *current;

    while (head != NULL) {
        current = pickNextTask();
        
        run(current, current->burst);

        delete(&head, current);
    }
}

/**
 * Returns the next task selected to run.
 */
Task *pickNextTask()
{
    struct node *cursor, *highest_priority;
    cursor = head;
    highest_priority = head;

    while (cursor != NULL)
    {
        if (cursor->task->priority > highest_priority->task->priority)
        {
            highest_priority = cursor;
        }

        cursor = cursor->next;
    }
    return highest_priority->task;
}
