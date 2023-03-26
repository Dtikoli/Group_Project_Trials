#ifndef _MAIN_H_
#define _MAIN_H_

/* C library Header files */
#include <limits.h>
#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

/* Flag Option Macros */
#define PLUS 1
#define SPACE 2
#define HASH 4
#define ZERO 8
#define NEG 16
#define PLUS_FLAG (flags & 1)
#define SPACE_FLAG ((flags >> 1) & 1)
#define HASH_FLAG ((flags >> 2) & 1)
#define ZERO_FLAG ((flags >> 3) & 1)
#define NEG_FLAG ((flags >> 4) & 1)

/* Length Modifier Macros */
#define SHORT 1
#define LONG 2

/**
 * struct buffer_type - A new type defining a buffer struct.
 * @buffer: A pointer to a character array.
 * @start: A pointer to the start of buffer.
 * @len: The length of the string stored in buffer.
 */
typedef struct buffer_type
{
	char *buffer;
	char *start;
	unsigned int len;
} buffer_t;

/**
 * struct print_type - A new type defining a converter struct.
 * @type: A character representing a conversion specifier.
 * @fun: A pointer to a conversion function corresponding to specifier.
 */
typedef struct print_type
{
	unsigned char type;
	unsigned int (*fun)(va_list, buffer_t *,
			unsigned char, int, int, unsigned char);
} print_t;

/**
 * struct flag_type - A new type defining a flags struct.
 * @flag: A character representing a flag.
 * @value: The integer value of the flag.
 */
typedef struct flag_type
{
	unsigned char flag;
	unsigned char value;
} flag_t;

int _printf(const char *format, ...);

/* Handler for Printf Function */
int print_handle(const char *format, va_list list, buffer_t *output);

/* Print Type Functions */
unsigned int print_c(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len);
unsigned int print_s(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len);
unsigned int print_di(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len);
unsigned int print_percent(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len);
unsigned int print_b(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len);
unsigned int print_u(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len);
unsigned int print_o(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len);
unsigned int print_hex(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len);
unsigned int print_HEX(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len);
unsigned int print_ns(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len);
unsigned int print_add(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len);
unsigned int print_r(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len);
unsigned int print_R(va_list list, buffer_t *output,
		unsigned char flags, int width, int prec, unsigned char len);

/* Print Option handlers */
unsigned char flag_handle(const char *flags, char *index);
unsigned char len_handle(const char *opts, char *index);
int width_handle(va_list list, const char *opts, char *index);
int prec_handle(va_list list, const char *opts, char *index);
unsigned int (*type_handle(const char *opts))(va_list, buffer_t *,
		unsigned char, int, int, unsigned char);

/* Width Modifier functions */
unsigned int numwidth_modify(buffer_t *output, unsigned int printed,
		unsigned char flags, int width);
unsigned int strwidth_modify(buffer_t *output,
		unsigned char flags, int width, int prec, int size);
unsigned int negflag_width_modify(buffer_t *output, unsigned int printed,
		unsigned char flags, int width);

/* Utility Functions */
buffer_t *init_buffer(void);
void free_buffer(buffer_t *output);
unsigned int _memcpy(buffer_t *output, const char *src, unsigned int n);
unsigned int sb_convert(buffer_t *output, long int num, char *base,
		unsigned char flags, int width, int prec);
unsigned int ub_convert(buffer_t *output, unsigned long int num, char *base,
		unsigned char flags, int width, int prec);

#endif /* #ifndef _MAIN_H_ */

