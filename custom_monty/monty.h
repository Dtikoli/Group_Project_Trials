#ifndef MONTY_H
#define MONTY_H

/* library functions */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

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
 * struct cmd_s - structure of arguments passed from CL
 * @av: name of file passed as CL arg
 * @ac: number of arguments from CL
 * @nline: number of the current line in the file
 *
 * Description: command line arguments passed to main used
 * in different functions, organized in a struct for clarity
 */
typedef struct cmd_s
{
	char *av;
	int ac;
	unsigned int nline;
} cmd_t;

/**
 * struct info_s - extern data to access inside functions
 * @line: line from the opcode file
 * @words: tokenized content of opcode file
 * @stack: pointer to the stack
 * @fp: file pointer
 * @sflag: flag for stack or queue
 */
typedef struct info_s
{
	char *line;
	char **words;
	stack_t *stack;
	FILE *fp;
	int sflag;
} info_t;

extern info_t info;

#define INFO_INIT {NULL, NULL, NULL, NULL, 0}

/* error and failure messages */
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

/* Monty parser */
void monty(cmd_t *);

/* get function */
void (*get_func(char **))(stack_t **, unsigned int);

/* OPCODE instruction functions */
void handle_pint(stack_t **, unsigned int);
void handle_push(stack_t **, unsigned int);
void handle_pall(stack_t **, unsigned int);
void handle_pop(stack_t **, unsigned int);
void handle_swap(stack_t **, unsigned int);
void handle_add(stack_t **, unsigned int);
void handle_nop(stack_t **, unsigned int);
void handle_sub(stack_t **, unsigned int);
void handle_div(stack_t **, unsigned int);
void handle_mul(stack_t **, unsigned int);
void handle_mod(stack_t **, unsigned int);
void handle_rotl(stack_t **, unsigned int);
void handle_rotr(stack_t **, unsigned int);
void handle_stack(stack_t **, unsigned int);
void handle_queue(stack_t **, unsigned int);
void handle_pchar(stack_t **, unsigned int);
void handle_pstr(stack_t **, unsigned int);

/* tokenizer */
int count_word(char *);
char **strtow(char *);

/* memory functions */
void free_content(int);
void free_array(char **);

/* double linked list functions */
size_t dlistint_len(const stack_t *);
stack_t *add_dnodeint(stack_t **, const int);
size_t print_dlistint(const stack_t *);
int delete_dnodeint_at_index(stack_t **, unsigned in);
stack_t *get_dnodeint_at_index(stack_t *, unsigned int);
stack_t *insert_dnodeint_at_index(stack_t **, unsigned int, int);
stack_t *add_dnodeint_end(stack_t **, const int);
void free_dlistint(stack_t *);

#endif /* MONTY_H */
