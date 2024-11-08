#include <stdlib.h>
#include <assert.h>
#include <string.h>

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
    assert(list);

    for(size_t i = 1; i < list -> size - 1; i++)
    {
        list -> node[i].data = POIZON;
        list -> node[i].next = (int)i + 1;
        list -> node[i].prev = -1;
    }

    list -> node[list -> size - 1].data = POIZON;
    list -> node[list -> size - 1].next =  0;
    list -> node[list -> size - 1].prev = -1;
}


Errors Insert_elem_after_num(List* list, list_elem new_elem, size_t num)
{
    assert(list);

    // if(Adress_not_list_elem(num, list))
    //     return NOT_OKEY;

    size_t new_elem_pos = list -> free;

    int next_free_val = list -> node[new_elem_pos].next;

    list -> node[new_elem_pos].data = new_elem;

    list -> node[new_elem_pos].next = list -> node[num].next;

    list -> node[new_elem_pos].prev = (list_elem)num;

    list -> node[num].next = (list_elem)new_elem_pos;

    list -> node[list -> node[new_elem_pos].next].prev = (list_elem)new_elem_pos;

    list -> free = next_free_val;

    ++list -> tail;

    return ALL_OKEY;
}

Errors Insert_first_elem(List* list, list_elem new_elem)
{
    assert(list);

    Insert_elem_after_num(list, new_elem, 0);

    return ALL_OKEY;
}

Errors Insert_elem_before_num(List* list, list_elem new_elem, size_t num)
{
    assert(list);

    Insert_elem_after_num(list, new_elem, list -> node[num].prev);

    return ALL_OKEY;
}

Errors Insert_last_elem(List* list, list_elem new_elem)
{
    assert(list);

    Insert_elem_before_num(list, new_elem, 0);

    return ALL_OKEY;
}

int* Ptr_on_elem_after_num(List* list, size_t num)
{
    assert(list);
    return &(list -> node[num].next);
}

int* Ptr_on_elem_before_num(List* list, size_t num)
{
    assert(list);
    return &(list -> node[num].prev);
}

int* Ptr_on_last_elem(List* list)
{
    assert(list);
    return &(list -> node[0].prev);
}


int* Ptr_on_first_elem(List* list)
{
    assert(list);
    return &(list -> node[0].next);
}

void Search_elem_by_val(List* list, list_elem val)
{
    assert(list);

    int flag = 0;
    size_t num_elem = 1;
    int i = list -> node[0].next;

    while(list -> node[i].next != 0)
    {
        if(list -> node[i].data == val)
        {
            printf("Your element index: %d\nYour element num in turn: %zu\n", i, num_elem);
            ++flag;
        }
        ++num_elem;
        i = list -> node[i].next;
    }

    if(flag == 0)
        printf("Your element is not in list\n");
}

Errors Pop_elem(List* list, size_t num)
{
    assert(list);

    // if(Adress_not_list_elem(num, list) || Pop_null_elem(num))
    //     return NOT_OKEY;

    list -> node[num].data = POIZON;

    list -> node[list -> node[num].prev].next = list -> node[num].next;

    list -> node[list -> node[num].next].prev = list -> node[num].prev;

    list -> node[num].next = (list_elem)list -> free;

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
        if(list -> node[i].data == (int)POIZON)
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

void dump_to_dot(List* list, int num_graph)
{
    FILE* f_dot = fopen("output/list.dot", "w");

    assert(f_dot);
    assert(list);
    if(ferror(f_dot))
        fprintf(stderr, "FILE OPEN ERROR!!!\n");


    fprintf(f_dot, "digraph LIST%d {\n\trankdir=LR;\n\tbgcolor = \"green:yellow\";\n", num_graph);

    fprintf(f_dot, "\t\"free = %zu\";\n", list -> free);

    fprintf(f_dot, "\tsubgraph cluster0 {\n\t\tnode [style=filled,color=white];\n"
                   "\t\tstyle=filled;\n\t\tcolor=lightgrey;\n");

    for(size_t i = 0; i < list -> size; i++)
    {
        if(list -> node[i].prev == -1 && list -> node[i].next == 0)
        {
            fprintf(f_dot, "\t\tnode%zu [shape=record, color=white,"
                           "label=\" index=%zu | data=POIZON | next=%d | prev=%d \" ];\n",
                           i, i, list -> node[i].next, list -> node[i].prev);
        }
        else if(list -> node[i].prev == -1)
        {
            fprintf(f_dot, "\t\tnode%zu [shape=record, color=white,"
                           "label=\" index=%zu | data=POIZON | next=%d | prev=%d \" ];\n",
                           i, i, list -> node[i].next, list -> node[i].prev);

            fprintf(f_dot, "\t\tnode%zu -> node%d;\n", i, list -> node[i].next);
        }

    }

    fprintf(f_dot, "\t\tlabel = \"Empty fields\";\n\t}\n");


    fprintf(f_dot, "\tnode0 [shape=record, color=red,"
                   "label=\" NULL LIST ELEMENT | index=0 | data=POIZON | next=%d | prev=%d \" ];\n",
                   list -> node[0].next, list -> node[0].prev);

    size_t i = 0;

    while(list -> node[i].next != 0)
    {
        fprintf(f_dot, "\tnode%zu -> node%d;\n", i, list -> node[i].next);

        i = list -> node[i].next;

        fprintf(f_dot, "\tnode%zu [shape=record, color=blue,"
                       "label=\" index=%zu | data=%d | next=%d | prev=%d \" ];\n",
                       i, i, list -> node[i].data, list -> node[i].next, list -> node[i].prev);
    }

    fprintf(f_dot, "\tnode%zu -> node0;\n", i);

    fprintf(f_dot, "}\n\n");

    fclose(f_dot);

    Dot_file_compile(num_graph);
}

void Dot_file_compile(int num_pucture)
{
    char com1[100] = "dot -Tpng output/list.dot > output/list";
    char com2[5]  = ".png";

    char num_str[3] = "";

    snprintf(num_str, sizeof(num_str), "%d", num_pucture);

    snprintf(com1, sizeof(com1), "%s%s%s", com1, num_str, com2);

    system(com1);
}

int Adress_not_list_elem(size_t num, List* list)
{
    assert(list);

    if(list -> size < num && list -> node[num].prev != -1)
    {
        printf("\n\nABOBUS ERROR YOU HAVE NOT %zu ELEMENT!!!\n\n\n", num);
        return 0;
    }
    return 1;
}

int Pop_null_elem(size_t num)
{
    if(num == 0)
    {
        printf("\n\nABOBUS ERROR DO NOT TOUCH NULL ELEMENT!!!\n\n\n");
        return 0;
    }
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