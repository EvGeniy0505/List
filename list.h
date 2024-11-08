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
    size_t     free;
    size_t     size;
};

enum Errors
{
    ALL_OKEY,
    CHANGE_NULL_ELEM,
    NOT_OKEY,
};

List C_tor();

void D_tor(List* list);

void Fill_in(List* list);

// Errors verificator();

Errors Insert_first_elem(List* list, list_elem new_elem);

Errors Insert_last_elem(List* list, list_elem new_elem);

int Adress_not_list_elem(size_t num, List* list);

int Pop_null_elem(size_t num);

Errors Pop_elem(List* list, size_t num);

void dump_to_dot(List* list);

void Search_elem_by_val(List* list, list_elem val);

int* Ptr_on_elem_after_num(List* list, size_t num);

int* Ptr_on_elem_before_num(List* list, size_t num);

int* Ptr_on_last_elem(List* list);

int* Ptr_on_first_elem(List* list);

Errors Insert_elem_after_num(List* list, list_elem new_elem, size_t num);

Errors Insert_elem_before_num(List* list, list_elem new_elem, size_t num);

void dump(List* list);

