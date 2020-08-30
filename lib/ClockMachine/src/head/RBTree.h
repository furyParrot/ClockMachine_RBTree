#pragma once
#include "ClockMachine.h"

typedef Stru_FullInfo Content;

typedef struct Node
{
    struct Node * lson;
    struct Node * rson;
    struct Node * dad;
    Content * cont;
    int keyvalue;
} Node;

Node * CreatRBTree();
int AddNode(Node* newnode);
int RemoveNode(Node * node);
Node * FindNode(int value);
int SaveRBTree(char * filename, );