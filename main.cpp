#include "list.h"



int main()
{
    List list = C_tor();

    Push_last_elem(&list, 3);
    Push_last_elem(&list, 3);
    Push_last_elem(&list, 3);
    Push_last_elem(&list, 3);

    dump(&list);

    D_tor(&list);

    return 0;
}