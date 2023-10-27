#include "main.h"

/**
 * convert_signed_base - Converts a signed long to an inputted base and stores
 *                      the result to a buffer contained in a struct.
 *
 * @output: A buffer_t struct containing a character array.
 * @num: A signed long to be converted.
 * @base: A pointer to a string containing the base to convert to.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 *
 * Returns: The number of bytes stored to the buffer.
 */
unsigned int convert_signed_base(buffer_t *output, long int num, char *base, unsigned char flags, int width, int precision)
{
    int base_size;
    char digit, padding_char = '0';
    unsigned int bytes_written = 1;

    for (base_size = 0; *(base + base_size);)
        base_size++;

    if (num >= base_size || num <= -base_size)
    {
        bytes_written += convert_signed_base(output, num / base_size, base, flags, width - 1, precision - 1);
    }
    else
    {
        for (; precision > 1; precision--, width--) /* Handle precision */
            bytes_written += copy_to_buffer(output, &padding_char, 1);

        if (NEG_FLAG == 0) /* Handle width */
        {
            padding_char = (ZERO_FLAG == 1) ? '0' : ' ';
            for (; width > 1; width--)
                bytes_written += copy_to_buffer(output, &padding_char, 1);
        }
    }

    digit = base[(num < 0 ? -1 : 1) * (num % base_size)];
    copy_to_buffer(output, &digit, 1);

    return (bytes_written);
}

/**
 * convert_unsigned_base - Converts an unsigned long to an inputted base and
 *                        stores the result to a buffer contained in a struct.
 *
 * @output: A buffer_t struct containing a character array.
 * @num: An unsigned long to be converted.
 * @base: A pointer to a string containing the base to convert to.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 *
 * Returns: The number of bytes stored to the buffer.
 */
unsigned int convert_unsigned_base(buffer_t *output, unsigned long int num, char *base, unsigned char flags, int width, int precision)
{
    unsigned int base_size, bytes_written = 1;
    char digit, padding_char = '0', *leading_str = "0x";

    for (base_size = 0; *(base + base_size);)
        base_size++;

    if (num >= base_size)
    {
        bytes_written += convert_unsigned_base(output, num / base_size, base, flags, width - 1, precision - 1);
    }
    else
    {
        if (((flags >> 5) & 1) == 1) /* Printing a pointer address */
        {
            width -= 2;
            precision -= 2;
        }
        for (; precision > 1; precision--, width--) /* Handle precision */
            bytes_written += copy_to_buffer(output, &padding_char, 1);

        if (NEG_FLAG == 0) /* Handle width */
        {
            padding_char = (ZERO_FLAG == 1) ? '0' : ' ';

            for (; width > 1; width--)
            {
                bytes_written += copy_to_buffer(output, &padding_char, 1);
            }
        }
        if (((flags >> 5) & 1) == 1) /* Print "0x" for a pointer address */
            bytes_written += copy_to_buffer(output, leading_str, 2);
    }

    digit = base[(num % base_size)];
    copy_to_buffer(output, &digit, 1);

    return (bytes_written);
}

