#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#include "../src/header.h"
#include "../src/single_linked_list.h"

#define   MAX    1000

void display(sll_data_t*, void*);
int  cmp(sll_data_t, sll_data_t);
void clear_op(sll_data_t*);

int main(int argc, char* argv[]) {
    p_sll        plist = NULL, plist1 = NULL;
    int          test_array[MAX];
    int          size, i, num, tmp;
    int*         re;
    size_t       index;
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

/* sort
    if (SingleLinkedList_BubbleSort_D(plist, cmp) == DS_OK) {
        SingleLinkedList_Map(plist, display, NULL);
        printf("\n");
    } else {
        printf("cannot sort\n");
    }
*/

/* max min
    if (SingleLinkedList_Min(plist, cmp, &index) == DS_OK)
        printf("The index of minimum node is %ld\n", index);
    else
        printf("Empty list\n");
*/

/* maxdata mindata
    if (SingleLinkedList_MinData(plist, cmp, (void**)&re) == DS_OK)
        printf("The min data is %d\n", *re);
    else
        printf("Empty list\n");
*/

/* contain
    for (i = 0; i < 5; i++) {
        size = rand() % SingleLinkedList_Size(plist) + 5;
        if (SingleLinkedList_Contain(plist, &test_array[size], 
                                     cmp) == DS_TRUE)
            printf("%d in this list\n", test_array[size]);
        else
            printf("no such data: %d\n", test_array[size + 5]);
    }
*/

/* clear
    SingleLinkedList_Clear(plist, clear_op);
    printf("the length is %ld\n", SingleLinkedList_Size(plist));
*/

/* destroy
    SingleLinkedList_Destroy(&plist, clear_op);
    if (!plist)
        printf("Destroyment over!\n");
*/

/* index
    for (i = 0; i < 5; i++) {
        size = rand() % SingleLinkedList_Size(plist) + 5;
        if (SingleLinkedList_Index(plist, &test_array[size], 
                                   &index, cmp) == DS_OK)
            printf("The index of %d is %ld\n", test_array[size], index);
        else
            printf("no such data: %d\n", test_array[size + 5]);
    }
*/

/* replace
    for (i = 0; i < 5; i++) {
        size = rand() % SingleLinkedList_Size(plist);
        tmp = rand() % SingleLinkedList_Size(plist);
        num = SingleLinkedList_Replace(plist, size, &test_array[tmp]);
        printf("Relace %dth node's data with %d\n", size, test_array[tmp]);
        SingleLinkedList_Map(plist, display, NULL);
        printf("\n");
    }
*/

/* get data
    for (i = 0; i < 5; i++) {
        size = rand() % SingleLinkedList_Size(plist);
        num = SingleLinkedList_GetData(plist, size, (sll_data_t*)&re);
        printf("The %dth node's data is %d\n", size, *re);
    }
*/

/* copy
    plist1 = SingleLinkedList_Copy(plist);
    printf("copy:\n");
    SingleLinkedList_Map(plist1, display, NULL);
    printf("\n");
*/

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

int
cmp(sll_data_t d1, sll_data_t d2) {
    int *c1 = (int*)d1, *c2 = (int*)d2;
    return (*c1 - *c2);
}

void
clear_op(sll_data_t* d)
{
    int*    data = (int*)(*d);
    printf("delete %d\n", *data);
}
