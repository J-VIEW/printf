#include "main.h"

/**
 * signed_integer - Converts a signed integer argument to a string
 * and stores it in a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored in the buffer.
 */
unsigned int signed_integer(va_list args, buffer_t *output,
                            unsigned char flags, int width, int precision, unsigned char length)
{
    long int decimal_value, copy;
    unsigned int bytes_written = 0, char_count = 0;
    char padding_char, space_char = ' ', negative_sign = '-', plus_sign = '+';

    if (length == LONG)
        decimal_value = va_arg(args, long int);
    else
        decimal_value = va_arg(args, int);

    if (length == SHORT)
        decimal_value = (short)decimal_value;

    // Handle space flag
    if (SPACE_FLAG == 1 && decimal_value >= 0)
        bytes_written += copy_to_buffer(output, &space_char, 1);

    if (precision <= 0 && NEG_FLAG == 0)
    {
        if (decimal_value == LONG_MIN)
            char_count += 19;
        else
        {
            for (copy = (decimal_value < 0) ? -decimal_value : decimal_value; copy > 0; copy /= 10)
                char_count++;
        }
        char_count += (decimal_value == 0) ? 1 : 0;
        char_count += (decimal_value < 0) ? 1 : 0;
        char_count += (PLUS_FLAG == 1 && decimal_value >= 0) ? 1 : 0;
        char_count += (SPACE_FLAG == 1 && decimal_value >= 0) ? 1 : 0;

        // Handle plus flag when zero flag is active
        if (ZERO_FLAG == 1 && PLUS_FLAG == 1 && decimal_value >= 0)
            bytes_written += copy_to_buffer(output, &plus_sign, 1);

        // Print negative sign when zero flag is active
        if (ZERO_FLAG == 1 && decimal_value < 0)
            bytes_written += copy_to_buffer(output, &negative_sign, 1);

        padding_char = (ZERO_FLAG == 1) ? '0' : ' ';
        for (width -= char_count; width > 0; width--)
            bytes_written += copy_to_buffer(output, &padding_char, 1);
    }

    // Print negative sign when zero flag is not active
    if (ZERO_FLAG == 0 && decimal_value < 0)
        bytes_written += copy_to_buffer(output, &negative_sign, 1);

    // Handle plus flag when zero flag is not active
    if (ZERO_FLAG == 0 && (PLUS_FLAG == 1 && decimal_value >= 0))
        bytes_written += copy_to_buffer(output, &plus_sign, 1);

    if (!(decimal_value == 0 && precision == 0))
        bytes_written += convert_signed_base(output, decimal_value, "0123456789",
                                             flags, 0, precision);

    bytes_written += store_trailing_padding(output, bytes_written, flags, width);

    return (bytes_written);
}

/**
 * get_binary - Converts an unsigned integer argument to a binary string
 * and stores it in a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored in the buffer.
 */
unsigned int get_binary(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length)
{
    unsigned int num;

    num = va_arg(args, unsigned int);

    (void)length;

    return (convert_unsigned_base(output, num, "01", flags, width, precision));
}

/**
 * get_octal - Converts an unsigned integer argument to an octal string
 * and stores it in a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored in the buffer.
 */
unsigned int get_octal(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length)
{
    unsigned long int num;
    unsigned int bytes_written = 0;
    char zero = '0';

    if (length == LONG)
        num = va_arg(args, unsigned long int);
    else
        num = va_arg(args, unsigned int);
    if (length == SHORT)
        num = (unsigned short)num;

    if (flags & HASH_FLAG && num != 0)
        bytes_written += copy_to_buffer(output, &zero, 1);

    if (!(num == 0 && precision == 0))
        bytes_written += convert_unsigned_base(output, num, "01234567", flags, width, precision);

    bytes_written += store_trailing_padding(output, bytes_written, flags, width);

    return (bytes_written);
}

/**
 * unsigned_integer - Converts an unsigned integer argument to a decimal
 * and stores it in a buffer contained in a struct.
 * @args: A va_list pointing to the argument to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored in the buffer.
 */
unsigned int unsigned_integer(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length)
{
    unsigned long int num;
    unsigned int bytes_written = 0;

    if (length == LONG)
        num = va_arg(args, unsigned long int);
    else
        num = va_arg(args, unsigned int);
    if (length == SHORT)
        num = (unsigned short)num;

    if (!(num == 0 && precision == 0))
        bytes_written += convert_unsigned_base(output, num, "0123456789", flags, width, precision);

    bytes_written += store_trailing_padding(output, bytes_written, flags, width);

    return (bytes_written);
}

