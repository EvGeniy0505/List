#include "list.h"



int main()
{
    List list = C_tor();

    for(int i = 0; i < 5; i++)
    {
        Push_elem_after_num(&list, i + 1, i);
    }

    dump(&list);

    Push_elem_after_num(&list, 52, 3);

    dump(&list);

    D_tor(&list);

    return 0;
}