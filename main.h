#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>

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
#define SHORT 1
#define LONG 2

/**
 * struct buffer_s - A new type defining a buffer struct.
 * @buffer: A pointer to a character array.
 * @start: A pointer to the start of buffer.
 * @len: The length of the string stored in buffer.
 */
typedef struct buffer_s
{
    char *buffer;
    char *start;
    unsigned int len;
} buffer_t;

typedef struct specifiers
{
    char format;
    unsigned int (*func)(va_list, buffer_t *, unsigned char, int, int, unsigned char);
} specifiers_t;

typedef struct converter_s
{
    unsigned char specifier;
    unsigned int (*func)(va_list, buffer_t *, unsigned char, int, int, unsigned char);
} converter_t;

/**
 * struct flag_s - A new type defining a flags struct.
 * @flag: A character representing a flag.
 * @value: The integer value of the flag.
 */
typedef struct flag_s
{
    unsigned char flag;
    unsigned char value;
} flag_t;

unsigned int convert_signed_base(buffer_t *output, long int num, char *base, unsigned char flags, int width, int precision);
unsigned int convert_unsigned_base(buffer_t *output, unsigned long int num, char *base, unsigned char flags, int width, int precision);
unsigned int get_char(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length);
unsigned int get_percent(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length);
unsigned int get_address(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length);
unsigned int get_string(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length);
unsigned int get_non_printable(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length);
unsigned int get_reverse(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length);
unsigned int get_rot13(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length);
unsigned char match_flags(const char *flag, char *index);
int match_width(va_list args, const char *modifier, char *index);
int match_precision(va_list args, const char *modifier, char *index);
unsigned int (*match_specifiers(const char *specifier))(va_list, buffer_t *, unsigned char, int, int, unsigned char);
int copy_to_buffer(buffer_t *output, const char *src, unsigned int size);
void free_buffer(buffer_t *output);

buffer_t *initialize_buffer(void);
unsigned int store_padding(buffer_t *output, unsigned int printed, unsigned char flags, int width);
unsigned int store_string_padding(buffer_t *output, unsigned char flags, int width, int precision, int string_size);
unsigned int store_trailing_padding(buffer_t *output, unsigned int printed, unsigned char flags, int width);

void perform_cleanup(va_list args, buffer_t *output);
int execute_printf(const char *format, va_list args, buffer_t *output);
int _printf(const char *format, ...);

unsigned int get_lowercase_hex(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length);
unsigned int get_uppercase_hex(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length);
unsigned int signed_integer(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length);
unsigned int get_binary(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length);

unsigned char get_length(const char *modifier, char *index);
unsigned int get_octal(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length);
unsigned int unsigned_integer(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length);

#endif

