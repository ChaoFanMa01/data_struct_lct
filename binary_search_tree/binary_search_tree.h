#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../header.h"

typedef int                 ElemType;
typedef struct bst_node*    p_node;
typedef struct bst*         p_bst;

struct bst_node{
    ElemType    key;
    p_node      left;
    p_node      right;
};

struct bst{
    p_node    root;
    ssize_t   size;
};

p_bst create_bst();
p_node create_node(ElemType);
Status insert_key(p_bst, ElemType);
void inorder_traverse(p_bst);
void inorder(p_node, ssize_t);
void preorder_traverse(p_bst);
void preorder(p_node, ssize_t);
void postorder_traverse(p_bst);
void postorder(p_node, ssize_t);
Bool isEmpty(p_bst);
ssize_t size(p_bst);
ElemType min(p_bst);
ElemType max(p_bst);
p_node min_node(p_bst);
p_node min_subtree_node(p_node);
p_node max_node(p_bst);
p_node max_subtree_node(p_node);
p_node find_node(p_bst, ElemType);
p_node find_subtree_node(p_node, ElemType);
p_node find_parent(p_bst, ElemType);
p_node find_subtree_parent(p_node, ElemType);
Status remove_key(p_bst, ElemType);

p_bst
create_bst() {
    p_bst bst;

    if ((bst = (p_bst)malloc(sizeof(struct bst))) == NULL) {
        printf("create_bst: memory allocation error\n");
        exit(OVERFLOW);
    }
    bst->root = NULL;
    bst->size = 0;
    return bst;
}

p_node
create_node(ElemType key) {
    p_node pn;

    if ((pn = (p_node)malloc(sizeof(struct bst_node))) == NULL) {
        printf("create_node: memory allocation error\n");
        exit(OVERFLOW);
    }

    pn->key = key;
    pn->left = NULL;
    pn->right = NULL;
    
    return pn;
}

Status 
insert_key(p_bst bst, ElemType key) {
    p_node     pn = bst->root;

    while (pn != NULL)
        if (pn->key > key) {
            if (pn->left != NULL)
                pn = pn->left;
            else
                break;
        } else {
            if (pn->right != NULL)
                pn = pn->right;
            else
                break;
        }
    if (!bst->root) {
        bst->root = create_node(key);
    } else if (pn->key > key) {
        pn->left = create_node(key);
    } else {
        pn->right = create_node(key);
    }

    bst->size++;

    return OK;
}

void
inorder_traverse(p_bst bst) {
    inorder(bst->root, 0);
}

void
inorder(p_node sub, ssize_t depth) {
    if (sub == NULL)
        return;
    inorder(sub->left, depth + 1);
    for (ssize_t i = 0; i < depth; i++)
        printf("   ");
    printf("%d\n", sub->key);
    inorder(sub->right, depth + 1);
}

void
preorder_traverse(p_bst bst) {
    preorder(bst->root, 0);
}

void
preorder(p_node sub, ssize_t depth) {
    if (sub == NULL)
        return;
    for (ssize_t i = 0; i < depth; i++)
        printf("   ");
    printf("%d\n", sub->key);
    preorder(sub->left, depth + 1);
    preorder(sub->right, depth + 1);
}

void
postorder_traverse(p_bst bst) {
    postorder(bst->root, 0);
}

void
postorder(p_node sub, ssize_t depth) {
    if (sub == NULL)
        return;
    postorder(sub->left, depth + 1);
    postorder(sub->right, depth + 1);
    for (ssize_t i = 0; i < depth; i++)
        printf("   ");
    printf("%d\n", sub->key);
}

Bool
isEmpty(p_bst bst) {
    if (bst->root == NULL)
        return TRUE;
    return FALSE;
}

ssize_t
size(p_bst bst) {
    return bst->size;
}

ElemType
min(p_bst bst) {
    p_node pn = bst->root;

    while (pn != NULL)
        if (pn->left == NULL)
            return pn->key;
        else
            pn = pn->left;
}

