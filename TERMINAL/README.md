
# myshell

## This is the readme file for the `myshell`.
## `myshell` is a custom shell implementation that supports the following commands: ls, cp, mv, grep, and ps.

There is a makefile already created to make the compiling easy.
Type :

```cpp
make
```

This would compile all the file.
I have executed both the question in 1 code.

Just execute ./terminal to run the terminal.
```
./terminal
```


### myshell supports the following commands:

    - ls [directory]: List the contents of a directory. If no directory is specified, list the contents of the current directory.
    - cp [source] [destination]: Copy a file from the source location to the destination location.
    - mv [source] [destination]: Move a file from the source location to the destination location.
    - grep [options] [pattern] [file]: Search for a pattern in a file. Options include -i (ignore case), -n (show line numbers), -c (show only the count of matches), and -w (match whole words only).
    - ps [options]: List the currently running processes. Options include -a (show all processes) and -r (show only the running processes).

### To exit myshell, type the `exit` command.


For 1st question:
If you type the commands in standard fashion like ls,ps,grep etc it will be executed through the system() command.
This would take the input and run it by passing it into system() function.

For 2nd question:
My own commands are named like myls,myps,mygrep.
When the user enters myls instead of ls, the command would be executed by the code written for it and it will bypass system() function.

Type >>help to get more info about the commands.
```
help
```

--- 

Created by: Parth Kansagra
Roll No:CS22BTECH11045
