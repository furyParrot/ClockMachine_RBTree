#include "RBTree.h"
#include <stdlib.h>

Node * CreatRBTree(){
    Node * a = (Node*)malloc(sizeof(Node));
    a->keyvalue = 0;
    a->Red1Black0 = 0;
    a->cont = NULL;
    a->lson = NULL;
    a->rson = NULL;
    a->dad = NULL;
    return &a;
}
int AddNode(Node * root , Node* newnode){

}
int RemoveNode(Node * node){
    
}
Node * FindNode(int keyvalue){}
int SaveRBTree(char * filename , char* (*tostring)(Node* a)){}
Node* LoadRBTree(char * filename, Node* (*byScanf)(char* s)){}
Node** GetAllNodes(Node* root){}