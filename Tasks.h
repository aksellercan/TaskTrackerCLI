#ifndef TASKS_H
#define TASKS_H
#include <stdbool.h>

extern int arrayLength;

typedef struct
{
    unsigned long id;
    char description[61]; //+1 for the \0
    char status[13];
    char createdAt[30];
    char updatedAt[30];
} Task;

void task_add_task(const Task *task, bool saveToFile);
void task_remove_task(const unsigned long task_id);
void task_update_task(const unsigned long taskid, const char *description);
void task_sort_task_by_completed();
void task_sort_task_by_in_progress();
void task_sort_task_by_todo();
void task_sort_by_status(const char *status);
void task_mark_task_status(unsigned long taskid, const char *status);
void task_list_tasks();
void task_free_tasks();

#endif // TASKS_H
