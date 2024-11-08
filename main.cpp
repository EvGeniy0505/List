#include "list.h"



int main()
{
    List list = C_tor();

    for(int i = 0; i < 5; i++)
    {
        Push_elem_after_num(&list, i + 1, i);
    }

    Push_elem_after_num(&list, 52, 3);

    Pop_elem(&list, 3);

    Push_elem_before_num(&list, 10, 2);

    dump_to_dot(&list);

    D_tor(&list);

    return 0;
}