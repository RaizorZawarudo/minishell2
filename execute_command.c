/*
** EPITECH PROJECT, 2021
** B-PSU-101-BER-1-1-minishell1-mickael.riess
** File description:
** execute_command
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include "include/my.h"
#include "include/input_parser.h"
#include "include/execute_command.h"

void display_command_doesnt_exist(char *command)
{
    my_putstr(command);
    my_putchar(':');
    my_putstr(" Command not found.\n");
}

void execute_binary(char **p_command, char **envp)
{
    char *abs_path = NULL;
    char *new_binary = p_command[0];
    struct stat stats;
    int path_exists = stat(p_command[0], &stats);

    if (new_binary[0] == '.')
        new_binary = &new_binary[1];
    abs_path = getcwd(abs_path, 0);
    abs_path = my_stringbinder(abs_path, new_binary);
    if (p_command[0][0] == '/')
        exec_script(p_command, path_exists, envp);
    else
        exec_prg(abs_path, p_command, path_exists, envp);
}

char **check_custom_commands(char **args, char **envp)
{
    char **new_envp = NULL;

    if (!my_strcmp(args[0], "env")){
        do_env(envp);
        return envp;
    }
    if (!my_strcmp(args[0], "setenv"))
        new_envp = do_setenv(args, envp);
    if (!my_strcmp(args[0], "unsetenv"))
        new_envp = do_unsetenv(args, envp);
    if (!my_strcmp(args[0], "cd"))
        new_envp = do_chdir(args, envp);
    else if (!my_strcmp(args[0], "exit")) {
        my_putstr("exit");
        exit(0);
    }
    return new_envp;
}

char **execute_command(char **args, char **envp)
{
    char **new_envp = NULL;
    char **paths = NULL;
    char *fc = NULL;
    pid_t pid;

    if ((new_envp = check_custom_commands(args, envp)) != NULL)
        return new_envp;
    paths = find_executable_paths(envp);
    fc = find_cmd_in_paths(paths, args[0]);
    if (fc == NULL)
        display_command_doesnt_exist(args[0]);
    else if (fc != NULL) {
        (pid = (fork() == 0)) ? execve(fc, args, envp) : waitpid(pid, NULL, 0);
    }

    return envp;
}

char **execute_input(char **p_command, char **envp)
{
    char **return_env = NULL;

    if (p_command[0][0] == '.' || p_command[0][0] == '/') {
        execute_binary(p_command, envp);
        return_env = duplicate_env(envp);
    }
    else
        return_env = execute_command(p_command, envp);
    return return_env;
}