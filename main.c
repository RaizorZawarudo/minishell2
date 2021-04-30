/*
** EPITECH PROJECT, 2021
** B-PSU-101-BER-1-1-minishell1-mickael.riess
** File description:
** main
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "include/my.h"
#include "include/input_parser.h"
#include "include/execute_command.h"

void print_arg(char **arg)
{
    while (*arg) {
        my_putstr(*arg);
        my_putchar('n');
        arg++;
    }
}

void avoid_seggy(int line_size)
{
    if (!((line_size - 1) % 2))
        my_putstr(": Command not found.\n");
    else if ((line_size - 1) % 2)
        my_putstr("Unmatched '\"'.\n");
}

int is_seggy(char *line)
{
    for (int i = 0; i < my_strlen(line) - 1; i++) {
        if (line[i] != '\"' && line[1] != '\n')
            return 0;
    }
    return 1;
}

void execute_commands(char *line, char **og_envp)
{
    char **parsed_command = NULL;
    char **semicolon_parse = NULL;

    semicolon_parse = my_str_to_word_array(line, ';');
    for (int i = 0; semicolon_parse[i]; i++) {
        parsed_command = parse_line(semicolon_parse[i]);
        og_envp = execute_input(parsed_command, og_envp);
    }
}

int main(int argc, char **argv, char **envp)
{
    char *line = NULL;
    size_t len = 0;
    int keep_going = 1;
    char **og_envp = duplicate_env(envp);

    if (envp == NULL)
        return 84;
    while (keep_going > 0) {
        my_putstr("$>");
        keep_going = getline(&line, &len, stdin);
        line = correct_line(line);
        if (line[0] == '\n' || is_seggy(line)) {
            if (keep_going > 1)
                avoid_seggy(keep_going);
            continue;
        }
        execute_commands(line, og_envp);
    }
    return 0;
}