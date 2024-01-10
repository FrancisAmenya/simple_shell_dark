#include "main.h"
/**
 * free_my_long - frees long memory
 * @argv: long of user string,
 *
 * Return: exit status, 0 if success, 1 if error, -1 if fail
 */
int free_my_long(long *argv)
{

    free(argv);
    argv = NULL;
    
    return (0);
}
