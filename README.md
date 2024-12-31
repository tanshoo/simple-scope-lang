# Simple Scope Language

This repository contains a very simple language implemented in C++. It allows variable assignment, variable printing and creating nested scopes. All variables declared or changed inside a scope revert to their previous state once that scope ends.

## Syntax
- **Assignment**: `<varname> = <number>` or `<varname> = <varname>`
- **Printing**: `print <varname>`
- **Variable scopes**: 
    - Open scope: `scope {`
    - Close scope: `}`

## Building
```sh
git clone https://github.com/tanshoo/simple-scope-lang.git
cd simple-scope-lang
g++ -std=c++20 interpreter.cc lexer.cc -o interpreter
```

## Usage
Provide the code as input to the interpreter. Example:
```sh
./interpreter < program1
```
An example program can be found in [program1](program1).