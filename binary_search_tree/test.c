#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <stdlib.h>

#include "binary_search_tree.h"

int 
main(int argc, char* argv[]) {
    ssize_t size; 
    unsigned num;
    p_bst bst;
    p_node pn1, pn2;
    int nums[] = {};
    srand((unsigned)time(NULL));

    if (argc != 2) {
        printf("main: parameter mismatch.\n");
        exit(-1);
    }

    size = atoi(argv[1]);

    bst = create_bst();
    for (ssize_t i = 0; i < size; ++i) {
        num = rand() % 100;
        printf("The %d-th insert key %d\n", i + 1, num);
        insert_key(bst, num);
    }

    inorder_traverse(bst);
    printf("delete node: ");
    scanf("%d", &num);

    remove_key(bst, num);
    inorder_traverse(bst);

    return 0;
}
