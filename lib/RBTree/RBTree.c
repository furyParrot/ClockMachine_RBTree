// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RBTree.h"

Node* GetMinNode(Node* node) {
    if (node->lson == NULL) {
        return node;
    }
    else {
        return GetMinNode(node->lson);
    }
}

Node* CreatRBTree() {
    Node* a = (Node*)malloc(sizeof(Node));
    a->keyvalue = 0;
    a->Red1Black0 = 0;
    a->cont = (Content*)malloc(sizeof(Content));
    a->lson = NULL;
    a->rson = NULL;
    a->dad = NULL;
    return a;
}

void ContCpy(Content* tar, Content* sor) {
    tar->baseInfo = sor->baseInfo;
    tar->clockInfo = sor->clockInfo;
}

int AddNode(Node* root, Node* newnode) {
    //是首个节点
    if (root->keyvalue == 0) {
        //将值赋值给根节点。
        root->keyvalue = newnode->keyvalue;
        ContCpy(root->cont, newnode->cont);
        //free(newnode);
    }
    //不是根节点
    else {
        if (newnode->keyvalue == root->keyvalue) {
            root->cont = newnode->cont;
        }
        else if (newnode->keyvalue > root->keyvalue) { //要往右边插

            if (root->rson != NULL) {//有右儿子的时候
                AddNode(root->rson, newnode);
            }
            else {//没右儿子的时候

                if (root->Red1Black0 == 0) { //爸是黑色，直接插入
                    root->rson = newnode;
                    newnode->dad = root;
                }
                else {  //爸是红色
                    int dadRight1Left0 = (root->dad->rson == NULL) ? 0 : ((root->keyvalue == root->dad->rson->keyvalue) ? 1 : 0);


                    if (((dadRight1Left0 == 1) && (root->dad->lson != NULL) && (root->dad->lson->Red1Black0 == 1)) ||
                        ((dadRight1Left0 == 0) && (root->dad->rson != NULL) && (root->dad->rson->Red1Black0 == 1))) {//叔叔是红色
                            //爸爸叔叔爷爷同时变色
                        root->Red1Black0 = 0;
                        if (dadRight1Left0 == 1) {
                            if (root->dad->lson != NULL)
                                root->dad->lson->Red1Black0 = 0;
                        }
                        else {
                            if (root->dad->rson != NULL)
                                root->dad->rson->Red1Black0 = 0;
                        }
                        root->dad->Red1Black0 = 1;
                        //将newnode插入
                        root->rson = newnode;
                        newnode->dad = root;
                        //爷爷变色，需要将爷爷插入祖父，如果没有祖父，就直接给爷爷变色
                        if (root->dad->dad == NULL) {
                            root->dad->Red1Black0 = 0;
                        }
                        else {
                            int ppRight1Left0 = (root->dad->dad->rson == NULL) ? 0 : ((root->dad->keyvalue == root->dad->dad->rson->keyvalue) ? 1 : 0);
                            if (ppRight1Left0 == 1) {
                                root->dad->dad->rson = NULL;
                                //root->dad->dad = NULL;
                            }
                            AddNode(root->dad->dad, root->dad);
                        }
                    }
                    else {//叔叔是黑色
                        if (dadRight1Left0 == 1) {//爸爸是爷爷的右儿子，和我同向：

                            Node* newpapa = CreatRBTree();
                            newpapa->keyvalue = root->dad->keyvalue;
                            ContCpy(newpapa->cont, root->dad->cont);

                            if (root->dad->lson != NULL) root->dad->lson->dad = newpapa;
                            newpapa->lson = root->dad->lson;

                            if (root->lson != NULL) root->lson->dad = newpapa;
                            newpapa->rson = root->lson;

                            root->dad->lson = newpapa;
                            newpapa->dad = root->dad;

                            root->dad->rson = newnode;
                            newnode->dad = root->dad;

                            root->dad->Red1Black0 = 0;
                            newpapa->Red1Black0 = 1;


                            root->dad->keyvalue = root->keyvalue;
                            ContCpy(root->dad->cont, root->cont);
                            //free(root);

                        }
                        else {//爸爸是爷爷的左儿子，和我反向：需要旋转操作
                            root->rson = newnode->lson;
                            if (newnode->lson != NULL) newnode->lson->dad = root;
                            newnode->lson = NULL;
                            root->dad->lson = newnode;
                            newnode->dad = root->dad;
                            root->dad = NULL;
                            AddNode(newnode, root);
                        }
                    }
                }
            }
        }
        else { //要往左边插
            if (root->lson != NULL) {//有左儿子的时候
                AddNode(root->lson, newnode);
            }
            else {//没左儿子的时候
                if (root->Red1Black0 == 0) { //爸是黑色，直接插入
                    root->lson = newnode;
                    newnode->dad = root;
                }
                else {  //爸是红色
                    int dadRight1Left0 = (root->dad->rson == NULL) ? 0 : ((root->keyvalue == root->dad->rson->keyvalue) ? 1 : 0);

                    if (((dadRight1Left0 == 1) && (root->dad->lson != NULL) && (root->dad->lson->Red1Black0 == 1)) ||
                        ((dadRight1Left0 == 0) && (root->dad->rson != NULL) && (root->dad->rson->Red1Black0 == 1))) { //叔叔是红色
                            //爸爸叔叔爷爷同时变色
                        root->Red1Black0 = 0;
                        if (dadRight1Left0 == 1) {
                            if (root->dad->lson != NULL)
                                root->dad->lson->Red1Black0 = 0;
                        }
                        else {
                            if (root->dad->rson != NULL)
                                root->dad->rson->Red1Black0 = 0;
                        }
                        root->dad->Red1Black0 = 1;
                        //将newnode插入
                        root->lson = newnode;
                        newnode->dad = root;
                        //爷爷变色，需要将爷爷插入祖父，如果没有祖父，就直接给爷爷变色
                        if (root->dad->dad == NULL) {
                            root->dad->Red1Black0 = 0;
                        }
                        else {
                            int ppRight1Left0 = (root->dad->dad->rson == NULL) ? 0 : ((root->dad->keyvalue == root->dad->dad->rson->keyvalue) ? 1 : 0);
                            if (ppRight1Left0 == 1) {
                                root->dad->dad->rson = NULL;
                                //root->dad->dad = NULL;
                            }
                            AddNode(root->dad->dad, root->dad);
                        }
                    }
                    else {//叔叔是黑色
                        if (dadRight1Left0 == 0) {//爸爸是爷爷的左儿子，和我同向：

                            Node* newpapa = CreatRBTree();
                            newpapa->keyvalue = root->dad->keyvalue;
                            ContCpy(newpapa->cont, root->dad->cont);
                            

                            if (root->dad->rson != NULL) root->dad->rson->dad = newpapa;
                            newpapa->rson = root->dad->rson;

                            if (root->rson != NULL) root->rson->dad = newpapa;
                            newpapa->lson = root->rson;

                            root->dad->rson = newpapa;
                            newpapa->dad = root->dad;

                            root->dad->lson = newnode;
                            newnode->dad = root->dad;

                            root->dad->Red1Black0 = 0;
                            newpapa->Red1Black0 = 1;

                            root->dad->keyvalue = root->keyvalue;
                            ContCpy(root->dad->cont , root->cont);
                            //free(root);
                        }
                        else {//爸爸是爷爷的右儿子，和我反向：需要旋转操作
                            root->lson = newnode->rson;
                            if (newnode->rson != NULL) newnode->rson->dad = root;
                            newnode->rson = NULL;
                            root->dad->rson = newnode;
                            newnode->dad = root->dad;
                            root->dad = NULL;
                            AddNode(newnode, root);
                        }
                    }
                }
            }
        }
    }
    return 1;
}

