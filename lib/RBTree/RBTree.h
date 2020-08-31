#pragma once
#include "../ClockMachine/ClockMachine.h"
typedef struct SomeNodes{
    Node** datas;
    int num;
} SomeNodes;
Node * CreatRBTree();
int AddNode(Node * root, Node* newnode);
int RemoveNode(Node * node);
Node * FindNode(int keyvalue);
int SaveRBTree(char * filename , char* (*tostring)(Node* a));
Node* LoadRBTree(char * filename, Node* (*byScanf)(char* s));
SomeNodes GetAllNodes(Node* root ,int MaxNum);
void GetAllNodes2(Node* root , Node ** datas);
