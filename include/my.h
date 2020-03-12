/*
** EPITECH PROJECT, 2020
** Alexandre Wagner - Théo Le bonniec
** File description:
** my.h
*/

#ifndef MY_H_
#define MY_H_

#define MAX_LENGTH_ARG 32

pid_t strace(pid_t child, size_t option);
int print_error(char *str);
int exit_strace(int value_status, size_t option);
int process_running(pid_t child);
int load_child(int ac, char **av);
unsigned long long get_register_value(pid_t pid, int arg_pos);
char *read_arg(pid_t pid, unsigned long long arg);
void print_syscall_ft(pid_t pid, struct user_regs_struct regs, size_t option);


#endif /* !MY_H_ */
