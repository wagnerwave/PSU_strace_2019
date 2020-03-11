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
#include <stdlib.h>

#define NO_FLAG 0
#define P_FLAG 1
#define S_FLAG -1

static int process_running(pid_t child)
{
    struct user_regs_struct register;
    long ret_value = 0;

    ret_value = ptrace(PTRACE_ATTACH, child);
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
    var_check = execvp(args[2], args);
    if (var_check == -1)
        return print_error("Error: excution error.\n");
    return 0;
}


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
static int parsing(int ac, char **av)
{
    error(ac, av);
    if (ac == 2)
        return (NO_FLAG);
    if (ac == 3 && strcmp(av[1], "-s") == 0)
        return (S_FLAG);
    if (ac == 3 && strcmp(av[1], "-p") == 0)
        return (P_FLAG);
}

int main(int ac, char **av)
{
    pid_t child;
    pid_t pid_arg; // le pid donné en argument
    size_t option = 0;
    int flag;

    flag = parsing(ac, av);
    if (flag == P_FLAG || flag == S_FLAG)
        pid_arg = atoi(av[2]);
    if (flag == NO_FLAG)
        pid_arg = atoi(av[1]);
    return (process_running(pid_arg));
    child = fork();
    if (child == 0)
        return (load_child(ac, av));

    return exit_strace(strace(child, option), option);
}