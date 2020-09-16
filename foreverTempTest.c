#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "inputFunc.h"
#include "function.h"
#include "interaction.h"

int main(int argc, char const *argv[])
{
    /* code */
    printf("Test Begin!\n");
    struct medicine_list *list = inter_create_medicine_list();
    struct medicine *temp = list->head;
    while (temp != NULL)
    {
        printf("%s\n", temp->name);
        temp = temp->next;
    }

    inter_search_medicine(list);
    inter_create_used_medicine(list);

    return 0;
}
