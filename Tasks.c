#include "Tasks.h"
#include "String/String.h"
#include "FileUtility.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

Task *taskList;
int arrayLength;

void _task_print_tasks(Task *task)
{
    if (isNullOrWhiteSpace(task->updatedAt))
    {
        printf("%lu: %s\nStatus: %s, Created At: %s\n", task->id, task->description, task->status, task->createdAt);
    }
    else
    {
        printf("%lu: %s\nStatus: %s, Updated At: %s\n", task->id, task->description, task->status, task->updatedAt);
    }
}

void _task_allocate_memory()
{
    if (taskList != NULL)
    {
        Task *ptr = realloc(taskList, sizeof(Task) * (arrayLength + 1));
        if (ptr == NULL)
        {
            printf("Memory reallocation failed\n");
            exit(3);
        }
        taskList = ptr;
        return;
    }
    taskList = (Task *)malloc(sizeof(Task));
    if (taskList == NULL)
    {
        printf("Memory allocation error\n");
        exit(3);
    }
}

void task_add_task(const Task *task, const bool saveToFile)
{
    if (task == NULL)
        return;
    _task_allocate_memory();
    taskList[arrayLength] = *task;
    arrayLength++;
    if (saveToFile)
    {
        save_to_file(taskList, arrayLength);
    }
}

Task *_bubble_sort(Task *array)
{
    for (int i = 0; i < arrayLength; i++)
    {
        for (int j = i + 1; j < arrayLength; j++)
        {
            if (array[i].id > array[j].id)
            {
                Task temp = taskList[i];
                taskList[i] = taskList[j];
                taskList[j] = temp;
            }
        }
    }
    return taskList;
}

void task_remove_task(const unsigned long task_id)
{
    _Bool success = false;
    for (int i = 0; i < arrayLength; i++)
    {
        const Task *task = &taskList[i];
        if (task->id == task_id)
        {
            taskList[i] = taskList[arrayLength - 1];
            arrayLength--;
            _task_allocate_memory();
            success = true;
        }
    }
    if (success)
    {
        printf("Task with id %lu removed\n", task_id);
        taskList = _bubble_sort(taskList);
        save_to_file(taskList, arrayLength);
    }
    else
    {
        printf("Task with id %lu not found\n", task_id);
    }
}

void task_mark_task_status(const unsigned long taskid, const char *status)
{
    bool success = false;
    for (int i = 0; i < arrayLength; i++)
    {
        Task *taskFound = &taskList[i];
        if (taskFound->id == taskid)
        {
            time_t currentTime;
            time(&currentTime);
            if (compareStrings(status, "done") == 1)
                StringCopy(RemoveTrailingNewLine(ctime(&currentTime)), taskFound->updatedAt);
            StringCopy(status, taskFound->status);
            taskList[i] = *taskFound;
            success = true;
        }
    }
    if (success)
    {
        printf("Task with id %lu status updated\n", taskid);
        save_to_file(taskList, arrayLength);
    }
    else
    {
        printf("Task with id %lu not found\n", taskid);
    }
}

void task_update_task(const unsigned long taskid, const char *description)
{
    const int descLength = stringLength(description);
    if (descLength > 60)
    {
        printf("Description is too long! Counted %d chars, should be less than 60 characters.\n", descLength);
        return;
    }
    bool success = false;
    for (int i = 0; i < arrayLength; i++)
    {
        Task *taskFound = &taskList[i];
        if (taskFound->id == taskid)
        {
            time_t currentTime;
            time(&currentTime);
            StringCopy(RemoveTrailingNewLine(ctime(&currentTime)), taskFound->updatedAt);
            StringCopy(description, taskFound->description);
            const char *status = "todo";
            StringCopy(status, taskFound->status);
            success = true;
        }
    }
    if (success)
    {
        printf("Task with id %lu updated\n", taskid);
        save_to_file(taskList, arrayLength);
    }
    else
    {
        printf("Task with id %lu not found\n", taskid);
    }
}

void task_list_tasks()
{
    if (taskList == NULL)
    {
        printf(":: Task List:\n");
        printf("No tasks found\n");
        return;
    }
    printf(":: Task List:\n");
    for (int i = 0; i < arrayLength; i++)
    {
        Task *task = &taskList[i];
        _task_print_tasks(task);
    }
}

void task_sort_by_status(const char *status)
{
    if (taskList == NULL)
    {
        printf("No tasks found\n");
        return;
    }
    int listLength = 0;
    for (int i = 0; i < arrayLength; i++)
    {
        Task *task = &taskList[i];
        if (compareStrings(task->status, status))
        {
            _task_print_tasks(task);
            listLength++;
        }
    }
    if (listLength == 0)
    {
        printf("No tasks found\n");
    }
}

void task_sort_task_by_completed()
{
    if (taskList == NULL)
    {
        printf(":: Completed Tasks:\n");
        printf("No tasks found\n");
        return;
    }
    printf(":: Completed Tasks:\n");
    int listLength = 0;
    for (int i = 0; i < arrayLength; i++)
    {
        Task *task = &taskList[i];
        if (compareStrings(task->status, "done"))
        {
            _task_print_tasks(task);
            listLength++;
        }
    }
    if (listLength == 0)
    {
        printf("No tasks found\n");
    }
}

void task_sort_task_by_in_progress()
{
    if (taskList == NULL)
    {
        printf(":: In Progress Tasks:\n");
        printf("No tasks found\n");
        return;
    }
    printf(":: In Progress Tasks:\n");
    int listLength = 0;
    for (int i = 0; i < arrayLength; i++)
    {
        Task *task = &taskList[i];
        if (compareStrings(task->status, "in-progress"))
        {
            _task_print_tasks(task);
            listLength++;
        }
    }
    if (listLength == 0)
    {
        printf("No tasks found\n");
    }
}

void task_sort_task_by_todo()
{
    if (taskList == NULL)
    {
        printf(":: To Do List:\n");
        printf("No tasks found\n");
        return;
    }
    printf(":: To Do List:\n");
    int listLength = 0;
    for (int i = 0; i < arrayLength; i++)
    {
        Task *task = &taskList[i];
        if (compareStrings(task->status, "todo"))
        {
            _task_print_tasks(task);
            listLength++;
        }
    }
    if (listLength == 0)
    {
        printf("No tasks found\n");
    }
}

void task_free_tasks()
{
    if (taskList == NULL)
        return;
    free(taskList);
}
