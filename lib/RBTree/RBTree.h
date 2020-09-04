#pragma once
#include "../ClockMachine/ClockMachine.h"

Node* CreatRBTree();
int AddNode(Node* root, Node* newnode);
int RemoveNode(Node* node);
Node* FindNode(Node* root,int keyvalue);
int SaveRBTree(Node* root,char* filename, char* (*NodeToString)(Node* a));
Node* LoadRBTree(char* filename, Node* (*StringToNode)(char* s));
SomeNodes GetAllNodes(Node* root, int MaxNum);
void GetAllNodes2(Node* root, Node** datas);
void dumpNode(Node a);
void DeleteBalance(Node* a);