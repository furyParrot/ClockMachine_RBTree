#pragma once
#include "../ClockMachine/ClockMachine.h"

Node * CreatRBTree();
int AddNode(Node* newnode);
int RemoveNode(Node * node);
Node * FindNode(int value);
int SaveRBTree(char * filename , char* (*tostring)(Node* a));
Node* LoadRBTree(char * filename, Node* (*byScanf)(char* s));
Node** GetAllNodes(Node* root);