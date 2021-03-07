#include "list.h"
#include <stdlib.h>
#include <stdbool.h>

static inline void list_add_node_t(node_t **list, node_t *node_t)
{
    node_t->next = *list;
    *list = node_t;
}

static inline void list_concat(node_t **left, node_t *right)
{
    while (*left) {
        left = &((*left)->next);
    }
    *left = right;
}

void quicksort(node_t **list)
{
    #define MAX_LEVELS 1000
    node_t **list_arr[MAX_LEVELS] = { list };
    node_t *l_arr[MAX_LEVELS], *r_arr[MAX_LEVELS], *piv_arr[MAX_LEVELS];
    bool left_sorted[MAX_LEVELS], right_sorted[MAX_LEVELS];
    int i = 0;
    while (i >= 0) {
        if (*list_arr[i]) {
            if (left_sorted[i]) {
                if (right_sorted[i]) {
                    goto CONCAT;
                } else {
                    goto SORT_RIGHT;
                }
            }
            PAIRTITION: {
                node_t *left = NULL, *right = NULL, *pivot = *list_arr[i];
                int value = pivot->value;
                node_t *p = pivot->next;
                pivot->next = NULL;

                while (p) {
                    node_t *n = p;
                    p = p->next;
                    list_add_node_t(n->value > value ? &right : &left, n);
                }
                l_arr[i] = left;
                r_arr[i] = right;
                piv_arr[i] = pivot;
            }
            SORT_LEFT: {
            	left_sorted[i] = true;
            	left_sorted[i+1] = false;
                right_sorted[i+1] = false;
                list_arr[i+1] = &l_arr[i];
                i++;
                continue;
            }
            SORT_RIGHT: {
                right_sorted[i] = true;
                left_sorted[i+1] = false;
                right_sorted[i+1] = false;
                list_arr[i+1] = &r_arr[i];
                i++;
                continue;
            }
            CONCAT: {
                node_t *result = NULL;
                list_concat(&result, l_arr[i]);
                list_concat(&result, piv_arr[i]);
                list_concat(&result, r_arr[i]);
                *list_arr[i] = result;
                i--;
            }
        } else {
            i--;
        }
    }
    *list = *list_arr[0];
}
