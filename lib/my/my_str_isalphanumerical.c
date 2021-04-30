/*
** EPITECH PROJECT, 2021
** B-PSU-101-BER-1-1-minishell1-mickael.riess
** File description:
** my_str_isalphanumerical
*/

int my_str_isalphanumerical(char const *str)
{
    if (str[0] == '\0')
        return (1);
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] < 'A' || str[i] > 'Z')
            && (str[i] < 'a' || str[i] > 'z')
            && (str[i] < '0' || str[i] > '9'))
            return (0);
    }
    return (1);
}
