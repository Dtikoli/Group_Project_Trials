# Monty Interpreter

Monty 0.98 is a scripting language that is first compiled into Monty byte code (just like in Python). It relies on a unique stack, with specific instructions to manipulate it. 

The goal of this project is to create an interpreter for Monty ByteCode files, utilizing Stacks (LIFO) and Queues (FIFO). Also included are [BrainFuck](https://en.wikipedia.org/wiki/Brainfuck) files.


## Quick Start

<u>Monty</u>:

Simply Compile: `$ gcc *.c -o monty`

Then Run: `$ ./monty filename.m`

A sample bytecode file is located at `/bytecodes/test.txt`.

<u>BrainFuck</u>:

Install the interpreter: `$ sudo apt-get install bf`

Then Run: `$ bf filename.bf`

Sample BrainFuck files are located at `/brainfuck`


## Commands Overview

Potential failures and their messages will be mentioned for each operation. Failures that can occur at this time include:

- USAGE: monty file      *# If given no file or too many arguments*
- Error: Can't open file <file name>      *# If given invalid file*
- Error: unknown instruction <opcode>      *# If unknown operation given*
- Error: malloc failed      *# if malloc fails*


## Author

D.Tikoli


