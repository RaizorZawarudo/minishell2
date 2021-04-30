/*
** EPITECH PROJECT, 2021
** B-PSU-101-BER-1-1-minishell1-mickael.riess
** File description:
** execute_command2
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include "include/my.h"
#include "include/input_parser.h"
#include "include/execute_command.h"

char *concat_paths(char *str1, char *str2)
{
    int counter = 0;
    int size1 = my_strlen(str1);
    int size2 = my_strlen(str2);
    char *returnstring = malloc(sizeof(char) * (size1 + size2 + 1));

    for (; str1[counter]; counter++)
        returnstring[counter] = str1[counter];
    returnstring[counter] = '/';
    counter++;
    for (int i = 0; str2[i]; i++) {
        returnstring[counter] = str2[i];
        counter++;
    }
    returnstring[counter] = '\0';
    return returnstring;
}

char *find_cmd_in_paths(char **paths, char *command)
{
    char *final_path = NULL;
    struct stat stats;
    int path_exists = 0;

    for (int i = 0; paths[i]; i++) {
        path_exists = stat(paths[i], &stats);
        if (S_ISDIR(stats.st_mode) && path_exists != -1) {
            if (we_found_cmd(paths[i], command)) {
                final_path = concat_paths(paths[i], command);
                break;
            }
        }
    }
    return final_path;
}

int we_found_cmd(char *path, char *command)
{
    DIR *dir;
    struct dirent *dp;

    dir = opendir(path);
    while ((dp = readdir(dir))) {
        if (!my_strcmp(dp->d_name, command)) {
            return 1;
        }
    }
    return 0;
}

char **find_executable_paths(char **envp)
{
    char **path_array = NULL;
    char *token = NULL;
    char *rest = NULL;
    int a = 0;

    for (int i = 0; envp[i]; i++) {
        if (!my_strncmp(envp[i], "PATH", 4)) {
            path_array = malloc(sizeof(char *) * my_strlen(envp[i]));
            rest = my_strdup(envp[i]);
            token = strtok_r(rest, "=", &rest);
            for (; (token = strtok_r(rest, ":", &rest)); a++)
                path_array[a] = my_strdup(token);
            path_array[a] = NULL;
        }
    }
    return path_array;
}