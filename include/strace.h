/*
** EPITECH PROJECT, 2020
** Alexandre Wagner - Théo Le bonniec
** File description:
** strace header
*/

#ifndef STRACE_H_
#define STRACE_H_

#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>

#define STRACE_SYSCALL_ARGS_MAX 6

typedef int (*t_printer)(unsigned long long int,
			 pid_t,
			 const struct user_regs_struct *,
			 const struct s_strace_opts *);

enum e_type
  {
    T_DEFAULT,
    T_INTEGER,
    T_POINTER,
    T_STRING,
    T_LONG,
    T_ULONG,
    T_SIZE_T,
    T_SSIZE_T,
  };

struct s_syscall_arg
{
  bool	custom;
  union
  {
    enum e_type	type;
    t_printer	callback;
  }	printer;
};

struct s_syscall
{
  unsigned long long	id;
  const char		*name;
  bool			noreturn;
  enum e_type		retval;
  size_t		argc;
  struct s_syscall_arg	args[STRACE_SYSCALL_ARGS_MAX];
};


#endif /* !STRACE_H_ */
