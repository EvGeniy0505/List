#include "list.h"



int main()
{
    List list = C_tor();

    for(size_t i = 0; i < 5; i++)
    {
        Insert_elem_after_num(&list, (list_elem)i + 1, i);
    }

    Insert_elem_after_num(&list, 52, 3);

    // dump_to_dot(&list);

    Pop_elem(&list, 3);

    // dump_to_dot(&list);

    Insert_elem_before_num(&list, 10, 2);

    // dump_to_dot(&list);

    Insert_first_elem(&list, 3);

    dump_to_dot(&list);

    Search_elem_by_val(&list, 52);

    printf("Ptr on first elem: %p\n", Ptr_on_first_elem);

    D_tor(&list);

    return 0;
}