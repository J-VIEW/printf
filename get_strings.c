#include "main.h"

/**
 * get_string - Converts a string argument and stores it in a buffer.
 * @args: A va_list pointing to the string to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored in the buffer.
 */
unsigned int get_string(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length)
{
    char *str, *null = "(null)";
    int size;
    unsigned int bytes_written = 0;

    (void)flags;
    (void)length;

    str = va_arg(args, char *);
    if (str == NULL)
        return (copy_to_buffer(output, null, 6));

    for (size = 0; *(str + size);)
        size++;

    bytes_written += store_string_padding(output, flags, width, precision, size);

    precision = (precision == -1) ? size : precision;
    while (*str != '\0' && precision > 0)
    {
        bytes_written += copy_to_buffer(output, str, 1);
        precision--;
        str++;
    }

    bytes_written += store_trailing_padding(output, bytes_written, flags, width);

    return (bytes_written);
}

/**
 * get_non_printable - Converts non-printable characters to their escaped
 * representation and stores it in a buffer.
 * @args: A va_list pointing to the string with non-printable characters.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored in the buffer.
 *
 * Description: Non-printable characters (ASCII values < 32 or >= 127)
 * are stored as \x followed by the ASCII code value in hex.
 */
unsigned int get_non_printable(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length)
{
    char *str, *null = "(null)", *hex = "\\x", zero = '0';
    int size, index;
    unsigned int bytes_written = 0;

    (void)length;
    str = va_arg(args, char *);
    if (str == NULL)
        return (copy_to_buffer(output, null, 6));

    for (size = 0; str[size];)
        size++;

    bytes_written += store_string_padding(output, flags, width, precision, size);

    precision = (precision == -1) ? size : precision;
    for (index = 0; *(str + index) != '\0' && index < precision; index++)
    {
        if (*(str + index) < 32 || *(str + index) >= 127)
        {
            bytes_written += copy_to_buffer(output, hex, 2);
            if (*(str + index) < 16)
                bytes_written += copy_to_buffer(output, &zero, 1);
            bytes_written += convert_unsigned_base(output, *(str + index), "0123456789ABCDEF", flags, 0, 0);
            continue;
        }
        bytes_written += copy_to_buffer(output, (str + index), 1);
    }

    bytes_written += store_trailing_padding(output, bytes_written, flags, width);

    return (bytes_written);
}

/**
 * get_reverse - Reverses a string and stores it in a buffer.
 * @args: A va_list pointing to the string to be reversed.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored in the buffer.
 */
unsigned int get_reverse(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length)
{
    char *str, *null = "(null)";
    int size, end, i;
    unsigned int bytes_written = 0;

    (void)flags;
    (void)length;

    str = va_arg(args, char *);
    if (str == NULL)
        return (copy_to_buffer(output, null, 6));

    for (size = 0; *(str + size);)
        size++;

    bytes_written += store_string_padding(output, flags, width, precision, size);

    end = size - 1;
    precision = (precision == -1) ? size : precision;
    for (i = 0; end >= 0 && i < precision; i++)
    {
        bytes_written += copy_to_buffer(output, (str + end), 1);
        end--;
    }

    bytes_written += store_trailing_padding(output, bytes_written, flags, width);

    return (bytes_written);
}

/**
 * get_rot13 - Converts a string to ROT13 and stores it in a buffer.
 * @args: A va_list pointing to the string to be converted.
 * @flags: Flag modifiers.
 * @width: A width modifier.
 * @precision: A precision modifier.
 * @length: A length modifier.
 * @output: A buffer_t struct containing a character array.
 *
 * Return: The number of bytes stored in the buffer.
 */
unsigned int get_rot13(va_list args, buffer_t *output, unsigned char flags, int width, int precision, unsigned char length)
{
    char *alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *rot13 = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
    char *str, *null = "(null)";
    int i, j, size;
    unsigned int bytes_written = 0;

    (void)flags;
    (void)length;

    str = va_arg(args, char *);
    if (str == NULL)
        return (copy_to_buffer(output, null, 6));

    for (size = 0; *(str + size);)
        size++;

    bytes_written += store_string_padding(output, flags, width, precision, size);

    precision = (precision == -1) ? size : precision;
    for (i = 0; *(str + i) != '\0' && i < precision; i++)
    {
        for (j = 0; j < 52; j++)
        {
            if (*(str + i) == *(alpha + j))
            {
                bytes_written += copy_to_buffer(output, (rot13 + j), 1);
                break;
            }
        }
        if (j == 52)
            bytes_written += copy_to_buffer(output, (str + i), 1);
    }

    bytes_written += store_trailing_padding(output, bytes_written, flags, width);

    return (bytes_written);
}

