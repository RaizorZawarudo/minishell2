/*
** EPITECH PROJECT, 2021
** B-PSU-101-BER-1-1-minishell1-mickael.riess
** File description:
** env
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "include/my.h"
#include "include/input_parser.h"
#include "include/execute_command.h"

void do_env(char **envp)
{
    for (int i = 0; envp[i]; i++) {
        my_putstr(envp[i]);
        my_putchar('\n');
    }
}

char *apply_setenv(char *arg1, char *arg2)
{
    int i = 0;
    char *ud_var = malloc(sizeof(char) *
    (my_strlen(arg1) + my_strlen(arg2) + 2));

    for (; arg1[i]; i++)
        ud_var[i] = arg1[i];
    ud_var[i] = '=';
    i++;
    if (arg2 != NULL) {
        for (int a = 0; arg2[a]; a++) {
            ud_var[i] = arg2[a];
            i++;
        }
    }
    ud_var[i] = '\0';
    return ud_var;
}

int setenv_special_cases(char **args, char **envp)
{
    if (!args[1]) {
        do_env(envp);
        return 1;
    }
    if (args[3] != NULL) {
        my_putstr("setenv : Too many arguments.\n");
        return 1;
    }
    else if (!my_str_isalphanumerical(args[1])) {
        my_putstr("setenv : Variable name must contain");
        my_putstr(" alphanumeric characters.\n");
        return 1;
    }
    else if ((args[1][0] < 'A' || args[1][0] > 'Z')
            && (args[1][0] < 'a' || args[1][0] > 'z')) {
            my_putstr("setenv : Variable name must begin with a letter.\n");
            return 1;
            }
    return 0;
}

char **add_line_to_env(char **args, char **envp)
{
    int i = 0;
    int e_size = 0;
    char **set_env = NULL;
    char *new_variable = apply_setenv(args[1], args[2]);

    for (; envp[e_size]; e_size++);
    set_env = malloc(sizeof(char *) * (e_size + 2));
    for (i = 0; envp[i]; i++)
        set_env[i] = envp[i];
    set_env[i] = new_variable;
    set_env[i + 1] = NULL;
    return set_env;
}

char **do_setenv(char **args, char **envp)
{
    char **new_envp = duplicate_env(envp);

    if (setenv_special_cases(args, envp))
        return envp;
    for (int i = 0; envp[i]; i++) {
        if (!my_strncmp(args[1], new_envp[i], my_strlen(args[1]))) {
            new_envp[i] = apply_setenv(args[1], args[2]);
            return new_envp;
        }
    }
    new_envp = add_line_to_env(args, envp);
    return new_envp;
}