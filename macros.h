#ifndef HELPERS_H
#define HELPERS_H

#define PROMPT_MSG "$"

#define UNUSED __attribute__((unused))
#define BUFFER_SIZE 1024

#define HELP_CD_MSG "cd=\n"                                                                \
                    "cd:\tcd [dir]\n\n"                                                    \
                    "\tChange the shell working directory.\n\n"                            \
                    "\tIf no argument is given to cd the command will be interpreted\n"    \
                    "\tas cd $HOME.\n"                                                     \
                    "\tif the argumenthelp is - (cd -), the command will be interpreted\n" \
                    "\tas cd $OLDPWD.\n\n"

#define HELP_EXIT_MSG "exit=\n"                                                              \
                      "exit:\texit [stts]\n\n"                                               \
                      "\tExit of the simple-shell.\n\n"                                      \
                      "\tExits the shell with a stts of N. If N is omitted, the exit stts\n" \
                      "\tis that of the last command executed.\n\n"

#define HELP_ENV_MSG "env=\n"                   \
                     "env:\tenv \n\n"           \
                     "\tPrint environment.\n\n" \
                     "\tThe env command will print a complete list of environment variables.\n\n"

#define HELP_SETENV_MSG "setenv=\n"                                                            \
                        "setenv:\tsetenv VARIABLE VALUE\n\n"                                   \
                        "\tChange or add an environment variable.\n\n"                         \
                        "\tInitialize a new environment variable, or modify an existing one\n" \
                        "\tWhen there are not the correct number of arguments print an error message.\n\n"

#define HELP_UNSETENV_MSG "unsetenv=\n"                                                            \
                          "unsetenv:\tunsetenv VARIABLE\n\n"                                       \
                          "\tThe unsetenv function deletes one variable from the environment.\n\n" \
                          "\tWhen there are not the correct number of arguments print an error message.\n\n"

#define HELP_MSG "help=\n"                                                                   \
                 "help:\thelp [BUILTIN_NAME]\n\n"                                            \
                 "\tDisplay information about builtin commands.\n\n"                         \
                 "\tDisplays brief summaries of builtin commands. If BUILTIN_NAME is\n"      \
                 "\tspecified, gives detailed help on all commands matching BUILTIN_NAME,\n" \
                 "\totherwise, the list of help topics is printed BUILTIN_NAME list.\n"      \
                 "\tArguments:\n\n"                                                          \
                 "\tBUILTIN_NAME specifying a help topic.\n\n"                               \
                 "\tcd\t[dir]\n"                                                             \
                 "\texit\t[stts]\n"                                                          \
                 "\tenv\n"                                                                   \
                 "\tsetenv\t[variable value]\n"                                              \
                 "\tunset\t[variable]\n"                                                     \
                 "\thelp\t[built_name]\n\n"

#endif