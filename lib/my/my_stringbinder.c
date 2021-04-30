/*
** EPITECH PROJECT, 2021
** B-PSU-101-BER-1-1-minishell1-mickael.riess
** File description:
** my_stringbinder
*/

#include <stdlib.h>

int my_strlen(char const *str);

char *my_stringbinder(char *str1, char *str2)
{
    int counter = 0;
    int size1 = my_strlen(str1);
    int size2 = my_strlen(str2);
    char *returnstring = malloc(sizeof(char) * (size1 + size2));

    for (; str1[counter]; counter++)
        returnstring[counter] = str1[counter];
    for (int i = 0; str2[i]; i++) {
        returnstring[counter] = str2[i];
        counter++;
    }
    returnstring[counter] = '\0';
    return returnstring;
}