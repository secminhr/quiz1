#include "list.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

static void list_free(node_t **list_p)
{
    while (*list_p) {
        node_t *tmp = *list_p;
        *list_p = (*list_p)->next;
        free(tmp);
    }
}

/* 
 *  Return a list with a new node_t.
 *  If allocation failed, function will free the given list and exit.
 */
static node_t *list_make_node_t(node_t *list, int value)
{
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {
        list_free(&list);
        exit(EXIT_FAILURE);
    }
    new->value = value;
    new->next = list;
    return new;
}

static bool list_is_ordered(node_t *list)
{
    bool first = true;
    int value;
    while (list) {
        if (first) {
            value = list->value;
            first = false;
        } else {
            if (list->value < value)
                return false;
            value = list->value;
        }
        list = list->next;
    }
    return true;
}

static void list_display(node_t *list) {
    printf("%s IN ORDER : ", list_is_ordered(list) ? "   " : "NOT");
    while (list) {
        printf("%d ", list->value);
        list = list->next;
    }
    printf("\n");
}

int main(int argc, char **argv) {
    size_t count = 20;
    
    srandom((unsigned int) main);
    node_t *list = NULL;
    while (count--)
        list = list_make_node_t(list, random() % 1024);

    list_display(list);
    quicksort(&list);
    list_display(list);

    if (!list_is_ordered(list))
        return EXIT_FAILURE;

    list_free(&list);
    return EXIT_SUCCESS;
}
