/*
** EPITECH PROJECT, 2020
** Alexandre Wagner - Théo Le bonniec
** File description:
** Main for Strace
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

/*
int do_trace(pid_t child)
{
    long test = 0;
    int status = 0;

    waitpid(child, &status, 0);
    ptrace(PTRACE_SINGLESTEP, child, 0, NULL);
    test = ptrace(PTRACE_GETREGS, child, 0, sizeof(long)*RAX);
    return 0;
}
*/

static int process_running(pid_t child)
{
    struct user_regs_struct register;
    long ret_value = 0;

    ret_value = ptrace(PTRACE_ATTACH, child, 0, 0);
    if (ret_value == -1)
        return print_error("Error: attach to running processus failed.\n");
    return (int)ret_value;
}

static int load_child(int ac, char **av)
{
    int var_check = 0;
    char *args[ac + 1];

    memcpy(args, av, ac * sizeof(char *));
    args[ac] = NULL;
    var_check = ptrace(PTRACE_TRACEME);
    if (var_check == -1)
        return print_error("Error: ptrace traceme failed.\n");
    var_check = kill(getpid(), SIGSTOP);
    if (var_check == -1)
        return print_error("Error: kill pid with sigstop failed.\n");
    var_check = execvp(args[0], args);
    if (var_check == -1)
        return print_error("Error: excution error.\n");
    return 0;
}

static int strace(pid_t child, size_t option)
{
    struct user_regs_struct register;
    int var_check = 0;
    int status = 0;
    int ret_value = 0;

    var_check = waitpid(child, &status, 0);
    if (var_check == -1)
        return print_error("Error: waitpid failed.\n");
    //while (get_signal_status(&status)) {

    //}
    return 0;
}

int main(int ac, char **av)
{
    pid_t child;
    size_t option = 0;

    if (ac < 2)
        return print_error("Usage: ./strace [-s] [-p <pid>|<commande>]\n");
    if (strcmp(av[1], "-s") == 0)
        option++;
    if (av[1 + option] && !strcmp(av[1 + option], "-p") && av[2 + option]) {
        child = atoi(av[2 + option]);
        if (process_running(child) == 84)
            return 84;
    } else {
        if (!av[1 + option])
            return print_error("Error: invalide option\n");
        child = fork();
        if (child == 0)
            return load_child(ac, av);
    }
    return exit_strace(strace(child, option), option);
}