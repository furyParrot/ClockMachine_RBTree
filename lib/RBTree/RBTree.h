#pragma once
#include "../ClockMachine/ClockMachine.h"

Node * CreatRBTree();
int AddNode(Node * root, Node* newnode);
int RemoveNode(Node * node);
Node * FindNode(int keyvalue);
int SaveRBTree(char * filename , char* (*tostring)(Node* a));
Node* LoadRBTree(char * filename, Node* (*byScanf)(char* s));
Node** GetAllNodes(Node* root ,int MaxNum);

void NodeCpy(Node* source , Node* target);