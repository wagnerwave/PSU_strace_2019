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

static void error(int ac, char **av)
{
    if (ac != 2 && ac != 3) {
        printf("Usage: ./strace [-s] [-p <pid>|<commande>]\n");
        exit(84);
    }
    if (ac == 3 && (strcmp(av[1], "-s") != 0 && strcmp(av[1], "-p") != 0)){
        printf("strace: Can't stat '%s': No such file or directory\n", av[1]);
        exit(84);
    }
}

int main(int ac, char **av)
{
    pid_t child;
    size_t option = 0;
    int flag = 0;

    error(ac, av);
    if (ac == 3 && strcmp(av[1], "-p") == 0) {
        child = atoi(av[2]);
        return (process_running(child));
    }
    if (ac == 3 && strcmp(av[1], "-s") == 0) {
        option = 1;
    }
    child = fork();
    if (child == 0)
        return load_child(ac, av, option);
    waitpid(child, &flag, 0);
    return exit_strace(strace(child, option), option);
}