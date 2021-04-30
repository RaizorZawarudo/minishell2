/*
** EPITECH PROJECT, 2021
** B-PSU-101-BER-1-1-minishell1-mickael.riess
** File description:
** execute_command3
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
#include <signal.h>
#include "include/my.h"
#include "include/input_parser.h"
#include "include/execute_command.h"

void display_access_denied(char *command)
{
    my_putstr(command);
    my_putchar(':');
    my_putstr(" Permission denied.\n");
}

void exec_script(char **p_command, int path_exists, char **envp)
{
    pid_t pid;
    if (access(p_command[0], X_OK) == -1) {
        display_access_denied(p_command[0]);
        return;
    }
    else if (path_exists  == -1) {
        display_command_doesnt_exist(p_command[0]);
        return;
    }
    else {
        pid = fork();
        if (pid == 0)
            execve(p_command[0], p_command, envp);
        waitpid(pid, NULL, 0);
    }
}

void exec_prg(char *abs_path, char **p_command, int path_exists, char **envp)
{
    pid_t pid;

    if (access(p_command[0], X_OK) == -1) {
        display_access_denied(p_command[0]);
        return;
    }
    if (path_exists == -1) {
        display_command_doesnt_exist(p_command[0]);
        return;
    }
    else {
        pid = fork();
        if (pid == 0)
            execve(abs_path, p_command, envp);
        waitpid(pid, NULL, 0);
    }
}