int RemoveNode(Node* node) {
    if(node==NULL){
        return 0;
    }
    //儿子的数量
    int sonNum = (node->lson == NULL ? 0 : 1) + (node->rson == NULL ? 0 : 1);
    //无子节点
    if (sonNum == 0) {
        if (node->Red1Black0 == 1) {//本节点为红色，直接删除
            int left1right0 = (node->dad->lson == NULL) ? 0 : ((node->dad->lson->keyvalue == node->keyvalue) ? 1 : 0);
            if (left1right0 == 1) {
                node->dad->lson = NULL;
            }
            else {
                node->dad->rson = NULL;
            }
            //不知道为什么出问题
            //free(node);
        }
        else {//本节点为黑色，情况复杂
            //进行DeleteBalance：
            DeleteBalance(node);
        }
    }
    else if (sonNum == 1) {//有一个子节点
        //看看子节点在哪边
        int left1right0 = (node->lson == NULL) ? 0 : 1;
        if (left1right0 == 1) {//左边子节点接替自己的地位。
            //让左边子节点的儿子们都指向自己，
            if(node->lson->lson!=NULL)node->lson->lson->dad = node;
            if(node->lson->rson!=NULL)node->lson->rson->dad = node;
            //将左节点的内容拿过来，
            node->keyvalue = node->lson->keyvalue;
            ContCpy(node->cont, node->lson->cont);
            //将自己的儿子指向左节点的儿子们
            node->rson = node->lson->rson;
            node->lson = node->lson->lson;
        }
        else {//右边子节点接替自己的地位。
            //让右边子节点的儿子们都指向自己，
            if(node->rson->lson!=NULL) node->rson->lson->dad = node;
            if(node->rson->rson!=NULL) node->rson->rson->dad = node;
            //将左右节点的内容拿过来，
            node->keyvalue = node->rson->keyvalue;
            ContCpy(node->cont, node->rson->cont);
            //将自己的儿子指向右节点的儿子们
            node->lson = node->rson->lson;
            node->rson = node->rson->rson;
        }
    }
    else {//有两个子节点，寻找右边的最大节点，用它替换本节点，并且将这个节点进行删除。
        Node* MinLagerNode = GetMinNode(node->rson);
        node->keyvalue = MinLagerNode->keyvalue;
        ContCpy(node->cont, MinLagerNode->cont);
        RemoveNode(MinLagerNode);
    }
    return 1;
}
//会在操作完成之后，移除一个黑色节点，或者降低一个黑色2节点的权值。
void DeleteBalance(Node* n){
    //先删除,
    Node* p = n->dad;
    Node* s = (n->dad==NULL)?NULL:((n->dad->rson->keyvalue==n->keyvalue)?n->dad->lson:n->dad->rson);
    int sL1R0 = (s==NULL)?3:( (n->dad->lson->keyvalue==s->keyvalue)?1:0);
    Node* sl = (s==NULL)?NULL:(s->lson);
    Node* sr = (s==NULL)?NULL:(s->rson);
    if(n->Red1Black0==2){
        n->Red1Black0 = 0;
    }else{
        if(n->dad == NULL){
            n->keyvalue =0;
            n->cont =NULL;
        }else{
            if(sL1R0==1){
                n->dad->rson =NULL;
            }else{
                n->dad->lson =NULL;
            }
            //不知道为什么
            //free(n);
        }
    }
    //然后开始判断是否需要平衡
    if(n->dad==NULL){//n为根节点，无需平衡
        return;
    }else{
        if(s->Red1Black0!=1){//兄黑
            if(((s->rson==NULL)|| (s->rson->Red1Black0!=1  ))&&((s->lson==NULL)||(s->lson->Red1Black0!=1))){//兄子节点全黑
                if(p->Red1Black0!=1){//父黑
                    s->Red1Black0=1;
                    p->Red1Black0=2;
                    DeleteBalance(p);
                }else{//父红
                    p->Red1Black0 =0;
                    s->Red1Black0 =1;
                    //交换ps颜色，平衡结束
                }
            }else{//兄子节点不全黑
                //拐的时候，先弄直
                if((sL1R0==1) && (sr!=NULL) && (sr->Red1Black0==1 )){
                    sr->dad = p;
                    p->lson = sr;

                    s->rson = sr->lson;
                    if(sr->lson!=NULL) sr->lson->dad = s;

                    s->dad = sr;
                    sr->lson =s;

                    s->Red1Black0=1;
                    sr->Red1Black0 =0;
                }else if((sL1R0==0)&&(sl!=NULL)&&(sl->Red1Black0==1)){
                    sl->dad =p;
                    p->rson = sl;

                    s->lson = sl->rson;
                    if(sl->rson!=NULL)sl->rson->dad =s;

                    s->dad = sl;
                    sl->rson = s;

                    s->Red1Black0 =1;
                    sl->Red1Black0 =0;
                }
                //直的时候，直接处理
                if(sL1R0 ==1){//s在左边
                    Node* newP = (Node*)malloc(sizeof(Node));
                    newP->cont = (Content*)malloc(sizeof(Content));
                    newP->keyvalue = p->keyvalue;
                    ContCpy(newP->cont,p->cont);
                    p->keyvalue = s->keyvalue;
                    ContCpy(p->cont,s->cont);

                    newP->lson = sr;
                    if(sr!=NULL)sr->dad = newP;

                    newP->rson = p->rson;
                    if(p->rson!=NULL)p->rson->dad = newP;

                    sl->dad = p;
                    p->lson = sl;

                    newP->dad = p;
                    p->rson = newP;
                    sl->Red1Black0 = 0;
                }else{
                    Node* newP = (Node*)malloc(sizeof(Node));
                    newP->cont = (Content*)malloc(sizeof(Content));
                    newP->keyvalue = p->keyvalue;
                    ContCpy(newP->cont,p->cont);
                    p->keyvalue = s->keyvalue;
                    ContCpy(p->cont,s->cont);

                    newP->rson = sl;
                    if(sl!=NULL)sl->dad = newP;

                    newP->lson = p->lson;
                    if(p->lson!=NULL)p->lson->dad = newP;

                    sr->dad = p;
                    p->rson = sr;

                    newP->dad = p;
                    p->lson = newP;
                    sr->Red1Black0 = 0;
                }
            }
        }
    }
}

