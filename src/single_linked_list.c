#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <sys/types.h>

#include "header.h"
#include "single_linked_list.h"

typedef struct SingleLinkedListNode   sll_node;
typedef struct SingleLinkedListNode*  psll_node;

static psll_node CreateNode(sll_data_t);
static psll_node FindPrev(p_sll, size_t);
static psll_node FindNode(p_sll, size_t);

/* @struct 
 *
 * Node in a single linked list.
 */
struct SingleLinkedListNode {
    /* pointer to data stored in this node */
    sll_data_t     data;
    /* next node in this list */
    psll_node      next;
}; 

/* @struct
 *
 * Single linked list.
 */
struct SingleLinkedList {
    /* the first node with valid data */
    psll_node    head;
    /* the number of nodes in this list */
    size_t      length;
};

ds_stat
SingleLinkedList_Init(p_sll* list) {
    /* 
     * if the given list pointing to a non-null
     * pointer, we assume it has been initialized,
     * and we leave it unchanged.
     */
    if (*list != NULL)
        return DS_ERROR;

    *list = malloc(sizeof(struct SingleLinkedList));

    if (!list) 
        return DS_ERROR;

    assert(list);
    (*list)->head   = NULL;
    (*list)->length = 0;

    return DS_OK;
}

static psll_node
CreateNode(sll_data_t data) {
    psll_node    nd = malloc(sizeof(sll_node));

    if (!nd)
        return NULL;
    assert(nd);

    nd->data = data;
    nd->next = NULL;

    return nd;
}

static psll_node
FindPrev(p_sll list, size_t index) {
    psll_node prev;
    size_t    i;

    if (SingleLinkedList_Empty(list) == DS_TRUE)
        return NULL;
    if (index < 0 || index > list->length)
        return NULL;

    for (i = 1, prev = list->head; i < index; 
         i++, prev = prev->next) ;
    
    assert(prev);
    return prev;
}

static psll_node
FindNode(p_sll list, size_t index) {
    psll_node nd;
    size_t    i;

    if (SingleLinkedList_Empty(list) == DS_TRUE)
        return NULL;
    if (index < 0 || index >= list->length )
        return NULL;

    for (i = 0, nd = list->head; i < index; i++, nd = nd->next);

    assert(nd);
    return nd;
}

ds_stat
SingleLinkedList_Insert(p_sll list, size_t index, 
                        sll_data_t data) {
    psll_node    nd, prev;

    if (!list) return DS_ERROR;
    if (index < 0 || index > list->length || !data)
        return DS_ERROR;
    if (!(nd = CreateNode(data)))
        return DS_ERROR;

    assert(nd);
    assert(list);

    if (!list->head) {
        list->head = nd;
    } else {
        if (index == 0) {
            nd->next = list->head;
            list->head = nd;
        } else {
            prev = FindPrev(list, index);
            
            assert(prev);

            nd->next = prev->next;
            prev->next = nd;
        }
    }

    list->length++;

    return DS_OK;
}

ds_stat
SingleLinkedList_InsertHead(p_sll list, sll_data_t data) {
    return SingleLinkedList_Insert(list, 0, data);
}

ds_stat
SingleLinkedList_InsertTail(p_sll list, sll_data_t data) {
    if (!list) return DS_ERROR;

    return SingleLinkedList_Insert(list, list->length, data);
}

ds_stat
SingleLinkedList_Delete(p_sll list, size_t index, sll_data_t* re) {
    psll_node    nd, prev;

    if (SingleLinkedList_Empty(list) == DS_TRUE)
        return DS_ERROR;
    if (index < 0 || index >= list->length)
        return DS_ERROR;

    if (index == 0) {
        nd = list->head;
        list->head = list->head->next;
    } else {
        prev = FindPrev(list, index);

        assert(prev);

        nd = prev->next;
        prev->next = prev->next->next;
    }

    assert(nd);
    if (re)
        *re = nd->data;
    free(nd);

    list->length--;

    return DS_OK;
}

ds_stat
SingleLinkedList_DeleteHead(p_sll list, sll_data_t* re) {
    return SingleLinkedList_Delete(list, 0, re);
}

ds_stat
SingleLinkedList_DeleteTail(p_sll list, sll_data_t* re) {
    return SingleLinkedList_Delete(list, list->length - 1, re);
}

ds_bool
SingleLinkedList_Empty(p_sll list) {
    if (!list || list->length == 0)
        return DS_TRUE;
    return DS_FALSE;
}

size_t
SingleLinkedList_Size(p_sll list) {
    if (!list) return 0;

    return list->length;
}

void
SingleLinkedList_Map(p_sll list, mapfunc map, void* vp) {
    psll_node nd;

    if (!list) return;
    assert(map);

    for (nd = list->head; nd; nd = nd->next)
        map(&nd->data, vp);
}

ds_stat
SingleLinkedList_Concat(p_sll list1, p_sll list2) {
    psll_node iter;

    if (!list1 || !list2)
        return DS_ERROR;

    for (iter = list2->head; iter; iter = iter->next)
        SingleLinkedList_InsertTail(list1, iter->data);

    return DS_OK;
}

p_sll
SingleLinkedList_Copy(p_sll list) {
    p_sll     cpy = NULL;
    psll_node iter;

    if (SingleLinkedList_Init(&cpy) == DS_ERROR)
        return NULL;

    assert(cpy);

    for (iter = list->head; iter; iter = iter->next)
        SingleLinkedList_InsertTail(cpy, iter->data);

    return cpy;
}
