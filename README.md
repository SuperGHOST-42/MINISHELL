# Minishell 

A small UNIX shell written in C, inspired by Bash.  
Made by **Ariclenes & Hugo** — 42 Lisboa.

---

## 📌 About

The goal of Minishell is to implement a functional command-line shell that behaves similarly to Bash for mandatory features:

✔ Interactive prompt  
✔ Command parsing with quotes  
✔ Pipes `|`  
✔ Redirections `< > >>`  
✔ Heredoc `<<`  
✔ Environment variable expansion `$VAR`, `$?`  
✔ Built-ins: `echo`, `cd`, `pwd`, `env`, `export`, `unset`, `exit`  
✔ Correct signal handling (`Ctrl-C`, `Ctrl-D`, `Ctrl-\`)  
✔ No memory leaks

This project teaches how shells work internally:  
process creation (`fork`), program execution (`execve`), inter-process communication (`pipe`), file descriptor management, and error handling.

---

## 🚀 Build & Run

```sh
make
./minishell
