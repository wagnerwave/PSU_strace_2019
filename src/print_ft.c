/*
** EPITECH PROJECT, 2020
** Alexandre Wagner - Théo Le bonniec
** File description:
** All print function for strace
*/

#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/signal.h>
#include <sys/user.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include "my.h"
#include "strace.h"

int print_error(char *str)
{
    perror(str);
    return 84;
}

int exit_strace(int value_status, size_t option)
{
    option = 0;
    if (WIFEXITED(value_status)) {
        printf("+++ exited with %d +++\n", WEXITSTATUS(value_status));
        return 0;
    }
    return 84;
}

static s_syscall_t *get_syscall_by_value(int id)
{
    int i = 0;

    while (g_syscalls[i].name) {
        if (g_syscalls[i].id == id)
            return (&g_syscalls[i]);
        i++;
    }
    return NULL;
}

static void print_arguement_function(struct user_regs_struct regs)
{
};

static void print_return_value(unsigned long long ret_value, s_syscall_t *temp, size_t option)
{
    if (option) {
        if (temp->retval == T_INTEGER)
            printf("%lld\n", ret_value);
        else
            printf("0x%llx\n", ret_value);
    } else {
        if (ret_value)
            printf("0x%llx\n", ret_value);
        else
            printf("0x0\n");
    }
}

void print_syscall_ft(pid_t child, struct user_regs_struct regs, size_t option)
{
    int syscall_nb = regs.orig_rax;
    int ret_value = regs.rax;
    s_syscall_t *temp = NULL;

    temp = get_syscall_by_value(syscall_nb);
    printf("%s(", temp->name);
    print_argument_function(regs);
    printf(") = ");
    print_return_value(ret_value, temp, option);
}