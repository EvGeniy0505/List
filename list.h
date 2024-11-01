#include <stdio.h>

typedef int list_elem;


struct List_node
{
    list_elem data;
    int next;
    int prev;
};

struct List
{
    List_node* node;
    size_t     head;
    size_t     tail;
    int        free;
    size_t     size;
};

enum Errors
{
    ALL_OKEY,
    CHANGE_FIRST_ELEM,
    NOT_OKEY,
};

List C_tor();

void D_tor(List* list);

void Fill_in(List* list);

Errors verificator();

Errors Push_last_elem(List* list, list_elem new_elem);

void Change_first_elem_error(size_t num);

Errors Pop_elem(List* list, size_t num);

Errors Push_elem_after_num(List* list, list_elem new_elem, size_t num);

void dump(List* list);

