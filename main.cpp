#include "list.h"



int main()
{
    List list = C_tor();

    Push_elem_after_num(&list, 2, 6);

    dump(&list);

    Push_elem_after_num(&list, 3, 2);

    dump(&list);

    Push_elem_after_num(&list, 4, 3);

    dump(&list);

    Push_elem_after_num(&list, 5, 1);

    dump(&list);

    D_tor(&list);

    return 0;
}