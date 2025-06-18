#include <stdio.h>
#include "todo.h"

int main() {
    printf("Welcome to TermiDo!\n");
    addTask("Learn C programming");
    addTask("Implement a simple TODO app");
    listTasks();

    addTask("Test the TODO app functionality");
    addTask("Write documentation");
    listTasks();

    markTaskCompleted(0);
    listTasks();

    removeTask(1);
    listTasks();

    return 0;
}