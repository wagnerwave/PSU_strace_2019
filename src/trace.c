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
#include "../include/strace.h"
#include "syscalls.c"

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

static int strace_syscall_get_by_id(unsigned long long id, struct s_syscall *scallp)
{
    size_t	i;

    i = 0;
    while (g_syscalls[i].name != NULL)
    {
        if (g_syscalls[i].id == id)
        {
            *scallp = g_syscalls[i];
            return (0);
        }
        i++;
    }
    return (-1);
}

/*
// methode 2
void syscall_value(int id, my_struct_s temp)
{
    int i = 0;

    while (g_syscalls[i].name){
        if (g_syscalls[i].id == id) {
            temp.id = g_syscalls[i].id;
            temp.name = g_syscalls[i].name;
            temp.argc = g_syscalls[i].argc;
            temp.noreturn = g_syscalls[i].noreturn;
            temp.retval = g_syscalls[i].retval;
            //*temp = temp;
            printf("id = %lld\n", temp.id);
            //printf("%d\n", temp.retval);
            //printf("%d\n", temp.noreturn);
            printf("argc = %zu\n", temp.argc);
            printf("name = %s\n", temp.name);
            return;
        }
        printf("toto");
        i++;
    }
}*/

// methode 1
s_syscall_t *get_syscall_by_value(int id)
{
    int i = 0;

    while (g_syscalls[i].name) {
        if (g_syscalls[i].id == id)
            return (&g_syscalls[i]);
        i++;
    }
    return NULL;
}

int strace(pid_t child, size_t option)
{
    struct user_regs_struct regs;
    s_syscall_t *temp = NULL;

    while (waitchild(child) < 1) {
        ptrace(PTRACE_GETREGS, child, NULL, &regs);
        temp = get_syscall_by_value(regs.orig_rax);
        printf("testuuu = %s\n", temp->name);
        //    ptrace(PTRACE_SINGLESTEP, child);
        //     FUNCTION QUI PRINT TOUT BIEN AVEC LA STRUCTURE EN PARAMETRE
        //}
    }
    return 0;
}