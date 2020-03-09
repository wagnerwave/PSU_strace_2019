/*
** EPITECH PROJECT, 2020
** Alexandre Wagner - Théo Le bonniec
** File description:
** main de test unitaire
*/

#include <unistd.h>
#include <string.h>
#include <criterion/criterion.h>
#include <criterion/redirect.h>

char *str = NULL;

void print(int fd, const char *str)
{
    write(fd, str, strlen(str));
}

Test(printer, print_stderr)
{
    cr_redirect_stderr();
    print(STDERR_FILENO, "Usage: ./strace [-s] [-p <pid>|<command>]");
    cr_assert_stderr_eq_str("Usage: ./strace [-s] [-p <pid>|<command>]");
}