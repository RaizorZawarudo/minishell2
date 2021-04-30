/*
** EPITECH PROJECT, 2021
** B-PSU-101-BER-1-1-minishell1-mickael.riess
** File description:
** execute_commad
*/

char **duplicate_env(char **og_envp);
void stop_exec_child(int sig);
void display_command_doesnt_exist(char *command);
void exec_prg(char *abs_path, char **p_command, int path_exists, char **envp);
void exec_script(char **p_command, int path_exists, char **envp);
char *find_cmd_in_paths(char **paths, char *command);
int we_found_cmd(char *path, char *command);
char **find_executable_paths(char **envp);
void do_env(char **envp);
char **do_setenv(char **args, char **envp);
char *apply_setenv(char *arg1, char *arg2);
char **execute_input(char **parsed_command, char **envp);
char **do_unsetenv(char **args, char **envp);
char **do_chdir(char **args, char **envp);