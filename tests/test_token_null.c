#include "../includes/minishell.h"

int main(void)
{
    t_token *list = NULL;
    /* Should not crash or modify list */
    token_add_back(&list, NULL);
    return (list != NULL); /* return 0 on success */
}
