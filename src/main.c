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

static int print_error(char const *str)
{
    perror(str);
    return 84;
}

int do_trace(pid_t child)
{
    long test = 0;
    int status = 0;

    waitpid(child, &status, 0);
    ptrace(PTRACE_SINGLESTEP, child, 0, NULL);
    test = ptrace(PTRACE_GETREGS, child, 0, sizeof(long)*RAX);
    return 0;
}

int do_child(char *cmd, char **envp)
{
    char *str = strcat("bin/", cmd);
    ptrace(PTRACE_TRACEME);
    execve(str, cmd,envp);
    return 0;
}

int main(int ac, char **av)
{
    pid_t child = fork();
    int count = 0;

    if (av < 2)
        return print_error("Usage: ./strace [-s] [-p <pid>|<commande>]\n");
    if (strcmp(av[1], "-s") == 0)
        count++;
    //if (av[1 + count] && strcmp(av[1 + cout], "-p") == 0 && av[2 + count])
     //   
    /*if (child == 0) {
        return do_child(av[1]);
    } else {
        return do_trace(child);
    }
    exit(0);*/
    return 0;
