// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "RBTree.h"
#include "myfunction.h"

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
    //儿子的数量
    int sonNum = (node->lson == NULL ? 0 : 1) + (node->rson == NULL ? 0 : 1);
    //无子节点
    if (sonNum == 0) {
        if (node->Red1Black0 == 1) {//本节点为红色，直接删除
            int left1right0 = (node->dad->lson == NULL) ? 0 : ((node->dad->lson->keyvalue == node->keyvalue) ? 1 : 0);
            if (node->Red1Black0 == 1) {
                if (left1right0 == 1) {
                    node->dad->lson = NULL;
                }
                else {
                    node->dad->rson = NULL;
                }
                free(node);
            }
        }
        else {//本节点为黑色，情况复杂
            //进行DeleteBalance：
            DeleteBalance(node->dad);
        }
    }
    else if (sonNum == 1) {//有一个子节点
        //看看子节点在哪边
        int left1right0 = (node->lson == NULL) ? 0 : 1;
        if (left1right0 == 1) {//左边子节点接替自己的地位。
            //让左边子节点的儿子们都指向自己，
            node->lson->lson->dad = node;
            node->lson->rson->dad = node;
            //将左节点的内容拿过来，
            node->keyvalue = node->lson->keyvalue;
            ContCpy(node->cont, node->lson->cont);
            //将自己的儿子指向左节点的儿子们
            node->rson = node->lson->rson;
            node->lson = node->lson->lson;
        }
        else {//右边子节点接替自己的地位。
            //让右边子节点的儿子们都指向自己，
            node->rson->lson->dad = node;
            node->rson->rson->dad = node;
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
    return 0;
}
//会在操作完成之后，移除一个黑色节点，或者降低一个黑色2节点的权值。
void DeleteBalance(Node* a){

}

Node* FindNode(int keyvalue) {
    return (Node*)malloc(sizeof(Node));
}
int SaveRBTree(char* filename, char* (*tostring)(Node* a)) {
    return 0;
}
Node* LoadRBTree(char* filename, Node* (*byScanf)(char* s)) {
    return (Node*)malloc(sizeof(Node));
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
    hello();

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
    


    SomeNodes sn = GetAllNodes(root, 10);
    for (int i = 0; i < sn.num; i++) {
        dumpNode(*sn.datas[i]);
    }
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
