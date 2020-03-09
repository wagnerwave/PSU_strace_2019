/*
** EPITECH PROJECT, 2020
** Alexandre Wagner - Théo Le bonniec
** File description:
** Main for Strace
*/

#include <stdio.h>

int main(int ac, char **av)
{
    pid_t child;
    int action = 0;

    if (ac < 2)
        perror("Usage: ./strace [-s] [-p <pid>|<command>]");
    return 0;
}