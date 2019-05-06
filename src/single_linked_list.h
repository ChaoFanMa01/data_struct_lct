/* @file single_linked_list.h
 *
 * Single linked list.
 *
 * In this file, the prefix sll stands for 
 * single linked list.
 */


#ifndef SINGLE_LINKED_LIST_H
#define SINGLE_LINKED_LIST_H

struct SingleLinkedList;

typedef struct SingleLinkedList*    p_sll;
typedef void*                       sll_data_t;
typedef int (*sll_comp_func)(sll_data_t, sll_data_t);
typedef void (*mapfunc)(sll_data_t*, void*);

/* @fn
 * Initialize a non-initialized single linked list.
 */
extern ds_stat SingleLinkedList_Init(p_sll*);

/* @fn
 * Insert a data to designed position.
 * @param list The list where data will be inserted.
 * @param index The insertion position of the data.
 * @param data Pointer to the data being inserted.
 */
extern ds_stat SingleLinkedList_Insert(p_sll list, size_t index, sll_data_t data);

/* @fn
 * Insert a data to the head of a list.
 */
extern ds_stat SingleLinkedList_InsertHead(p_sll, sll_data_t);

/* @fn
 * Inset a data to the tail of a list.
 */
extern ds_stat SingleLinkedList_InsertTail(p_sll, sll_data_t);

/* @fn
 * Delete the node at given position.
 * 
 * @param list From which the node is deleted.
 * @param index The position of the node to be deleted.
 * @param re The data of the deleted node will be returned
 *           through this parameter.
 */
extern ds_stat SingleLinkedList_Delete(p_sll list, size_t index, sll_data_t* re);

/* @fn
 * Delete the first node of a list.
 */
extern ds_stat SingleLinkedList_DeleteHead(p_sll, sll_data_t*);

/* @fn
 * Delete the last node of a list.
 */
extern ds_stat SingleLinkedList_DeleteTail(p_sll, sll_data_t*);

/* @fn
 * Return the length of this list.
 */
extern size_t SingleLinkedList_Size(p_sll);

/* @fn
 * Check whether the given list is empty.
 */
extern ds_bool SingleLinkedList_Empty(p_sll);

/* @fn
 * Do something to data of each node in list according
 * to the given function.
 */
extern void SingleLinkedList_Map(p_sll list, mapfunc map, void* vp);

/* @fn
 * Concatenate two lists, i.e., joining list2 to the end of 
 * list1 without varying their internal order.
 */
extern ds_stat SingleLinkedList_Concat(p_sll list1, p_sll list2);

/* @fn
 * Perform a deep copy of given list, and return new list.
 */
extern p_sll SingleLinkedList_Copy(p_sll);
#endif
