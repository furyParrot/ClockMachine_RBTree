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
    //是首个节点
    if(root->keyvalue==0){
        //将值赋值给根节点。
        root->keyvalue = newnode->keyvalue;
        root->cont = newnode->cont;
        free(newnode);
    }
    //不是根节点
    else{
        if(newnode->keyvalue == root->keyvalue){
            root->cont = newnode->cont;
        }else if(newnode->keyvalue > root->keyvalue){ //要往右边插

            if(root->rson != NULL){//有右儿子的时候
                AddNode(root->rson , newnode);
            }else{//没右儿子的时候
                
                if(root->Red1Black0 == 0){ //爸是黑色，直接插入
                    root->rson = newnode;
                    newnode->dad = root;
                }else{  //爸是红色
                    int dadRight1Left0 = (root->dad->rson==NULL)?0:((root->keyvalue == root->dad->rson->keyvalue)?1:0);


                    if(((dadRight1Left0==1) && (root->dad->lson!=NULL) && (root->dad->lson->Red1Black0==1 ))||
                    ((dadRight1Left0==0 )&& (root->dad->rson != NULL) && (root->dad->rson->Red1Black0==1))){//叔叔是红色
                        //爸爸叔叔爷爷同时变色
                        root->Red1Black0 = 0;
                        if(dadRight1Left0==1){
                            root->dad->lson->Red1Black0 = 0;
                        }else{
                            root->dad->rson->Red1Black0 = 0;
                        }
                        root->dad->Red1Black0 = 1;
                        //将newnode插入
                        root->rson = newnode;
                        newnode->dad = root;
                        //爷爷变色，需要将爷爷插入祖父，如果没有祖父，就直接给爷爷变色
                        if(root->dad->dad==NULL){
                            root->dad->Red1Black0 = 0;
                        }else{
                            AddNode(root->dad->dad,root->dad);
                        }
                    }else{//叔叔是黑色
                        if(dadRight1Left0==1){//爸爸是爷爷的右儿子，和我同向：
                            //          root 顶替掉 root->dad,并且变黑
                            //创建一个新节点，cont 、 keyvalue、lson和root dad一样，颜色红，rson是root的lson
                            Node * grandpa = (Node *)malloc(sizeof(Node));
                            grandpa->cont = root->dad->cont;
                            grandpa->keyvalue = root->dad->keyvalue;
                            grandpa->lson = root->dad->lson;
                            if(root->dad->lson!=NULL) root->dad->lson->dad =grandpa; 
                            grandpa->Red1Black0 = 1;

                            grandpa->rson = root->lson;
                            if(root->lson!=NULL) root->lson->dad = grandpa;

                            grandpa->dad = root->dad;

                            root->dad->cont = root->cont;
                            root->dad->keyvalue = root->keyvalue;
                            root->dad->Red1Black0 = 0;
                            root->dad->lson = grandpa;
                            if(root->lson!=NULL)root->lson->dad = root->dad;
                            root->dad->rson = newnode;
                            newnode->dad = root->dad;
                            free(root);

                        }else{//爸爸是爷爷的左儿子，和我反向：需要旋转操作
                            root->rson = newnode->lson;
                            if(newnode->lson!=NULL) newnode->lson->dad = root;
                            newnode->lson = root;
                            root->dad->lson = newnode;
                            newnode->dad = root->dad;
                            root->dad = newnode;
                            AddNode(newnode,root);
                        }
                    }
                }
            }
        }else{ //要往左边插
            if(root->lson != NULL){//有左儿子的时候
                AddNode(root->lson , newnode);
            }else{//没左儿子的时候
                if(root->Red1Black0 == 0){ //爸是黑色，直接插入
                    root->lson = newnode;
                    newnode->dad = root;
                }else{  //爸是红色
                    int dadRight1Left0 = (root->dad->rson==NULL)?0:((root->keyvalue == root->dad->rson->keyvalue)?1:0);

                    if(((dadRight1Left0==1) && (root->dad->lson!=NULL) && (root->dad->lson->Red1Black0==1 ))||
                    ((dadRight1Left0==0 )&& (root->dad->rson != NULL) && (root->dad->rson->Red1Black0==1))){ //叔叔是红色
                        //爸爸叔叔爷爷同时变色
                        root->Red1Black0 = 0;
                        if(dadRight1Left0==1){
                            root->dad->lson->Red1Black0 = 0;
                        }else{
                            root->dad->rson->Red1Black0 = 0;
                        }
                        root->dad->Red1Black0 = 1;
                        //将newnode插入
                        root->lson = newnode;
                        newnode->dad = root;
                        //爷爷变色，需要将爷爷插入祖父，如果没有祖父，就直接给爷爷变色
                        if(root->dad->dad==NULL){
                            root->dad->Red1Black0 = 0;
                        }else{
                            AddNode(root->dad->dad,root->dad);
                        }
                    }else{//叔叔是黑色
                        if(dadRight1Left0==0){//爸爸是爷爷的左儿子，和我同向：
                            //          root 顶替掉 root->dad,并且变黑
                            //创建一个新节点，cont 、 keyvalue、lson和root dad一样，颜色红，rson是root的lson
                            
                            Node * grandpa = (Node *)malloc(sizeof(Node));
                            grandpa->cont = root->dad->cont;
                            grandpa->keyvalue = root->dad->keyvalue;
                            grandpa->rson = root->dad->rson;
                            if(root->dad->rson!=NULL) root->dad->rson->dad =grandpa; 
                            grandpa->Red1Black0 = 1;

                            grandpa->lson = root->rson;
                            if(root->rson!=NULL) root->rson->dad = grandpa;

                            grandpa->dad = root->dad;

                            root->dad->cont = root->cont;
                            root->dad->keyvalue = root->keyvalue;
                            root->dad->Red1Black0 = 0;
                            root->dad->rson = grandpa;
                            if(root->rson!=NULL)root->rson->dad = root->dad;
                            root->dad->lson = newnode;
                            newnode->dad = root->dad;
                            free(root);

                        }else{//爸爸是爷爷的右儿子，和我反向：需要旋转操作
                            root->lson = newnode->rson;
                            if(newnode->rson!=NULL) newnode->rson->dad = root;
                            newnode->rson = root;
                            root->dad->rson = newnode;
                            newnode->dad = root->dad;
                            root->dad = newnode;
                            AddNode(newnode,root);
                        }
                    }
                }
            }
        }
    }
}
int RemoveNode(Node * node){

}
Node * FindNode(int keyvalue){}
int SaveRBTree(char * filename , char* (*tostring)(Node* a)){}
Node* LoadRBTree(char * filename, Node* (*byScanf)(char* s)){}

Node** datas;
int CurrentIndex =0;
Node** GetAllNodes(Node* root ,int MaxNum){
    datas = malloc(sizeof(Node*)*MaxNum);
    CurrentIndex =0;
    if(root->lson!=NULL){
        GetAllNodes2(root->lson,datas);
    }
    datas[CurrentIndex] = root;
    CurrentIndex++;
    if(root->rson!=NULL){
        GetAllNodes2(root->rson,datas);
    }
    return datas;
}
void GetAllNodes2(Node* root , Node ** datas){
    if(root->lson!=NULL){
        GetAllNodes2(root->lson,datas);
    }
    datas[CurrentIndex] = root;
    CurrentIndex++;
    if(root->rson!=NULL){
        GetAllNodes2(root->rson,datas);
    }
    return;
}


void NodeCpy(Node* source , Node* target){
    target->keyvalue = source->keyvalue;
    target->cont = source->cont;
    target->rson = source->rson;
    target->lson = source->lson;
    target->Red1Black0 = source->Red1Black0;
}