/**
 *
 * Priority round robin scheduling
 */

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "task.h"
#include "list.h"
#include "cpu.h"

struct node *head = NULL;
struct node *cursor = NULL;
int highest_priority;
bool equal_priority_tasks;

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

    if (newTask->priority > highest_priority)
    {
        highest_priority = newTask->priority;
    }

    // insert the new task into the list of tasks 
    insert(&head, newTask);
}

/**
 * Run the Priority RR scheduler
 */
void schedule() 
{
    Task *current;
    cursor = head;

    while (head != NULL) {
        current = pickNextTask();

        int effective_burst_time;
        if (equal_priority_tasks)
        {
            effective_burst_time = QUANTUM > current->burst ? current->burst : QUANTUM;
        }
        else
        {
            effective_burst_time = current->burst;
        }

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
    struct node *tmp_cursor = head;
    int current_highest_priority = 0;

    while (tmp_cursor)
    {
        if (tmp_cursor->task->priority > current_highest_priority)
        {
            current_highest_priority = tmp_cursor->task->priority;
            equal_priority_tasks = false;
        }
        else if (tmp_cursor->task->priority == current_highest_priority)
        {
            equal_priority_tasks = true;
        }

        tmp_cursor = tmp_cursor->next;
    }

    if (current_highest_priority < highest_priority)
    {
        cursor = head;
        highest_priority = current_highest_priority;
    }
    else if (cursor->next)
    {
        cursor = cursor->next;
    }
    else
    {
        cursor = head;
    }

    while (cursor)
    {
        if (cursor->task->priority == current_highest_priority)
        {
            break;
        } 
        
        if (cursor->next)
        {
            cursor = cursor->next;
        }
        else
        {
            cursor = head;
        }
    }

    return cursor->task;
}
