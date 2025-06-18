#include <stdio.h>
#include "todo.h"

int main() {
    printf("Welcome to TermiDo!\n");

    addTask("Learn C programming");
    addTask("Implement a simple TODO app");
    listTasks();

    return 0;
}