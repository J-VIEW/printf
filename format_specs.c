#include "main.h"

/**
 * match_flags - Match and handle flag characters in the format string.
 * @flag: A pointer to a potential string of flags.
 * @index: An index counter for the original format string.
 *
 * Returns: (A value representing matched flags, or 0 if none are matched).
 */
unsigned char match_flags(const char *flag, char *index)
{
    int i, j;
    unsigned char matched_flags = 0;
    flag_t flags[] = {
        {'+', PLUS},
        {' ', SPACE},
        {'#', HASH},
        {'0', ZERO},
        {'-', NEG},
        {0, 0}};

    for (i = 0; flag[i]; i++)
    {
        for (j = 0; flags[j].flag != 0; j++)
        {
            if (flag[i] == flags[j].flag)
            {
                (*index)++;
                if (matched_flags == 0)
                    matched_flags = flags[j].value;
                else
                    matched_flags |= flags[j].value;
                break;
            }
        }
        if (flags[j].value == 0)
            break;
    }

    return (matched_flags);
}

/**
 * match_width - Match and handle a width modifier in the format string.
 * @args: A va_list of arguments.
 * @modifier: A pointer to a potential width modifier.
 * @index: An index counter for the original format string.
 *
 * Returns: (The matched width value, or 0 if none are matched).
 */
int match_width(va_list args, const char *modifier, char *index)
{
    int width_value = 0; /* Initialize width_value to 0*/

    while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
    {
        (*index)++;

        if (*modifier == '*')
        {
            width_value = va_arg(args, int); /*Set width_value to the argument value*/
            if (width_value <= 0)
                return (0);
            return (width_value);
        }

        width_value *= 10;
        width_value += (*modifier - '0');
        modifier++;
    }

    return (width_value); /* Return the accumulated width value*/
}

/**
 * match_precision - Match and handle a precision modifier in the format string.
 * @args: A va_list of arguments.
 * @modifier: A pointer to a potential precision modifier.
 * @index: An index counter for the original format string.
 *
 * Returns: (The matched precision value, 0 for empty or negative modifiers, or -1 for invalid modifiers).
 */
int match_precision(va_list args, const char *modifier, char *index)
{
    int precision_value = 0;

    if (*modifier != '.')
    {
        return (-1);
    }

    modifier++;
    (*index)++;

    if ((*modifier <= '0' || *modifier > '9') && *modifier != '*')
    {
        if (*modifier == '0')
        {
            (*index)++;
        }
        return (0);
    }

    while ((*modifier >= '0' && *modifier <= '9') || (*modifier == '*'))
    {
        (*index)++;

        if (*modifier == '*')
        {
            precision_value = va_arg(args, int);
            if (precision_value <= 0)
                return (0);
            return (precision_value);
        }

        precision_value *= 10;
        precision_value += (*modifier - '0');
        modifier++;
    }

    return (precision_value);
}

/**
 * match_specifiers - Match a conversion specifier and return the corresponding conversion function.
 * @specifier: A pointer to a potential conversion specifier.
 *
 * Returns: (A pointer to the matched conversion function or NULL if none are matched).
 */
unsigned int (*match_specifiers(const char *specifier))(va_list, buffer_t *, unsigned char, int, int, unsigned char)
{
    int i;
    converter_t converters[] = {
        {'c', get_char},
        {'s', get_string},
        {'d', signed_integer},
        {'i', signed_integer},
        {'%', get_percent},
        {'b', get_binary},
        {'u', unsigned_integer},
        {'o', get_octal},
        {'x', get_lowercase_hex},
        {'X', get_uppercase_hex},
        {'S', get_string},
        {'p', get_address},
        {'r', get_reverse},
        {'R', get_rot13},
        {0, NULL}};

    for (i = 0; converters[i].func; i++)
    {
        if (converters[i].specifier == *specifier)
            return converters[i].func;
    }

    return (NULL);
}

/**
 * get_length - Matches length modifiers with their corresponding value.
 * @modifier: A pointer to a potential length modifier.
 * @index: A pointer to an index counter for the original format string.
 *
 * Return: If a length modifier is matched, it returns its corresponding value.
 *         Otherwise, it returns 0.
 */
unsigned char get_length(const char *modifier, char *index)
{
    if (*modifier == 'h')
    {
        (*index)++;
        return (SHORT);
    }
    else if (*modifier == 'l')
    {
        (*index)++;
        return (LONG);
    }

    return (0);
}

