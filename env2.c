/*
** EPITECH PROJECT, 2021
** B-PSU-101-BER-1-1-minishell1-mickael.riess
** File description:
** env2
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "include/my.h"
#include "include/input_parser.h"
#include "include/execute_command.h"

char **duplicate_env(char **og_envp)
{
    int i = 0;
    int e_size = 0;
    char **dup_env = NULL;

    for (; og_envp[e_size]; e_size++);
    dup_env = malloc(sizeof(char *) * (e_size + 1));
    for (; og_envp[i]; i++)
        dup_env[i] = og_envp[i];
    dup_env[i] = NULL;

    return dup_env;
}

char **generate_smaller_env(char **og_envp, int i)
{
    int j = 0;
    int a = 0;
    int e_size = 0;
    char **dup_env = NULL;

    for (; og_envp[e_size]; e_size++);
    dup_env = malloc(sizeof(char *) * (e_size + 1));
    for (; og_envp[j]; j++) {
        if (j != i) {
        dup_env[a] = og_envp[j];
        a++;
        }
    }
    dup_env[a] = NULL;
    return dup_env;
}

char **do_unsetenv(char **args, char **envp)
{
    char **new_envp;
    
    for (int i = 0; envp[i]; i++) {
        if (!my_strncmp(args[1], envp[i], my_strlen(args[1]))) {
            new_envp = generate_smaller_env(envp, i);
            return new_envp;
        }
    }
    return envp;
}