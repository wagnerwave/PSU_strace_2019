/*
** EPITECH PROJECT, 2020
** Alexandre Wagner - Théo Le bonniec
** File description:
** all function for ptrace
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

int process_running(pid_t child)
{
    struct user_regs_struct register;
    long ret_value = 0;

    ret_value = ptrace(PTRACE_ATTACH, child);
    if (ret_value == -1)
        return print_error("Error: attach to running processus failed.\n");
    return (int)ret_value;
}

int load_child(int ac, char **av)
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

static int waitchild(pid_t pid)
{
    int status;

    waitpid(pid, &status, 0);
    if (WIFSTOPPED(status)) {
        return 0;
    } else if (WIFEXITED(status)) {
        return 1;
    } else {
        printf("%d raised an unexpected status %d", pid, status);
        return 1;
    }
}

int strace(pid_t child, size_t option)
{
    struct user_regs_struct regs;
    //CREE LA VARIABLE DE LA STRUCTURE DE PERSON

    while (waitchild(child) < 1) {
        ptrace(PTRACE_GETREGS, child, NULL, &regs);
        //if (STRUCT2PERSON = FUNCTION QUI REMPLI LA STRUCTURE(regs.orig_rax) /* sheach syscall */) {
        //    ptrace(PTRACE_SINGLESTEP, child);
        //     FUNCTION QUI PRINT TOUT BIEN AVEC LA STRUCTURE EN PARAMETRE
        //}
    }
    return 0;
}

i