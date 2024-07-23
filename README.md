##**Minishell**

**Overview**

Minishell is a project aimed at creating a simple shell, similar to a minimal version of bash, using the C programming language. This project is part of the 42 curriculum and focuses on understanding processes and file descriptors.

**Features**
- **Prompt Display**: Displays a prompt when waiting for a command.
- **Command Execution**: Searches for and executes commands based on the PATH variable or relative/absolute paths.
- **History Management**: Maintains a history of commands executed.
- **Signal Handling**: Implements custom handling for signals like ctrl-C, ctrl-D, and ctrl-\.
- **Redirections**: Supports input (<), output (>), append (>>), and here-document (<<) redirections.
- **Pipes**: Allows chaining of commands using pipes (|).
- **Environment Variables**: Expands environment variables ($VAR), including $? for the exit status of the last executed command.
- **Built-in Commands**: Implements built-ins such as echo, cd, pwd, export, unset, env, and exit.

##**Requirements**
- **Memory Management**: All heap-allocated memory must be freed appropriately to avoid leaks.
- **External Functions**: Uses functions like readline, printf, malloc, free, fork, execve, pipe, and others.
- **No Global Variables**: Limits to one global variable for signal handling.

##**Build and Run**

To build the project, use the provided Makefile:

```bash
	make
```

To clean up build files:

```bash
make clean
```

To clean up all generated files:

```bash
make fclean
```

To rebuild the project:

```bash
make re
```
**Usage**
Run the shell by executing the compiled binary:

```bash
./minishell
```
**Note**
Memory leaks from the `readline()` function are acknowledged and not required to be fixed, but all other code must be leak-free.

