#include "../includes/fdf.h"

void		push(t_coord_val **coords_stack, t_coord_val *new)
{
    if (coords_stack)
    {
        if (new)
            new->next = *coords_stack;
        *coords_stack = new;
    }
}

t_coord_val	*pop(t_coord_val **coords_stack)
{
    t_coord_val *top;

    top = NULL;
    if (coords_stack && *coords_stack)
    {
        top = *coords_stack;
        *coords_stack = (*coords_stack)->next;
    }
    return (top);
}

