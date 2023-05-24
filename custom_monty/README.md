# Monty Interpreter

Monty 0.98 is a scripting language that is first compiled into Monty byte code (just like in Python). It relies on a unique stack, with specific instructions to manipulate it. 

The goal of this project is to create an interpreter for Monty ByteCode files, utilizing Stacks (LIFO) and Queues (FIFO). Also included are [BrainFuck](https://en.wikipedia.org/wiki/Brainfuck) files.


## Quick Start

<u>Monty</u>:

1. Simply Compile: `$ gcc *.c -o monty`
2. Then Run: `$ ./monty filename.m`
3. A sample bytecode file is located at `/bytecodes/test.txt`.

<u>BrainFuck</u>:

1. Install the interpreter: `$ sudo apt-get install bf`
2. Then Run: `$ bf filename.bf`
3. Sample BrainFuck files are located at `/brainfuck`


## Commands Overview

1. push: Pushes an integer onto the stack.
2. pall: Prints all integers on the stack, starting at the top..
3. pint: Prints the integer at the top of the stack.
4. pop: Removes top element of stack.
5. swap: Swaps top two elements of the stack.
6. add: Add top two elements of the stack, remove them, and push result onto stack.
7. sub: Subtract top two elements of the stack, remove them, and push result onto stack.
8. div: Integer divide top two elements of the stack, remove them, and push result onto stack.
9. mul: Multiply top two elements of the stack, remove them, and push result onto stack.
10. mod: Integer division remainder top two elements, remove them, push result onto stack.
11. pchar: Print the ascii character based on top integer in stack.
12. pstr: Print the ascii characters related to integers in stack until 0 or >255.
13. rotl: Rotate stack. Top element becomes last. Second from top becomes top.
14. rotr: Rotate stack. Last element becomes top, Top element becomes second from top.
15. stack: Changes mode to first in first out (the default behavior). Front of queue becomes top of stack.
16. queue: Changes mode to last in first out. Top of stack becomes front of queue.


## Potential Failures

Potential failures and their messages will be mentioned for each operation. Failures that can occur at this time include:

- USAGE: monty file      *# If given no file or too many arguments*
- Error: Can't open file <file name>      *# If given invalid file*
- Error: unknown instruction <opcode>      *# If unknown operation given*
- Error: malloc failed      *# if malloc fails*


## Author

D. Tikoli
