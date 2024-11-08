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
    list -> node[list -> size - 1].next =  0;
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
    FILE* f_dot = fopen("list.dot", "wr");

    for(size_t i = 0; i < list -> tail; i++)
    {
        if(list -> node[i].data == POIZON)
            fprintf(f_dot, "%d ", 0);
        else
            fprintf(f_dot, "node[%d ", list -> node[i].data);
    }

    putc('\n', f_dot);

    for(size_t i = 0; i < list -> tail; i++)
    {
        fprintf(f_dot, "%d ", list -> node[i].next);
    }

    putc('\n', f_dot);

    for(size_t i = 0; i < list -> tail; i++)
    {
        if(list -> node[i].prev < 0)
            fprintf(f_dot, "%d ", list -> node[i].prev);
        else
            fprintf(f_dot, "%d ", list -> node[i].prev);
    }

    putc('\n', f_dot);

    // printf("head = %zu\ntail = %zu\nfree = %zu\n", list -> head, list -> tail, list -> free);

    fclose(f_dot);
}

void dump_to_dot(List* list)
{
    FILE* f_dot = fopen("output/list.dot", "wr");

    fprintf(f_dot, "digraph LIST {\n\trankdir=LR;\n\tbgcolor = \"green:yellow\";\n");

    fprintf(f_dot, "\tnode0 [shape=record, color=red, label=\" NULL LIST ELEMENT | index=0 | data=POIZON | next=%d | prev=%d \" ];\n",
                                                                                            list -> node[0].next,
                                                                                            list -> node[0].prev);
    size_t i = 0;

    while(list -> node[i].next != 0)
    {
        fprintf(f_dot, "\tnode%zu -> node%zu;\n", i, list -> node[i].next);

        i = list -> node[i].next;

        fprintf(f_dot, "\tnode%zu [shape=record, color=blue, label=\" index=%d | data=%d | next=%d | prev=%d \" ];\n", i, i,
                                                                                                    list -> node[i].data,
                                                                                                    list -> node[i].next,
                                                                                                    list -> node[i].prev);
    }

    fprintf(f_dot, "\tsubgraph cluster0 {\n\t\tnode [style=filled,color=white];\n\t\tstyle=filled;\n\t\tcolor=lightgrey;\n");

    for(size_t i = 0; i < list -> size; i++)
    {
        if(list -> node[i].prev == -1)
        {
            fprintf(f_dot, "\t\tnode%zu -> node%zu;\n", i, list -> node[i].next);

            fprintf(f_dot, "\t\tnode%zu [shape=record, color=white, label=\" index=%d | data=POIZON | next=%d | prev=%d \" ];\n", i, i,
                                                                                                    list -> node[i].next,
                                                                                                    list -> node[i].prev);
        }
    }

    fprintf(f_dot, "\t\tlabel = \"Empty fields\";\n\t}\n");

    fprintf(f_dot, "\tnode%zu -> node0;\n", i);

    fprintf(f_dot, "\t\"free = %zu\";\n", list -> free);

    fprintf(f_dot, "}");

    fclose(f_dot);
}

int Adress_not_list_elem(size_t num, List* list)
{
    if(list -> size < num && list -> node[num].prev != -1)
        printf("\n\nABOBUS ERROR YOU HAVE NOT %d ELEMENT!!!\n\n\n", num);
        return 0;
    return 1;
}

int Pop_null_elem(size_t num)
{
    if(num == 0)
        printf("\n\nABOBUS ERROR DO NOT TOUCH NULL ELEMENT!!!\n\n\n");
        return 0;
    return 1;
}

void D_tor(List* list)
{
    list -> free = POIZON;
    list -> head = POIZON;
    list -> tail = POIZON;
    list -> size = POIZON;

    free(list -> node);
}