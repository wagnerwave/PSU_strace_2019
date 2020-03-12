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
#include <ctype.h>
#include "my.h"
#include "strace.h"

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

static void print_argument(pid_t pid, unsigned long long arg,
size_t option, enum e_type type)
{
    char *str = NULL;

    if (option && type == T_INTEGER) {
        printf("%lld", arg);
    } else if (option && type == T_STRING) {
        str = read_arg(pid, arg);
        printf("\"");
        for (size_t i = 0; str[i] && i < MAX_LENGTH_ARG; i++) {
            isprint(str[i]) ? printf("%c", str[i]) : printf("\\%o", str[i]);
            i >= MAX_LENGTH_ARG ? printf("\"...") : printf("\"");
            free(str);
        }
    } else {
        if (arg)
            printf("0x%llx", arg);
        else
            (option) ? printf("NULL") : printf("0x0");
    }
}

static void print_argument_function(pid_t pid, s_syscall_t *temp, size_t option)
{
    unsigned long long arg = 0;
    enum e_type type;

    for (size_t i = 0; i < temp->argc; i++) {
        arg = get_register_value(pid, i);
        type = temp->args[i].printer.type;
        print_argument(pid, arg, option, type);
        if (i + 1 != temp->argc - 1)
            printf(", ");
    }
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
    int syscall_nb = regs.rax;
    int ret_value = regs.rax;
    s_syscall_t *temp = NULL;

    temp = get_syscall_by_value(syscall_nb);
    if (temp == NULL) {
        exit(84);
    }
    printf("%s(", temp->name);
    print_argument_function(child, temp, option);
    printf(") = ");
    print_return_value(ret_value, temp, option);
}