#include <stdlib.h>
#include <assert.h>

#include "list.h"

#define SIZE_LIST 10
#define POIZON    0xDEDAB0BA

List C_tor()
{
    List list = {};

    list.size = SIZE_LIST;

    list.node = (List_node*) calloc(SIZE_LIST, sizeof(*list.node));

    list.node[0].data = POIZON;
    list.node[0].next = 0;
    list.node[0].prev = 0;

    list.head = 1;
    list.tail = 1;
    list.free = 1;

    Fill_in(&list);

    return list;
}

void Fill_in(List* list)
{
    for(size_t i = 1; i < list -> size - 1; i++)
    {
        list -> node[i].data = POIZON;
        list -> node[i].next = i + 1;
        list -> node[i].prev = -1;
    }

    list -> node[list -> size - 1].data = POIZON;
    list -> node[list -> size - 1].next = list -> size;
    list -> node[list -> size - 1].prev = -1;
}


Errors Push_elem_after_num(List* list, list_elem new_elem, size_t num)
{
    assert(list);

    if(Adress_not_list_elem(num, list))
        return NOT_OKEY;

    size_t new_elem_pos = list -> free;

    int next_free_val = list -> node[new_elem_pos].next;

    list -> node[new_elem_pos].data = new_elem;

    list -> node[new_elem_pos].next = list -> node[num].next;

    list -> node[new_elem_pos].prev = num;

    list -> node[num].next = new_elem_pos;

    list -> node[list -> node[new_elem_pos].next].prev = new_elem_pos;

    list -> free = next_free_val;

    ++list -> tail;

    return ALL_OKEY;
}

Errors Push_first_elem(List* list, list_elem new_elem)
{
    Push_elem_after_num(list, new_elem, 0);

    return ALL_OKEY;
}

Errors Push_elem_before_num(List* list, list_elem new_elem, size_t num)
{
    Push_elem_after_num(list, new_elem, list -> node[num].prev);

    return ALL_OKEY;
}

Errors Push_last_elem(List* list, list_elem new_elem)
{
    Push_elem_before_num(list, new_elem, 0);

    return ALL_OKEY;
}

Errors Pop_elem(List* list, size_t num)
{
    assert(list);

    if(Adress_not_list_elem(num, list) || Pop_null_elem(num))
        return NOT_OKEY;

    list -> node[num].data = POIZON;

    list -> node[list -> node[num].prev].next = list -> node[num].next;

    list -> node[list -> node[num].next].prev = list -> node[num].prev;

    list -> node[num].next = list -> free;

    list -> free = num;

    list -> node[num].prev = -1;

    --list -> tail;

    return ALL_OKEY;
}


void dump(List* list)
{
    printf("-----------------LIST------------------\n");
    for(size_t i = 0; i < list -> tail; i++)
    {
        if(list -> node[i].data == POIZON)
            printf("    %d  ", 0);
        else
            printf("    %d  ", list -> node[i].data);
    }

    putchar('\n');

    for(size_t i = 0; i < list -> tail; i++)
    {
        printf("    %d  ", list -> node[i].next);
    }

    putchar('\n');

    for(size_t i = 0; i < list -> tail; i++)
    {
        if(list -> node[i].prev < 0)
            printf("   %d  ", list -> node[i].prev);
        else
            printf("    %d  ", list -> node[i].prev);
    }

    putchar('\n');

    printf("head = %zu\ntail = %zu\nfree = %zu\n", list -> head, list -> tail, list -> free);

    printf("-----------------LIST------------------\n\n\n");
}

int Adress_not_list_elem(size_t num, List* list)
{
    if(num < list -> size && list -> node[num].prev == -1)
        printf("\n\nABOBUS ERROR YOU HAVE NOT %d ELEMENT!!!\n\n\n", num);
        return 1;
    return 0;
}

int Pop_null_elem(size_t num)
{
    if(num == 0)
        printf("\n\nABOBUS ERROR DO NOT TOUCH NULL ELEMENT!!!\n\n\n");
        return 1;
    return 0;
}

void D_tor(List* list)
{
    list -> free = POIZON;
    list -> head = POIZON;
    list -> tail = POIZON;
    list -> size = POIZON;

    free(list -> node);
}