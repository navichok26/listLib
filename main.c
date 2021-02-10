#include "list.h"

int main(void)
{
    List *list = list_new("drs", 555, 1.23, "Hello world");
    list_push(list, "d", 20657);
    list_print(list);
    // List *temp = push_list(list, "d", 571);

    // temp = push_list(temp, "b", 1);
    // temp = push_list(temp, "c", 2);
    // temp = push_list(temp, "d", 3);

    // print_list(list);
    // free_list(list);

    return 0;
}