Node* FindNode(Node* root,int keyvalue) {
    if(root==NULL){return NULL;}
    if((root->keyvalue )== keyvalue){
        return root;
    }else{
        if(keyvalue>(root->keyvalue)){
            return FindNode(root->rson,keyvalue);
        }else{
            return FindNode(root->lson,keyvalue);
        }
    }
}
int SaveRBTree(Node* root,char* filename, char* (*tostring)(Node* a)) {
    SomeNodes a = GetAllNodes(root, 1000);
    FILE * p = fopen(filename , "w");
    fprintf(p,"%d\n",a.num);
    for(int i=0; i < a.num ; i++){
        fprintf(p,"%s\n",tostring(a.datas[i]));
    }
    fclose(p);
    return a.num;
}
Node* LoadRBTree(char* filename, Node* (*byScanf)(char* s)) {
    Node* root = CreatRBTree();
    int num;
    FILE* p=fopen(filename,"r");
    fscanf(p,"%d",&num);
    char *one_line;
    one_line = (char*)malloc( 1000 * sizeof(char));
    for(int i=0;i<num+1;i++){
        fgets(one_line, 1000, p);
        AddNode(root,byScanf(one_line));
    }
    return root;
}

Node** datas;
int CurrentIndex = 0;
int maxnum;
SomeNodes GetAllNodes(Node* root, int MaxNum) {
    datas = (Node**)malloc(sizeof(Node*) * MaxNum);
    CurrentIndex = 0;
    maxnum = MaxNum;

    if (root->lson != NULL) {
        GetAllNodes2(root->lson, datas);
    }
    datas[CurrentIndex] = root;
    CurrentIndex++;
    if (root->rson != NULL) {
        GetAllNodes2(root->rson, datas);
    }
    SomeNodes res;
    res.datas = datas;
    res.num = CurrentIndex;
    return res;
}
void GetAllNodes2(Node* root, Node** datas) {
    if (CurrentIndex >= maxnum) {
        return;
    }
    if (root->lson != NULL) {
        GetAllNodes2(root->lson, datas);
    }
    datas[CurrentIndex] = root;
    CurrentIndex++;
    if (root->rson != NULL) {
        GetAllNodes2(root->rson, datas);
    }
    return;
}

