#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "../src/header.h"
#include "../src/single_linked_list.h"

#define   MAX    1000

void display(sll_data_t*, void*);

int main(int argc, char* argv[]) {
    p_sll     plist = NULL, plist1 = NULL;
    int       test_array[MAX];
    int       size, i, num;
    srand((unsigned)time(NULL));

    if (argc != 2) {
        printf("argument error!\n");
        exit(-1);
    }

    size = atoi(argv[1]);

    for (i = 0; i < size; i++)
        test_array[i] = rand() % 1000;

    if (SingleLinkedList_Init(&plist) == DS_ERROR)
        printf("init error!\n");
    if (SingleLinkedList_Init(&plist1) == DS_ERROR)
        printf("init error!\n");

    for (i = 0; i < size; i++)
//        SingleLinkedList_InsertHead(plist, &test_array[i]);
        SingleLinkedList_InsertTail(plist, &test_array[i]);
    for (i = 0; i < 10; i++)
        SingleLinkedList_InsertTail(plist1, &test_array[i]);

    printf("origin list:\n");
    SingleLinkedList_Map(plist, display, NULL);
    printf("\n");

    plist1 = SingleLinkedList_Copy(plist);
    printf("copy:\n");
    SingleLinkedList_Map(plist1, display, NULL);
    printf("\n");

/* concatenate
    printf("list 2:\n");
    SingleLinkedList_Map(plist1, display, NULL);
    printf("\n");

    SingleLinkedList_Concat(plist, plist1);
    printf("after concat:\n");
    SingleLinkedList_Map(plist, display, NULL);
    printf("\n");
*/

/* head or tail deletion
    for (i = 0; i < 5; i++) {
//        SingleLinkedList_DeleteHead(plist, NULL);
        SingleLinkedList_DeleteTail(plist, NULL);
        SingleLinkedList_Map(plist, display, NULL);
        printf("\n");
    }
*/

/* random deletion
    for (i = 0; i < size - 10; i++) {
        num = rand() % SingleLinkedList_Size(plist);
        printf("Delete the %dth node\n", num);
        SingleLinkedList_Delete(plist, num, NULL);
        SingleLinkedList_Map(plist, display, NULL);
        printf("\n");
    }
*/

    return 0;
}

void
display(sll_data_t* data, void* vp) {
    int **val = (int**)data;
    printf("%4d ", (int)(**val));
}
