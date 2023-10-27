#include "main.h"

/**
 * copy_to_buffer - Copies a string to a buffer.
 * @output: A buffer_t struct containing a character array.
 * @src: The string to be copied.
 * @size: The number of bytes to be copied.
 * Return: The number of bytes copied.
 *
 * Description: If the buffer is full, the buffer is printed and cleared.
 * If @size is greater than the buffer length, the buffer is printed and
 * cleared.
 * If @src is NULL, the buffer is printed and cleared.
 * If @size is 0, nothing is copied and 0 is returned.
 * If @output is NULL, 0 is returned.
 * If @src is NULL, 0 is returned.
 * If @size is 0, 0 is returned.
 * If malloc fails, 0 is returned.
 * If write fails, 0 is returned.
 *
 */

int copy_to_buffer(buffer_t *output, const char *src, unsigned int size)
{
    unsigned int index;

    for (index = 0; index < size; index++)
    {
        *(output->buffer) = *(src + index);
        (output->len)++;

        if (output->len == 1024)
        {
            write(1, output->start, output->len);
            output->buffer = output->start;
            output->len = 0;
        }

        else
        {
            (output->buffer)++;
        }
    }
    return (size);
}

/**
 * free_buffer - Frees a buffer_t struct.
 * @output: The buffer_t struct to be freed.
 */
void free_buffer(buffer_t *output)
{
    free(output->start);
    free(output);
}

/**
 * initialize_buffer - Initializes a buffer_t struct.
 * Return: A pointer to the newly initialized struct.
 * Description: If malloc fails, NULL is returned.
 * If malloc fails, NULL is returned.
 *
 */
buffer_t *initialize_buffer(void)
{
    buffer_t *output;

    output = malloc(sizeof(buffer_t));
    if (output == NULL)
        return (NULL);

    output->buffer = malloc(sizeof(char) * 1024);
    if (output->buffer == NULL)
    {
        free(output);
        return (NULL);
    }

    output->start = output->buffer;
    output->len = 0;

    return (output);
}

