#ifndef _MONTY_H_
#define _MONTY_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define ERROR_USAGE "USAGE: monty file\n"
#define ERROR_FILE "Error: Can't open file %s\n"
#define ERROR_UNKNOWN "L%u: unknown instruction %s\n"
#define FAILURE_MALLOC "Error: malloc failed\n"
#define FAILURE_PUSH "L%u: usage: push integer\n"
#define FAILURE_PINT "L%u: can't pint, stack empty\n"
#define FAILURE_POP "L%u: can't pop an empty stack\n"
#define FAILURE_SWAP "L%u: can't swap, stack too short\n"
#define FAILURE_ADD "L%u: can't add, stack too short\n"
#define FAILURE_SUB "L%u: can't sub, stack too short\n"
#define FAILURE_DIV "L%u: can't div, stack too short\n"
#define ERROR_DIV "L%u: division by zero\n"
#define FAILURE_MUL "L%u: can't mul, stack too short\n"
#define FAILURE_MOD "L%u: can't mod, stack too short\n"
#define FAILURE_PCHAR "L%u: can't pchar, stack empty\n"
#define ERROR_PCHAR "L%u: can't pchar, value out of range\n"


/**
 * struct stack_s - doubly linked list representation of a stack (or queue)
 * @n: integer
 * @prev: points to the previous element of the stack (or queue)
 * @next: points to the next element of the stack (or queue)
 *
 * Description: doubly linked list node structure
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct stack_s
{
	int n;
	struct stack_s *prev;
	struct stack_s *next;
} stack_t;

/**
 * struct instruction_s - opcode and its function
 * @opcode: the opcode
 * @f: function to handle the opcode
 *
 * Description: opcode and its function
 * for stack, queues, LIFO, FIFO Holberton project
 */
typedef struct instruction_s
{
	char *opcode;
	void (*f)(stack_t **stack, unsigned int line_number);
} instruction_t;

/**
 * struct args_s - structure of arguments from main
 * @av: name of the file from the command line
 * @ac: number of arguments from main
 * @line_number: number of the current line in the file
 *
 * Description: arguments passed to main from the command line
 * used in different functions, organized in a struct for clarity
 */
typedef struct args_s
{
	char *av;
	int ac;
	unsigned int line_number;
} args_t;

/**
 * struct data_s - extern data to access inside functions
 * @line: line from the file
 * @words: parsed line
 * @stack: pointer to the stack
 * @fptr: file pointer
 * @qflag: flag for queue or stack
 */
typedef struct data_s
{
	char *line;
	char **words;
	stack_t *stack;
	FILE *fptr;
	int qflag;
} data_t;

typedef stack_t dlistint_t;

extern data_t data;

#define DATA_INIT {NULL, NULL, NULL, NULL, 0}

/* Monty parser */
void monty(args_t *args);

/* get function */
void (*get_func(char **parsed))(stack_t **, unsigned int);

/* OPCODE operation functions */
void pint_handler(stack_t **stack, unsigned int line_number);
void push_handler(stack_t **stack, unsigned int line_number);
void pall_handler(stack_t **stack, unsigned int line_number);
void pop_handler(stack_t **stack, unsigned int line_number);
void swap_handler(stack_t **stack, unsigned int line_number);
void add_handler(stack_t **stack, unsigned int line_number);
void nop_handler(stack_t **stack, unsigned int line_number);
void sub_handler(stack_t **stack, unsigned int line_number);
void div_handler(stack_t **stack, unsigned int line_number);
void mul_handler(stack_t **stack, unsigned int line_number);
void mod_handler(stack_t **stack, unsigned int line_number);
void rotl_handler(stack_t **stack, unsigned int line_number);
void rotr_handler(stack_t **stack, unsigned int line_number);
void stack_handler(stack_t **stack, unsigned int line_number);
void queue_handler(stack_t **stack, unsigned int line_number);
void pchar_handler(stack_t **stack, unsigned int line_number);
void pstr_handler(stack_t **stack, unsigned int line_number);

/* tokenizer */
int count_word(char *s);
char **strtow(char *str);

/* memory functions */
void free_handle(int);
void free_str(char **);

#endif /* _MONTY_H_ */
