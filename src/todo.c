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
    FILE *fp = fopen(filename, "wb");
    if (!fp) {
        perror("Failed to save tasks");
        return;
    }

    char buffer[8192] = "";  // big enough for all tasks
    char line[512];

    for (int i = 0; i < taskCount; i++) {
        snprintf(line, sizeof(line), "%s|%d\n", taskList[i].description, taskList[i].completed);
        strncat(buffer, line, sizeof(buffer) - strlen(buffer) - 1);
    }

    size_t bufferLength = strlen(buffer);
    xorEncryptDecrypt(buffer, "supersecret", bufferLength);
    fwrite(buffer, 1, bufferLength, fp);

    fclose(fp);
    printf("Tasks encrypted and saved to '%s'\n", filename);
}


void loadTasks(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (!fp) return;

    char buffer[8192];
    size_t bytesRead = fread(buffer, 1, sizeof(buffer) - 1, fp);
    fclose(fp);

    buffer[bytesRead] = '\0';  // null-terminate
    xorEncryptDecrypt(buffer, "supersecret", bytesRead);

    // Now parse buffer line-by-line
    char *line = strtok(buffer, "\n");
    while (line != NULL && taskCount < MAX_TASKS) {
        char desc[256];
        int done;
        if (sscanf(line, "%255[^|]|%d", desc, &done) == 2) {
            strncpy(taskList[taskCount].description, desc, sizeof(taskList[taskCount].description) - 1);
            taskList[taskCount].description[sizeof(taskList[taskCount].description) - 1] = '\0';
            taskList[taskCount].completed = done;
            taskCount++;
        }
        line = strtok(NULL, "\n");
    }

    printf("Loaded %d task(s) from '%s'\n", taskCount, filename);
}
