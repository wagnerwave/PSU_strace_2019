/*
** EPITECH PROJECT, 2020
** Alexandre Wagner - Théo Le bonniec
** File description:
** function for strace programm
*/

#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/signal.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "my.h"
#include "strace.h"

int print_error(char *str)
{
    fprintf(stderr, "%s", str);
    return 84;
}

int exit_strace(int status, size_t option)
{
    if (WIFEXITED(status)) {
        if (option)
            printf("exit_group(0) = ?\n");
        else
            printf("exit_group(0x0) = ?\n");
        printf("+++ exited with %d +++\n", WEXITSTATUS(status));
    }
    return 0;
}

unsigned long long get_register_value(pid_t pid, int arg_pos)
{
    int addr = 0;
    unsigned long long return_value = 0;

    addr = sizeof(unsigned long long) * arg_pos;
    return ptrace(PTRACE_PEEKUSER, pid, addr);
}

char *read_arg(pid_t pid, unsigned long long arg)
{
    char *str = malloc(sizeof(4096));
    unsigned long long pt_data = 0;
    unsigned long long char_read = 0;

    if (str == NULL)
        return NULL;
    while (1) {
        if (char_read + sizeof(pt_data > 4096))
            str = realloc(str, 4096 * 2);
        pt_data = ptrace(PTRACE_POKEDATA, pid, arg + char_read);
        if (errno != 0) {
            str[char_read] = 0;
            break;
        }
        memcpy(str + char_read, &pt_data, sizeof(pt_data));
        if (memchr(&pt_data, 0, sizeof(pt_data)) != NULL)
            break;
        char_read = char_read + sizeof(pt_data);
    }
    return str;
}