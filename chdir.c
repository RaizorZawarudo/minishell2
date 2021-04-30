/*
** EPITECH PROJECT, 2021
** B-PSU-210-BER-2-1-minishell2-mickael.riess
** File description:
** chdir
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "include/my.h"
#include "include/input_parser.h"
#include "include/execute_command.h"

char  **update_env_dir(char **envp, char *oldwd)
{
    for (int i = 0; envp[i]; i++) {
        if (!my_strncmp("OLDPWD=", envp[i], my_strlen("OLDPWD="))) {
            envp[i] = apply_setenv("OLDPWD", oldwd);
            return envp;
        }
    }
    return envp;
}

char *home_path_string_create(int pre, char *uncut_path)
{
    int a = 0;
    char *home_path_cut = malloc(sizeof(char) * (my_strlen(uncut_path) - pre));

    for (int i = pre; uncut_path[i]; i++) {
        home_path_cut[a] = uncut_path[i];
        a++;
    }
    home_path_cut[a] = '\0';

    return home_path_cut;
}

char *get_home_path(char **envp)
{
    for (int i = 0; envp[i]; i++) {
        if (!my_strncmp("HOME=", envp[i], my_strlen("HOME="))) {
            return home_path_string_create(5, envp[i]);
        }
    }
    return (getcwd(NULL, 0));
}

void print_no_such(char *arg)
{
    my_putstr("cd: No such file or directory :");
    my_putstr(arg);
    my_putchar('\n');
}

char **do_chdir(char **args, char **envp)
{
    char *oldwd;

    if (!args[1]) {
        oldwd = getcwd(NULL, 0);
        chdir(get_home_path(envp));
        envp = update_env_dir(envp, oldwd);
    }
    if (args[1]) {
        oldwd = getcwd(NULL, 0);
        if (chdir(args[1])== -1)
            print_no_such(args[1]);
        envp = update_env_dir(envp, oldwd);
    }
    return envp;
}