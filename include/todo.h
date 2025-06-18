#ifndef TODO_H
#define TODO_H

#define MAX_TASKS 100

typedef struct {
    char description[256];
    int completed; // 0 = not completed, 1 = completed
} Task;

void addTask(const char *desc);

void listTasks(void);

void markTaskCompleted(int index);

void removeTask(int index);

void saveTasks(const char *filename);

void loadTasks(const char *filename);

#endif