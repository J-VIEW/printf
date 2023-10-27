#include "main.h"

/**
 * _printf - Outputs a formatted string.
 * @format: Character string to print - may contain directives.
 *
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{

    buffer_t *output;
    va_list args;

    int result;

    if (format == NULL)
        return (-1);
    output = initialize_buffer();
    if (output == NULL)
        return (-1);

    va_start(args, format);
    result = execute_printf(format, args, output);
    va_end(args);

    return (result);
}

