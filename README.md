# Simple Shell

This is a simple UNIX command line interpreter (shell) written in C. The shell allows users to execute basic commands and displays a prompt for user input. It supports the execution of single-word commands and provides a basic error handling mechanism.

## Table of Contents

- [Getting Started](#getting-started)
- [Features](#features)
- [Usage](#usage)
- [Code Structure](#code-structure)
- [Functionality](#functionality)
- [Known Issues](#known-issues)
- [Contributing](#contributing)
- [License](#license)

## Getting Started

To compile and run the simple shell on your system, follow these steps:

1. Clone the repository:

    ```bash
    git clone <repository_url>
    cd simple_shell
    ```

2. Compile the code:

    ```bash
    gcc -o hsh *.c
    ```

3. Run the shell:

    ```bash
    ./hsh
    ```

## Features

- Display a prompt and wait for the user to type a command.
- Execute single-word commands.
- Provide basic error handling for command execution.
- Handle the "end of file" condition (Ctrl+D).
- Display appropriate error messages for command not found.
- Gracefully handle fork failures and execution errors.

## Usage

```bash
./hsh
```

Once the shell is running, you can enter single-word commands at the prompt. The shell will execute the command and display the prompt again.

```bash
#cisfun$ ls
#cisfun$ /bin/ls
#cisfun$ /bin/ls -l
#cisfun$ exit
```

## Code Structure

The code is organized into several source files for better modularity:

- **simple_shell.c**: The main entry point for the shell program.
- **execute.c**: Contains functions related to command execution and process creation.
- **parsed_line.c**: Handles parsing and extraction of commands from user input.
- **get_input.c**: Manages user input, reading from the command line.
- **prompt_usr.c**: Displays the shell prompt.

## Functionality

### `displayPrompt()`

Displays the shell prompt "( ͡° ͜ʖ ͡°)" if the file descriptor refers to a terminal.

### `readUserInput()`

Reads a line of input from the user, handling errors and checking for the end of file condition (Ctrl+D).

### `extractCommand(char *inputLine)`

Extracts a single-word command from the input line. Handles errors if the command is not a single word.

### `exit_Shell(char *command)`

Checks if the given command is the "exit" command. If true, exits the shell.

### `create_CP(char *args[])`

Forks and executes the given command in a child process. Waits for the child process to complete execution.

### `executeCommand(char *command)`

Executes the given command by parsing it and creating a child process using `create_CP()`.

## Known Issues

- The shell currently does not handle special characters, command arguments, or advanced features.
- No support for the PATH environment variable, built-ins, or special characters.
- Limited error handling for invalid user input.

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests to improve the functionality, address known issues, or add new features.

## License

This simple shell is open-source and distributed under the [MIT License](LICENSE). Feel free to use, modify, and distribute the code. See the LICENSE file for details.
