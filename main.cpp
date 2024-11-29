#include "list.h"



int main()
{
    List list = List_ctor();

    for(size_t i = 0; i < 5; i++)
    {
        Insert_elem_after_num(&list, (list_elem)i + 1, i);
    }

    Insert_elem_after_num(&list, 52, 3);

    dump_to_dot(&list, 1);

    Pop_elem(&list, 3);

    dump_to_dot(&list, 2);

    Insert_elem_before_num(&list, 10, 2);

    dump_to_dot(&list, 3);

    Insert_first_elem(&list, 3);

    Insert_last_elem(&list, 1);
    Insert_last_elem(&list, 1);

    dump_to_dot(&list, 4);

    printf("list tail = %zu\n", list.tail);
    printf("list size = %zu\n", list.size);

    Insert_last_elem(&list, 1);
    Insert_last_elem(&list, 1);
    Insert_last_elem(&list, 1);
    Insert_last_elem(&list, 1);

    dump_to_dot(&list, 5);

    Search_elem_by_val(&list, 52);

    printf("Ptr on first elem: %p\n", Ptr_on_first_elem(&list));

    printf("Ptr on second elem: %p\n", Ptr_on_elem_after_num(&list, 1));

    List_dtor(&list);

    return 0;
}