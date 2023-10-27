#include "main.h"

/**
 * perform_cleanup - Performs cleanup operations for _printf.
 * @args: A va_list of arguments provided to _printf.
 * @output: A buffer_t struct.
 */
void perform_cleanup(va_list args, buffer_t *output)
{
    va_end(args);
    write(1, output->start, output->len);
    free_buffer(output);
}

/**
 * execute_printf - Processes the format string for _printf.
 * @format: Character string to print - may contain directives.
 * @output: A buffer_t struct containing a buffer.
 * @args: A va_list of arguments.
 *
 * Return: The number of characters stored to the output buffer.
 */
int execute_printf(const char *format, va_list args, buffer_t *output)
{
    int i, width, precision, total_printed = 0;
    char tmp;
    unsigned char flags, length;
    unsigned int (*specifier_func)(va_list, buffer_t *, unsigned char, int, int, unsigned char);

    for (i = 0; *(format + i); i++)
    {
        length = 0;
        if (*(format + i) == '%')
        {
            tmp = 0;
            flags = match_flags(format + i + 1, &tmp);
            width = match_width(args, format + i + tmp + 1, &tmp);
            precision = match_precision(args, format + i + tmp + 1, &tmp);
            length = get_length(format + i + tmp + 1, &tmp);

            specifier_func = match_specifiers(format + i + tmp + 1);
            if (specifier_func != NULL)
            {
                i += tmp + 1;
                total_printed += specifier_func(args, output, flags, width, precision, length);
                continue;
            }
            else if (*(format + i + tmp + 1) == '\0')
            {
                total_printed = -1;
                break;
            }
        }
        total_printed += copy_to_buffer(output, (format + i), 1);
        i += (length != 0) ? 1 : 0;
    }
    perform_cleanup(args, output);
    return (total_printed);
}

