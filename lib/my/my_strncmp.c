/*
** EPITECH PROJECT, 2020
** my_strncmp
** File description:
** Task07
*/

int my_strlen(char const *str);

int my_strncmp(char const *str1, char const *str2, int n)
{
    int str1_len = my_strlen(str1);
    int str2_len = my_strlen(str2);
    int max_len = (str1_len > str2_len) ? str1_len : str2_len;

    n = (n > max_len) ? max_len : n;
    for (int i = 0; i < n; i++) {
        if (str1[i] - str2[i] != 0)
            return str1[i] - str2[i];
    }
    return 0;
}
