#include "main.h"

/**
 * get_char - Converts an argument to an unsigned char and stores it in a buffer.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored in the buffer.
 */
unsigned int get_char(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length)
{
    char c;
    unsigned int bytes_written = 0;

    (void)precision;
    (void)length;

    c = va_arg(args, int);

    bytes_written += store_padding(output, bytes_written, flags, width);
    bytes_written += copy_to_buffer(output, &c, 1);
    bytes_written += store_trailing_padding(output, bytes_written, flags, width);

    return (bytes_written);
}

/**
 * get_percent - Stores a percent sign in a buffer.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored in the buffer (always 1).
 */
unsigned int get_percent(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length)
{
    char percent = '%';
    unsigned int bytes_written = 0;

    (void)args;
    (void)precision;
    (void)length;

    bytes_written += store_padding(output, bytes_written, flags, width);
    bytes_written += copy_to_buffer(output, &percent, 1);
    bytes_written += store_trailing_padding(output, bytes_written, flags, width);

    return (bytes_written);
}

/**
 * get_address - Converts the address of an argument to hexadecimal and stores it in a buffer.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored in the buffer.
 */
unsigned int get_address(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length)
{
    char *null = "(nil)";
    unsigned long int address;
    unsigned int bytes_written = 0;

    (void)length;

    address = va_arg(args, unsigned long int);
    if (address == '\0')
        return (copy_to_buffer(output, null, 5));

    flags |= 32;
    bytes_written += convert_unsigned_base(output, address, "0123456789abcdef", flags, width, precision);
    bytes_written += store_trailing_padding(output, bytes_written, flags, width);

    return (bytes_written);
}

