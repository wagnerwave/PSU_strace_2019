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

static int get_status_signal(int status)
{
    int ret = ((WSTOPSIG(status) == SIGTRAP || WSTOPSIG(status) == SIGSTOP)
                && WIFSTOPPED(status));
    return ret;
}

int strace(pid_t child, size_t option)
{
    struct user_regs_struct regs = {0};
    long check_syscall;
    int status = 0;

    if (ptrace(PTRACE_SINGLESTEP, child, 0, 0) == -1)
        return 84;
    waitpid(child, &status, 0);
    while (get_status_signal(status)) {
        ptrace(PTRACE_GETREGS, child, NULL, &regs);
        check_syscall = ptrace(PTRACE_PEEKTEXT, child, regs.rip, 0);
        if ((check_syscall & 0xFFFF) == 0x050F)
            print_syscall_ft(child, regs, option);
        if (ptrace(PTRACE_SINGLESTEP, child, 0, 0) == -1)
            return 84;
        waitpid(child, &status, 0);
    }
    return status;
}