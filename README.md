# Minishell\_42

**Minishell\_42** is a simplified shell program designed to mimic the behavior of a UNIX shell. It is a part of the 42 Network curriculum and is meant to help students learn about the core functionalities of shell commands, environment variables, and process management. The project involves implementing a shell from scratch, providing fundamental shell features such as command parsing, file redirection, environment variable expansion, command execution, and more.

## Features

* **Command Parsing:** The shell parses user input and interprets commands.
* **Environment Variables:** Support for handling environment variables like `$HOME`, `$PATH`, etc.
* **Process Management:** Executes commands in a separate process and supports piping and redirection.
* **Built-in Commands:** Implements common shell built-ins like `cd`, `echo`, `exit`, `pwd`, `export`, `unset`, and `env`.
* **File Redirection:** Handles file redirection for input/output, including `>`, `>>`, and `<`.
* **Piping:** Supports piping between commands using `|`.
* **Herodoc:** Implements heredoc functionality to handle multi-line input redirection.

## Table of Contents

1. [Project Structure](#project-structure)
2. [Compilation & Installation](#compilation--installation)
3. [Usage](#usage)
4. [Key Components](#key-components)
5. [Built-in Commands](#built-in-commands)
6. [Parser](#parser)
7. [Execution](#execution)
8. [Memory Management](#memory-management)
9. [Error Handling](#error-handling)
10. [Contributing](#contributing)

## Project Structure

This project is organized into multiple directories and files, each serving a specific purpose:

### Main Directories:

* **src/**: Contains the core functionality of the shell program.
* **lib/**: Includes helper functions used throughout the project, such as string manipulation, memory management, and utility functions.
* **memory/**: Implements memory management utilities for efficient handling of dynamic memory.
* **components/**: A collection of smaller submodules, each dedicated to specific parts of the shell (like parsing, lexer, execution).
* **parser/**: Responsible for breaking down the input commands into tokens and interpreting them.
* **prompt/**: Handles user input and displays the shell prompt.
* **lexer/**: Implements the lexical analyzer, converting raw input into structured tokens.
* **expander/**: Expands environment variables and handles command substitution.
* **herdoc/**: Handles heredoc functionality.
* **execution/**: Executes commands and manages processes.
* **env/**: Manages environment variables.
* **builtin/**: Implements built-in shell commands like `cd`, `echo`, `exit`, etc.
* **execute/**: Handles the execution flow, including file redirection and pipes.

### Key Files:

* **Makefile**: Automates the build process, defining how to compile and link the project.
* **minishell.h**: The header file containing declarations for the main program functions.
* **execution.h**: Declares functions related to command execution.
* **parser.h**: Defines functions for parsing user input and handling syntax.

### Notable Functions & Files:

* **lib/ft\_\*.c**: Functions that provide basic utilities such as string manipulation (e.g., `ft_atoi.c`, `ft_strncpy.c`, `ft_strlen.c`, etc.).
* **parser/parser.c**: Main file responsible for parsing the input.
* **lexer/lexer.c**: Handles lexical analysis of user input.
* **expander/expander.c**: Expands variables and processes them before execution.
* **execution/execution.c**: Executes commands and processes.
* **builtin/builtin.c**: Handles built-in commands (e.g., `echo`, `pwd`, `cd`, etc.).

## Compilation & Installation

### Requirements:

* **C Compiler** (e.g., GCC or Clang)
* **Make** (to build the project)
* **Unix-like system** (Linux/macOS)

### To Compile:

1. Clone the repository:

```bash
git clone https://github.com/iaceene/Minishell_42.git
cd Minishell_42
```

2. Build the project using `Makefile`:

```bash
make
```

3. To clean the build files:

```bash
make clean
```

4. To remove all generated files (including binaries):

```bash
make fclean
```

5. To recompile everything:

```bash
make re
```

### Running the Program:

After compiling the project, you can run the shell program with:

```bash
./minishell
```

This will start an interactive shell where you can enter commands.

## Usage

Once the shell is running, you can type Unix commands, and it will execute them just like any other shell. Here are some basic features:

* **Command Execution**: You can run programs by typing their name (e.g., `ls`, `pwd`).
* **Piping**: You can chain commands using pipes (`|`).

  ```bash
  echo "hello" | tr "a-z" "A-Z"
  ```
* **Redirection**: Input and output redirection works with `>`, `>>`, and `<`.

  ```bash
  echo "Hello" > output.txt
  cat < output.txt
  ```
* **Built-in Commands**: These commands are built into the shell and don’t require external binaries:

  * `cd`: Change directory.
  * `echo`: Print text to standard output.
  * `exit`: Exit the shell.
  * `pwd`: Print working directory.
  * `export`: Set environment variables.
  * `unset`: Remove environment variables.
  * `env`: Print all environment variables.

### Examples:

```bash
$ ./minishell
$ echo "Hello World"
Hello World
$ ls
src  lib  memory  components  parser  prompt  lexer  expander  execution  env  builtin
$ cd src
$ ./minishell
$ echo $PWD
/home/user/minishell/src
```

## Key Components

### 1. **Parser**

The parser takes user input and splits it into tokens (commands, arguments, and operators). It checks for valid syntax and prepares the data for execution.

### 2. **Lexer**

The lexer breaks down the input string into tokens such as words, operators, and symbols. It plays a crucial role in interpreting the user’s intentions.

### 3. **Expander**

The expander is responsible for replacing variables in the commands, such as `$PATH` or `$HOME`, with their actual values from the environment.

### 4. **Execution**

The execution component is responsible for forking new processes, redirecting input/output, handling pipes, and executing commands. It uses system calls like `execve()` and `fork()`.

### 5. **Memory Management**

Efficient memory management is implemented using custom memory tracking functions to avoid leaks. Dynamic memory allocation is handled manually.

## Built-in Commands

The following built-in commands are implemented:

* **cd**: Changes the current directory.
* **echo**: Prints a message to the standard output.
* **exit**: Exits the shell.
* **pwd**: Prints the current working directory.
* **export**: Sets environment variables.
* **unset**: Removes environment variables.
* **env**: Lists all environment variables.

### Example:

```bash
$ cd /home/user/projects
$ pwd
/home/user/projects
```

## Error Handling

The shell ensures that errors are caught at every stage:

* **Syntax Errors**: If the user inputs a command with invalid syntax, an error message is displayed.
* **Command Not Found**: If a command doesn’t exist or is incorrectly typed, the shell will print an error message.
* **Memory Errors**: If memory allocation fails, the program gracefully exits with an error message.

## Contributing

If you'd like to contribute to **Minishell\_42**, feel free to fork the repository and submit a pull request. Please make sure to:

* Follow the coding standards used throughout the project.
* Provide clear and concise commit messages.
* Write tests where applicable.

