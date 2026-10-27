#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "FileUtility.h"
#include "Tasks.h"
#include "String/String.h"

char *version = "v3.8";

void _main_add_Option(const char *description)
{
    Task task = {lastIdentifier + 1};
    time_t currentTime;
    time(&currentTime);
    StringCopy(RemoveTrailingNewLine(ctime(&currentTime)), task.createdAt);
    const unsigned int descLength = stringLength(description);
    if (descLength > 60)
    {
        printf("Description is too long! Counted %d chars, should be less than 60 characters.\n", descLength);
        return;
    }
    StringCopy(description, task.description);
    const char *status = "todo";
    StringCopy(status, task.status);
    task_add_task(&task, true);
    printf("Task added successfully (ID %lu)\n", task.id);
}

void _main_help()
{
    printf("Usage: [OPTION] <description/id>\n");
    printf("\nOptions:\n");
    printf("add <description>\n");
    printf("delete <id>\n");
    printf("update <id> <description>\n");
    printf("mark-todo <id>\n");
    printf("mark-in-progress <id>\n");
    printf("mark-done <id>\n");
    printf("list <todo, in-progress, done>\n");
    printf("\nUsage: [OPTION]\n");
    printf("sort-completed -> Sort by completed\n");
    printf("sort-incomplete -> Sort by incomplete or in-progress\n");
    printf("list -> List all tasks\n");
    printf("size -> Get number of tasks\n");
    printf("version -> print version\n");
    printf("help -> print this menu\n");
}

int main(int argc, char *argv[])
{
    if (argc > 1)
    {
        prepare_directory();
        load_from_file();
        if (argc == 3)
        {
            if (compareStrings(argv[1], "add"))
            {
                _main_add_Option(argv[2]);
            }
            if (compareStrings(argv[1], "delete"))
            {
                const int intValue = atoi(argv[2]);
                task_remove_task(intValue);
            }
            if (compareStrings(argv[1], "list"))
            {
                int statusValue = atoi(argv[2]);
                if (compareStrings(argv[2], "todo"))
                {
                    statusValue = 4;
                    task_sort_by_status("todo");
                }
                if (compareStrings(argv[2], "in-progress"))
                {
                    statusValue = 4;
                    task_sort_by_status("in-progress");
                }
                if (compareStrings(argv[2], "done"))
                {
                    statusValue = 4;
                    task_sort_by_status("done");
                }
                if (compareStrings(argv[2], "hold"))
                {
                    statusValue = 4;
                    task_sort_by_status("hold");
                }
                switch (statusValue)
                {
                case 0:
                    task_sort_by_status("todo");
                    break;
                case 1:
                    task_sort_by_status("in-progress");
                    break;
                case 2:
                    task_sort_by_status("done");
                    break;
                case 3:
                    task_sort_by_status("hold");
                    break;
                }
            }
            if (compareStrings(argv[1], "mark-todo"))
            {
                const int intValue = atoi(argv[2]);
                task_mark_task_status(intValue, "todo");
            }
            if (compareStrings(argv[1], "mark-in-progress"))
            {
                const int intValue = atoi(argv[2]);
                task_mark_task_status(intValue, "in-progress");
            }
            if (compareStrings(argv[1], "mark-done"))
            {
                const int intValue = atoi(argv[2]);
                task_mark_task_status(intValue, "done");
            }
            if (compareStrings(argv[1], "mark-hold"))
            {
                const int intValue = atoi(argv[2]);
                task_mark_task_status(intValue, "hold");
            }
        }

        if (argc == 4)
        {
            if (compareStrings(argv[1], "update"))
            {
                int intValue = atoi(argv[2]);
                task_update_task(intValue, argv[3]);
            }
            if (compareStrings(argv[1], "mark"))
            {
                int statusValue = atoi(argv[2]);
                int intValue = atoi(argv[3]);
                switch (statusValue)
                {
                case 1:
                    task_mark_task_status(intValue, "in-progress");
                    break;
                case 2:
                    task_mark_task_status(intValue, "done");
                    break;
                case 3:
                    task_mark_task_status(intValue, "hold");
                    break;
                default:
                    task_mark_task_status(intValue, "todo");
                    break;
                }
            }
        }

        if (argc == 2)
        {
            if (compareStrings(argv[1], "list"))
            {
                task_list_tasks();
            }

            if (compareStrings(argv[1], "size"))
            {
                printf("%d\n", arrayLength);
            }

            if (compareStrings(argv[1], "sort-completed"))
            {
                task_sort_task_by_completed();
            }

            if (compareStrings(argv[1], "sort-incomplete"))
            {
                task_sort_task_by_in_progress();
            }

            if (compareStrings(argv[1], "help"))
            {
                _main_help();
            }
            if (compareStrings(argv[1], "version"))
            {
                printf("%s\n", version);
            }
        }
        task_free_tasks();
    }
    else
    {
        _main_help();
    }
    return 0;
}
