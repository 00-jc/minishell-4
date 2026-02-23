*This project has been created as part of the 42 curriculum by asoria and edblazqu*

# Minishell

## Description
Minishell is a simplified Unix shell written in __C__, designed to reproduce core features of __Bash__ while providing a deep understanding of how command interpreters work internally.

The objective of this project is to explore low-level system programming concepts such as process creation, file descriptor management, signal handling, and inter-process communication. By building a shell from scratch, the project aims to strengthen knowledge of operating system fundamentals and Unix architecture.

Minishell parses user input, interprets commands, and executes them using system calls like ``fork``, ``execve``, and ``wait``. It supports built-in commands, pipes, input/output redirections, environment variable expansion, and proper signal management. The implementation emphasizes clean architecture, memory management, and precise control over process execution.

Overall, Minishell is used as a practical introduction to how real-world shells operate, bridging the gap between theoretical OS concepts and hands-on system-level development.

## Instructions

### 1. Compilation

First, clone the repository and enter the project directory:

```bash
git clone <repository_url>
cd minishell
```

Compile the project with:

```bash
make
```

If compilation succeeds, an executable named `minishell` will be created.

#### Available Make Rules

```bash
make clean     # Removes object files
make fclean    # Removes object files and the executable
make re        # Recompiles everything from scratch
```

---

### 2. Launching Minishell

Start the shell with:

```bash
./minishell
```

You should see a prompt similar to:

```bash
minishell$
```

The shell is now ready to receive commands.

---

### 3. Running Basic Commands

You can execute standard Unix commands:

```bash
ls
pwd
whoami
echo Hello World
```

Internally, Minishell:
- Parses the user input
- Creates child processes using `fork`
- Executes programs using `execve`
- Waits for their termination using `wait`

---

### 4. Built-in Commands

Minishell implements the following built-ins:

```bash
cd <directory>
pwd
echo <text>
export VAR=value
unset VAR
env
exit
```

Example:

```bash
export NAME=Manolo
echo $NAME
```

---

### 5. Pipes

Commands can be chained using pipes (`|`):

```bash
ls | grep .c
cat file.txt | wc -l
```

The output of the first command becomes the input of the next command.

---

### 6. Redirections

Minishell supports input and output redirections:

```bash
echo Hello > file.txt      # Overwrites file
echo Hello >> file.txt     # Appends to file
cat < file.txt             # Uses file as input
```

---

### 7. Environment Variables

Environment variables can be expanded using `$`:

```bash
echo $HOME
echo $PATH
```

You can create or modify variables with:

```bash
export VAR=value
```

---

### 8. Signal Handling

Minishell handles common signals correctly:

- `Ctrl + C` → Interrupts the current running command
- `Ctrl + D` → Exits the shell (EOF)
- `Ctrl + \` → Sends quit signal but does nothing

---

### 9. Exiting Minishell

To properly exit the shell:

```bash
exit
```

Or press:

```bash
Ctrl + D
```

After exiting, control returns to your system’s default shell.

## Resources

### Official Documentation

Throughout the development of Minishell, we relied on official Linux manual pages to understand system calls, process control, file descriptors, and signal handling.

The following commands were especially useful:

```bash
man fork
man execve
man wait
man dup
man dup2
man pipe
man signal
man readline
```

We also consulted:

- GNU Bash manual  
- POSIX specifications for shell behavior  
- The Linux Programmer’s Manual  

These resources were essential for understanding low-level system programming and ensuring correct behavior aligned with Unix standards.

---

### Educational Content

To reinforce theoretical concepts and better understand implementation details, we used:

- YouTube tutorials on:
  - Process creation and management
  - File descriptor duplication
  - Pipes and redirections
  - Signal handling in Unix
- Community discussions and developer forums for debugging insights and edge cases

These materials helped clarify complex topics such as inter-process communication and parsing strategies.

---

### Generative AI Assistance

Generative AI tools were used as a complementary resource to:

- Clarify theoretical concepts
- Review and refactor code
- Assist with repetitive tasks
- Help draft documentation

AI was used as a support tool, not as a replacement for understanding. All critical logic, architectural decisions, and debugging processes were carried out through independent reasoning and validation against official documentation.

---

These resources collectively contributed to a deeper understanding of how a real shell operates internally.
