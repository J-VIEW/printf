#include "main.h"

/**
 * store_padding - Stores leading spaces to a buffer for a width modifier.
 * @output: A buffer_t struct containing a character array.
 * @printed: The current number of characters already printed for a given specifier.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 *
 * Return: The number of bytes stored in the buffer.
 */
unsigned int store_padding(buffer_t *output, unsigned int printed, unsigned char flags, int width)
{
    unsigned int bytes_stored = 0;
    char padding_char = ' ';

    if (NEG_FLAG == 0)
    {
        for (width -= printed; width > 0;)
            bytes_stored += copy_to_buffer(output, &padding_char, 1);
    }

    return (bytes_stored);
}

/**
 * store_string_padding - Stores leading spaces to a buffer for a width modifier.
 * @output: A buffer_t struct containing a character array.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @string_size: The size of the string.
 *
 * Return: The number of bytes stored in the buffer.
 */
unsigned int store_string_padding(buffer_t *output, unsigned char flags, int width, int precision, int string_size)
{
    unsigned int bytes_stored = 0;
    char padding_char = ' ';

    if (NEG_FLAG == 0)
    {
        width -= (precision == -1) ? string_size : precision;
        for (; width > 0;)
            bytes_stored += copy_to_buffer(output, &padding_char, 1);
    }

    return (bytes_stored);
}

/**
 * store_trailing_padding - Stores trailing spaces to a buffer for a '-' flag.
 * @output: A buffer_t struct containing a character array.
 * @printed: The current number of bytes already stored for a given specifier.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 *
 * Return: The number of bytes stored in the buffer.
 */
unsigned int store_trailing_padding(buffer_t *output, unsigned int printed, unsigned char flags, int width)
{
    unsigned int bytes_stored = 0;
    char padding_char = ' ';

    if (NEG_FLAG == 1)
    {
        for (width -= printed; width > 0; width--)
            bytes_stored += copy_to_buffer(output, &padding_char, 1);
    }

    return (bytes_stored);
}

