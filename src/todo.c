#include <stdio.h>
#include <string.h>
#include "todo.h"
#include "crypto.h"

static Task taskList[MAX_TASKS];
static int taskCount = 0;

void addTask(const char *desc) {
    if (taskCount >= MAX_TASKS) {
        printf("Task list is full!\n");
        return;
    }

    // Check if the description is too long
    strncpy(taskList[taskCount].description, desc, sizeof(taskList[taskCount].description) - 1);
    
    // Ensure null termination
    taskList[taskCount].description[sizeof(taskList[taskCount].description) - 1] = '\0'; // Ensure null termination
    
    // Initialize the task as not completed
    taskList[taskCount].completed = 0; 

    // Increment the task count
    taskCount++;

    printf("Task added: %s\n", desc);
}

void listTasks(void) {
    // Check if there are any tasks to list
    if (taskCount == 0) {
        printf("No tasks found.\n");
        return;
    }
    
    // Print the list of tasks
    printf("Tasks:\n");
    for (int i = 0; i < taskCount; i++) {
       printf("[%c] Task Item %i: %s\n", 
              taskList[i].completed ? 'X' : ' ', 
              i,
              taskList[i].description);
    }
    printf("Total tasks: %d\n", taskCount);
}

void markTaskCompleted(int index) {
    // Check if the index is valid
    if (index < 0 || index >= taskCount) {
        printf("Invalid task index.\n");
        return;
    }

    // Mark the task as completed
    taskList[index].completed = 1;
    printf("Task %d marked as completed.\n", index);
}

void removeTask(int index) {
    // Check if the index is valid
    if (index < 0 || index >= taskCount) {
        printf("Invalid task index.\n");
        return;
    }

    // Shift tasks to remove the specified task
    for (int i = index; i < taskCount - 1; i++) {
        taskList[i] = taskList[i + 1];
    }

    // Decrement the task count
    taskCount--;

    printf("Task %d removed.\n", index);
}

void saveTasks(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file for saving tasks.\n");
        return;
    }

    char buffer[512];
    for (int i = 0; i < taskCount; i++) {
        // Prepare the task description and completion status for saving
        snprintf(buffer, sizeof(buffer), "%s|%d\n", taskList[i].description, taskList[i].completed);
        xorEncryptDecrypt(buffer, "supersecret", strlen(buffer)); // Encrypt the task data
        fwrite(buffer, sizeof(char), strlen(buffer), file);
    }

    fclose(file);
    printf("Tasks saved to %s.\n", filename);
}

void loadTasks(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) return; // If the file doesn't exist, we simply return

    char line[512];
    while (fgets(line, sizeof(line), file)) {
        xorEncryptDecrypt(line, "supersecret", strlen(line)); // Decrypt the task data
        int done;
        char description[256];
        if (sscanf(line, "%255[^|]|%d", description, &done) == 2) {
            if (taskCount < MAX_TASKS) {
                strcpy(taskList[taskCount].description, description);
                taskList[taskCount].description[sizeof(taskList[taskCount].description) - 1] = '\0'; // Ensure null termination
                taskList[taskCount].completed = done;
                taskCount++;
            }
        }
    }
    fclose(file);
    printf("Tasks loaded from %s.\n", filename);
}   