ElemType
max(p_bst bst) {
    p_node pn = bst->root;

    while (pn != NULL)
        if (pn->right == NULL)
            return pn->key;
        else
            pn = pn->right;
}

p_node
min_node(p_bst bst) {
    p_node pn = bst->root;

    while (pn != NULL)
        if (pn->left == NULL)
            break;
        else
            pn = pn->left;

    return pn;
}

p_node
min_subtree_node(p_node sub) {
    p_node pn = sub;

    while (pn != NULL)
        if (pn->left == NULL)
            break;
        else 
            pn = pn->left;
    return pn;
}

p_node
max_node(p_bst bst) {
    p_node pn = bst->root;

    while (pn != NULL)
        if (pn->right == NULL)
            break;
        else
            pn = pn->right;

    return pn;
}

p_node
max_subtree_node(p_node sub) {
    p_node pn = sub;

    while (pn != NULL)
        if (pn->right == NULL)
            break;
        else
            pn = pn->right;
    return pn;
}

p_node
find_node(p_bst bst, ElemType key) {
    p_node pn = bst->root;

    while (pn != NULL)
        if (key == pn->key)
            return pn;
        else if (pn->key > key)
            pn = pn->left;
        else
            pn = pn->right;
    return NULL;
}

p_node
find_subtree_node(p_node sub, ElemType key) {
    p_node pn = sub;

    while (pn != NULL)
        if (key == pn->key)
            return pn;
        else if (pn->key > key)
            pn = pn->left;
        else
            pn = pn->right;
    return NULL;
}

/*
 * Returning NULL when "key" is stored in root node.
 */
p_node
find_parent(p_bst bst, ElemType key) {
    p_node pn = bst->root;

    while (pn != NULL)
        if ((pn->left != NULL && pn->left->key == key) || 
            (pn->right != NULL && pn->right->key == key))
            return pn;
        else if (pn->key > key)
            pn = pn->left;
        else
            pn = pn->right;
    return NULL;
}

p_node
find_subtree_parent(p_node sub, ElemType key) {
    p_node pn = sub;

    while (pn != NULL)
        if ((pn->left != NULL && pn->left->key == key) || 
            (pn->right != NULL && pn->right->key == key))
            return pn;
        else if (pn->key > key)
            pn = pn->left;
        else
            pn = pn->right;
    return NULL;
}

Status
remove_key(p_bst bst, ElemType key) {
    p_node  parent, node, min, min_parent;

    node = find_node(bst, key);
    parent = find_parent(bst, key);

    if (node == NULL)
        return ERROR;

    if (parent != NULL) {
        if (node->left == NULL) {
            if (parent->left == node)
                parent->left = node->right;
            else
                parent->right = node->right;
        } else if (node->right == NULL) {
            if (parent->left == node)
                parent->left = node->left;
            else
                parent->right = node->left;
        } else {
            min = min_subtree_node(node->right);
            if (node->right == min) {
                if (parent->left == node) {
                    parent->left = min;
                    min->left = node->left;
                } else {
                    parent->right = min;
                    min->left = node->left;
                }
            } else {
                min_parent = find_subtree_parent(node->right, min->key);
                if (parent->left == node) {
                    parent->left = min;
                    min_parent->left = min->right;
                    min->right = node->right;
                    min->left = node->left;
                } else {
                    parent->right = min;
                    min_parent->left = min->right;
                    min->right = node->right;
                    min->left = node->left;
                }
            }
        }
    } else {
        if (node->left == NULL) {
            bst->root = node->right;
        } else if (node->right == NULL) {
            bst->root = node->left;
        } else {
            min = min_subtree_node(node->right);
            if (node->right == min) {
                bst->root = min;
                min->left = node->left;
            } else {
                min_parent = find_subtree_parent(node->right, min->key);
                bst->root = min;
                min_parent->left = min->right;
                min->right = node->right;
                min->left = node->left;
            }
        }
    }
    node->left = NULL;
    node->right = NULL;
    free(node);
    bst->size--;

    return OK;
}

#endif
