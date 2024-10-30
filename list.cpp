#include <stdlib.h>

#include "list.h"

#define SIZE_LIST 52
#define POIZON    0xDEDAB0BA

List C_tor()
{
    List list = {};

    list.size = SIZE_LIST;

    list.node = (List_node*) calloc(SIZE_LIST, sizeof(*list.node));

    list.node[0].data = POIZON;
    list.node[0].next = 0;
    list.node[0].prev = 0;

    Fill_in(&list);

    list.head = 1;
    list.tail = 1;
    list.free = 1;

    return list;
}

void Fill_in(List* list)
{
    for(int i = list -> head; i < list -> size - 1; i++)
    {
        list -> node[i].data = POIZON;
        list -> node[i].next = i + 1;
        list -> node[i].prev = -1;
    }

    list -> node[list -> size - 1].data = POIZON;
    list -> node[list -> size - 1].next = 0;
    list -> node[list -> size - 1].prev = -1;
}

Errors Push_last_elem(List* list, list_elem new_elem)
{
    list -> node[list -> tail].data = new_elem;
    list -> node[list -> tail].next = list -> tail;
    ++list -> tail;

    return ALL_OKEY;
}

Errors Push_first_elem(List* list, list_elem new_elem)
{

}

Errors Push_elem_after_num(List* list, list_elem new_elem, size_t num)
{
    list -> node[list -> free].data = new_elem;
    list -> node[list -> free].next = num;
    list -> node[num].next = list -> free;
    ++list -> free;

    return ALL_OKEY;
}

void dump(List* list)
{
    for(int i = 1; i < list -> head; i++)
    {
        printf("%d ", list -> node[list -> node[i].next]);
    }

    putchar('\n');
}

void D_tor(List* list)
{
    list -> free = POIZON;
    list -> head = POIZON;
    list -> tail = POIZON;
    list -> size = POIZON;

    free(list -> node);
}