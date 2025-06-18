#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "todo.h"

#define INPUT_SIZE 300

int main() {
    const char *filename = "tasks.enc";
    loadTasks(filename); // Load tasks from file at startup

    char input[INPUT_SIZE];

    printf("Welcome to TermiDo! - Your Terminal Based To-Do List\n");
    printf("Type 'help' for a list of commands.\n");

    while (1) {
        printf("> ");
        if (!fgets(input, sizeof(input), stdin)) break; // Handle EOF or read error
    
        // Remove newline character from input
        input[strcspn(input, "\n")] = '\0';

        if (strcmp(input, "help") == 0) {
            printf("Available commands:\n");
            printf("add <task description> - Add a new task\n");
            printf("list - List all tasks\n");
            printf("done <task index> - Mark a task as completed\n");
            printf("remove <task index> - Remove a task\n");
            printf("exit - Exit the application\n");
        } else if (strncmp(input, "add ", 4) == 0) {
            addTask(input + 4);
        } else if (strcmp(input, "list") == 0) {
            listTasks();
        } else if (strncmp(input, "done ", 5) == 0) {
            int index = atoi(input + 5);
            markTaskCompleted(index);
        } else if (strncmp(input, "remove ", 7) == 0) {
            int index = atoi(input + 7);
            removeTask(index);
        } else if (strcmp(input, "exit") == 0) {
            break;
        } else {
            printf("Unknown command: %s\n", input);
        }
    }

    // Save tasks to file before exiting
    saveTasks(filename);

    printf("Exiting TermiDo. Goodbye!\n");
    return 0;
}