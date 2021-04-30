/*
** EPITECH PROJECT, 2021
** B-PSU-101-BER-1-1-minishell1-mickael.riess
** File description:
** input_parser
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "include/my.h"
#include "include/input_parser.h"

char *correct_line(char *line)
{
    char *newline = malloc(sizeof(char) * my_strlen(line) + 1);
    int j = 0;

    for (int i = 0; line[i]; i++) {
        if (line[i] == '\"' && line[i + 1] == '\"') {
            i = i + 2;
            newline[j] = line[i];
        } else {
            newline[j] = line[i];
        }
        j++;
    }
    newline[j] = '\0';
    return newline;
}

void add_quotes_to_array(char **array, char *token, int *pos, int *qv)
{
    array[(*pos)] = my_strdup(token);
    (*pos)++;
    *qv = 0;
}

char **parse_line(char *line)
{
    char **array = malloc(sizeof(char *) * (my_strlen(line) + 1));
    char *rest = my_strdup(strtok(line, "\n"));
    char *lil_rest = NULL;
    char *token;
    char *newtoken;
    int quotes_validator = rest[0] == '\"' ? 1 : 0;
    int pos = 0;

    while ((token = strtok_r(rest, "\"", &rest))) {
        if (quotes_validator == 1) {
            add_quotes_to_array(array, token, &pos, &quotes_validator);
        } else {
            quotes_validator = 1;
            lil_rest = my_strdup(token);
            for (; (newtoken = strtok_r(lil_rest, "\t ", &lil_rest)); pos++)
                array[pos] = my_strdup(newtoken);
        }
    }
    array[pos] = NULL;
    return array;
}