void dumpNode(Node a) {

    printf("id:%d\t", a.keyvalue);
    printf("name:%s\t\n", a.cont->baseInfo.name);



}



int main() {
    printf("hello world\n");

    Stru_BaseInfo s1 = { 10,"101010",22,'m',17777777,"41819@qq.com" };
    Stru_ClockInfo *s1c = (Stru_ClockInfo*)malloc(sizeof(Stru_ClockInfo));
    Stru_FullInfo s1f = { s1, *s1c};
    Node a = { 10,1,&s1f,NULL,NULL,NULL };

    Stru_BaseInfo s2 = { 10,"888",22,'m',17777777,"41819@qq.com" };
    Stru_ClockInfo* s2c = (Stru_ClockInfo*)malloc(sizeof(Stru_ClockInfo));
    Stru_FullInfo s2f = { s2, *s2c };
    Node b = { 8,1,&s2f,NULL,NULL,NULL };

    Stru_BaseInfo s3 = { 10,"999",22,'m',17777777,"41819@qq.com" };
    Stru_ClockInfo* s3c = (Stru_ClockInfo*)malloc(sizeof(Stru_ClockInfo));
    Stru_FullInfo s3f = { s3, *s3c };
    Node c = { 9,1,&s3f,NULL,NULL,NULL };

    Stru_BaseInfo s4 = { 10,"111111",22,'m',17777777,"41819@qq.com" };
    Stru_ClockInfo* s4c = (Stru_ClockInfo*)malloc(sizeof(Stru_ClockInfo));
    Stru_FullInfo s4f = { s4, *s4c };
    Node d = { 11,1,&s4f,NULL,NULL,NULL };


    Stru_BaseInfo s5 = { 10,"121212",22,'m',17777777,"41819@qq.com" };
    Stru_ClockInfo* s5c = (Stru_ClockInfo*)malloc(sizeof(Stru_ClockInfo));
    Stru_FullInfo s5f = { s5, *s5c };
    Node e = { 12,1,&s5f,NULL,NULL,NULL };


    Stru_BaseInfo s6 = { 10,"1313113",22,'m',17777777,"41819@qq.com" };
    Stru_ClockInfo* s6c = (Stru_ClockInfo*)malloc(sizeof(Stru_ClockInfo));
    Stru_FullInfo s6f = { s6, *s6c };
    Node f = { 13,1,&s6f,NULL,NULL,NULL };

    Node* root = CreatRBTree();
    AddNode(root, &a);
    AddNode(root, &b);
    AddNode(root, &c);
    
    AddNode(root, &d);
    AddNode(root, &e);
    AddNode(root, &f);
    printf("before remove:\n");
    SomeNodes sn = GetAllNodes(root, 10);
    for (int i = 0; i < sn.num; i++) {
        dumpNode(*sn.datas[i]);
    }

    printf("after remove:\n");
    Node * nn = FindNode(root,10);
    RemoveNode(nn);

    sn = GetAllNodes(root, 10);
    for (int i = 0; i < sn.num; i++) {
        dumpNode(*sn.datas[i]);
    }
    printf("save file to datas.txt and read:\n");
    SaveRBTree(root,"data.txt",NodeToString);
    root = LoadRBTree("data.txt",StringToNode);
    
    sn = GetAllNodes(root, 10);
    for (int i = 0; i < sn.num; i++) {
        dumpNode(*sn.datas[i]);
    }
}
