/*
** EPITECH PROJECT, 2020
** Alexandre Wagner - Théo Le bonniec
** File description:
** function for option -s and -p
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

int process_running(pid_t child)
{
    struct user_regs_struct register;
    long ret_value = 0;

    ret_value = ptrace(PTRACE_ATTACH, child);
    if (ret_value == -1)
        return 84;
    return 0;
}

int load_child(int ac, char **av, size_t option)
{
    int var_check = 0;

    var_check = ptrace(PTRACE_TRACEME, 0, 0, 0);
    if (var_check == -1)
        return 84;
    var_check = kill(getpid(), SIGSTOP);
    if (var_check == -1)
        return 84;
    var_check = execvp(av[1 + option], &av[1 + option]);
    if (var_check == -1)
        return 84;
    return 0;
}