# Minishell

Minishell is a simple shell implementation written in C. It aims to replicate basic functionalities of Unix shells, allowing users to execute commands, manage environment variables, and use built-in commands.

## Features
- Command execution (with support for pipes and redirections)
- Built-in commands: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`
- Environment variable management
- Quoting and tokenization
- Custom implementation of standard library functions (see `libft/`)

## Project Structure
- `main.c` — Entry point of the shell
- `minishell.h` — Main header file
- `built_in/` — Built-in command implementations
- `butcher/` — Command execution and file handling
- `creation_ast/` — Abstract Syntax Tree creation and utilities
- `libft/` — Custom standard library functions
- `tokenization/` — Tokenization and parsing logic

## Build Instructions
1. Clone the repository:
   ```bash
   git clone https://github.com/JefersonSopanR/My_minishell_almost_finish.git
   cd My_minishell_almost_finish
   ```
2. Build the project using `make`:
   ```bash
   make
   ```

## Usage
Run the shell executable:
```bash
./minishell
```
Type commands as you would in a regular shell. Built-in commands are supported, as well as external commands found in your `$PATH`.

## Requirements
- GCC or Clang
- Linux or macOS

## Authors
- Jeferson Sopan R
- Contributors: See commit history

## License
This project is licensed under the MIT License.
