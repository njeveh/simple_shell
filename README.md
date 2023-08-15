# Project 0x016. C - Simple Shell

## Learning Objectives
At the end of this project, you are expected to be able to explain to anyone, without the help of Google:

## General
 - How does a shell work
 - What is a `pid` and a `ppid`
 - How to manipulate the environment of the current process
 - What is the difference between a function and a system call
 - How to create processes
 - What are the three prototypes of `main`
 - How does the shell use the `PATH` to find the programs
 - How to execute another program with the `execve` system call
 - How to suspend the execution of a process until one of its children terminates
 - What is `EOF` / “end-of-file”?

## Requirements
### General
 - Allowed editors: `vi`, `vim`, `emacs`
 - All your files will be compiled on `Ubuntu 20.04 LTS` using `gcc`, using the options `-Wall -Werror -Wextra -pedantic -std=gnu89`
 - All your files should end with a new line
 - A README.md file, at the root of the folder of the project is mandatory
 - Your code should use the `Betty` style. It will be checked using `betty-style.pl` and `betty-doc.pl`
 - Your shell should not have any memory leaks
 - No more than 5 functions per file
 - All your header files should be include guarded
 - Use system calls only when you need to (why?)
 - Write a `README` with the description of your project
 - You should have an `AUTHORS` file at the root of your repository, listing all individuals having contributed content to the repository. Format, see Docker

## Output
 - Unless specified otherwise, your program must have the exact same output as `sh` (`/bin/sh`) as well as the exact same error output.
 - The only difference is when you print an error, the name of the program must be equivalent to your `argv[0]` (See below)
Example of error with `sh`:

```bash
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
```

Same error with your program hsh:

```bash
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$
```

## Compilation
Your shell will be compiled this way:

`gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh`

## Testing
Your shell should work like this in interactive mode:

```bash
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```
But also in non-interactive mode:

```bash
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```

## Files

File | Content
---- | -----------
[main.c](./main.c) | entry point, executing function
[shell.h](./shell.h) | function prototypes, standard libraries, structs
[print_funcs.c](./print_funcs.c) | printing functions
[print_errors.c](./print_errors.c) | error printing functions
[string_funcs_1.c](./string_funcs_1.c) | string-handling functions
[string_funcs_2.c](./string_funcs_2.c) | string-handling functions
[list_funcs_1.c](./list_funcs_1.c) | linked list handling functions
[list_funcs_2.c](./list_funcs_2.c) | linked list handling functions
[tokenize.c](./tokenize.c) | string to tokens parsing functions
[path_finder.c](./path_finder.c) | functions that check the PATH for commands
[builtins.c](./builtins.c) | functions dealing with the shell builtins
[set_env.c](./set_env.c) | functions dealing with the setenv/unsetenv builtins
[helper_funcs.c](./helper_funcs.c) | memory and signal handling functions
[convert_funcs.c](./convert_funcs.c) | conversion between string and number functions
[man_1_simple_shell](./man_1_simple_shell) | Simple Shell man page (```man ./man_1_simple_shell```)

