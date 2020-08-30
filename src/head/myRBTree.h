#ifndef __MY_RBTREE_H__
#define __MY_RBTREE_H__
#include "usr_sql3.h"

typedef Employee Content;


typedef struct Node
{
    struct Node * lson;
    struct Node * rson;
    struct Node * dad;
    Content * cont;
    int value;
    /* data */
} Node;

Node * CreatRBTree();
int AddNode(Node* newnode);
int RemoveNode(Node * node);
Node * FindNode(int value);

#endif
