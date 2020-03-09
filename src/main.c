/*
** EPITECH PROJECT, 2020
** Alexandre Wagner - Théo Le bonniec
** File description:
** Main for Strace
*/

#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

static int print_error(char *str)
{
    write(2, str, strlen(str));
    return 84;
}

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

if (child == 0) {
        return do_child(av[1]);
    } else {
        return do_trace(child);
    }
    exit(0);

int do_child(char *cmd, char **envp)
{
    char *str = strcat("bin/", cmd);
    ptrace(PTRACE_TRACEME);
    execve(str, cmd,envp);
    return 0;
}*/

static int procress_running(pid_t child)
{
    return 0;
}

static int load_child(int ac, char **av, size_t option)
{
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
        if (procress_running(child) == 84)
            return 84;
    } else {
        if (!av[1 + option])
            return print_error("Error: invalide option\n");
        child = fork();
        if (child == 0)
            return (load_child(ac, av, option));
    }
    return 0;
}
