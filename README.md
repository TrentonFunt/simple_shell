# Simple Shell Project

This repository contains a simple shell implementation in C, which provides a basic command-line interface for users to interact with the system. The main functionalities include command execution, environment variable management, history tracking, and basic error handling.

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [File Structure](#file-structure)
- [Usage](#usage)
- [Functionality Overview](#functionality-overview)
- [Building the Shell](#building-the-shell)
- [Contributing](#contributing)
- [License](#license)

## Introduction

This simple shell project is designed to mimic the basic functionalities of a Unix-like shell. It supports command execution, environment variables, history tracking, and more. The project is written in C and uses standard C libraries for various functionalities.

## Features

- Command execution with basic command chaining
- Environment variable management
- History tracking of executed commands
- Built-in commands such as `exit`, `cd`, `help`, and more
- Alias support for custom commands
- File input redirection
- Basic error handling and reporting

## File Structure

- **shell.h**: Header file containing function prototypes, macro definitions, and structure declarations.
- **main.c**: Main entry point of the shell, initializes necessary data structures, and starts the shell's main loop.
- **handleStrings1.c, handleStrings2.c**: Functions for string manipulation.
- **leaveShell.c**: Functions related to exiting the shell.
- **generateTokens.c**: Functions for tokenizing input commands.
- **realloc.c**: Functions for memory reallocation.
- **memory.c**: Functions for memory management.
- **convert.c**: Functions for converting between data types.
- **loop.c**: Functions for the main shell loop.
- **parsed.c**: Functions for parsing and executing commands.
- **loophsh.c**: Functions for handling the shell loop.
- **handleErrors.c, shellErrors2.c**: Functions for error handling and reporting.
- **shellBuiltins1.c, shellBuiltins2.c**: Functions for built-in shell commands.
- **getLine.c**: Functions for reading input from the command line.
- **getinfo.c**: Functions for handling shell information.
- **environment.c, setEnvironment.c**: Functions for managing environment variables.
- **history.c**: Functions for managing command history.
- **linkedLists1.c, linkedLists2.c**: Functions for handling linked lists.
- **shellVariables.c**: Functions for managing shell variables.

## Usage

To use the simple shell, compile the source files and run the executable. The shell supports both interactive mode and script execution. For script execution, provide the script file as a command-line argument.

```bash
gcc main.c -o simple_shell
./simple_shell
```

## Functionality Overview

- **Command Execution**: The shell can execute various commands entered by the user, either interactively or from a script file.

- **Environment Variables**: The shell supports basic environment variable management, including setting, unsetting, and displaying environment variables.

- **History Tracking**: The shell keeps track of the command history, allowing users to navigate and re-execute previous commands.

- **Built-in Commands**: Several built-in commands, such as `exit`, `cd`, `help`, `history`, and `alias`, are available for enhanced user interaction.

- **File Input Redirection**: The shell supports file input redirection for executing commands with input from a file.

- **Error Handling**: Basic error handling is implemented to provide informative error messages when issues arise during command execution.

## Building the Shell

To build the simple shell, use the provided `gcc` command:

```bash
gcc main.c -o simple_shell
```

This will generate an executable file named `simple_shell`. Run the executable to start the shell.

## Contributing

Contributions to this simple shell project are welcome. If you find any issues or have suggestions for improvements, please open an issue or submit a pull request.

## License

This simple shell project is licensed under the [MIT License](LICENSE). Feel free to use, modify, and distribute the code for your purposes.

**Happy coding!**