#include <stdlib.h>

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
    // list -> node[list -> tail].data = new_elem;
    // list -> node[list -> tail].next = list -> tail;

    // list -> node[list -> tail].prev = list -> free - 1;

    // ++list -> tail;
    // list -> free = list -> node[list -> tail].next;

    Push_elem_after_num(list, new_elem, 0);

    return ALL_OKEY;
}

Errors Push_first_elem(List* list, list_elem new_elem)
{


    return ALL_OKEY;
}

Errors Push_elem_after_num(List* list, list_elem new_elem, size_t num)
{
    ++num;

    Change_first_elem_error(num);

    list -> node[list -> free].data = new_elem;

    list -> node[list -> free].next = num;

    list -> node[num].prev = list -> free - 1;

    list -> node[num].next = list -> free;

    ++list -> free;

    return ALL_OKEY;
}

Errors Pop_elem(List* list, size_t num)
{
    list -> node[num].data = POIZON;

    list -> node[list -> node[num].prev].next = list -> node[num].next;

    list -> node[num].next = list -> free;

    list -> free = num;

    list -> node[list -> free].prev = list -> node[num].prev;

    list -> node[num].prev = -1;

    return ALL_OKEY;
}


void dump(List* list)
{
    printf("-----------------LIST------------------\n");
    for(int i = 0; i < list -> size; i++)
    {
        if(list -> node[i].data == POIZON)
            printf("    %d  ", 0);
        else
            printf("    %d  ", list -> node[i].data);
    }

    putchar('\n');

    for(int i = 0; i < list -> size; i++)
    {
        printf("    %d  ", list -> node[i].next);
    }

    putchar('\n');

    for(int i = 0; i < list -> size; i++)
    {
        if(list -> node[i].prev < 0)
            printf("   %d  ", list -> node[i].prev);
        else
            printf("    %d  ", list -> node[i].prev);
    }

    putchar('\n');

    printf("head = %d\ntail = %d\nfree = %d\n", list -> head, list -> tail, list -> free);
}

void Change_first_elem_error(size_t num)
{
    if(num == 0)
        printf("\n\nABOBUS ERROR NOT TOUCH FIRST ELEMENT!!!\n\n\n");
}

void D_tor(List* list)
{
    list -> free = POIZON;
    list -> head = POIZON;
    list -> tail = POIZON;
    list -> size = POIZON;

    free(list -> node);
}