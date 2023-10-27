#include "main.h"

/**
 * get_lowercase_hex - Converts an unsigned int argument to lowercase hex and
 * stores it in a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored in the buffer.
 */
unsigned int get_lowercase_hex(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length)
{
    unsigned long int num;
    unsigned int bytes_written = 0;
    char *prefix = "0x";

    if (length == LONG)
        num = va_arg(args, unsigned long int);
    else
        num = va_arg(args, unsigned int);
    if (length == SHORT)
        num = (unsigned short)num;

    if (HASH_FLAG == 1 && num != 0)
        bytes_written += copy_to_buffer(output, prefix, 2);

    if (!(num == 0 && precision == 0))
        bytes_written += convert_unsigned_base(output, num, "0123456789abcdef", flags, width, precision);

    bytes_written += store_trailing_padding(output, bytes_written, flags, width);

    return (bytes_written);
}

/**
 * get_uppercase_hex - Converts an unsigned int argument to uppercase hex and
 * stores it in a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored in the buffer.
 */
unsigned int get_uppercase_hex(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length)
{
    unsigned long int num;
    unsigned int bytes_written = 0;
    char *prefix = "0X";

    if (length == LONG)
        num = va_arg(args, unsigned long int);
    else
        num = va_arg(args, unsigned int);
    if (length == SHORT)
        num = (unsigned short)num;

    if (HASH_FLAG == 1 && num != 0)
        bytes_written += copy_to_buffer(output, prefix, 2);

    if (!(num == 0 && precision == 0))
        bytes_written += convert_unsigned_base(output, num, "0123456789ABCDEF", flags, width, precision);

    bytes_written += store_trailing_padding(output, bytes_written, flags, width);

    return (bytes_written);
}

