/*
** EPITECH PROJECT, 2020
** Alexandre Wagner - Théo Le bonniec
** File description:
** All print function for strace
*/

#include <stdio.h>
#include <sys/wait.h>

int print_error(char *str)
{
    perror(str);
    return 84;
}

int exit_strace(int value_status, size_t option)
{
    if (WIFEXITED(value_status)) {
        printf("+++ exited with %d +++\n", WEXITSTATUS(value_status));
        return 0;
    }
    return 84;
}