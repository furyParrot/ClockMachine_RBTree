#include "ClockMachine.h"
#include "../RBTree/RBTree.h"
#include "../UsrTime/usr_time.h"

#include <stdio.h>
#include <stdlib.h>

char* NodeToString(Node* a){
    char *s = (char *)malloc(1001);
    sprintf(s,"key=%d id=%d name=%s age=%d gender=%c phonenum=%ld email=%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
    a->keyvalue,a->cont->baseInfo.id,a->cont->baseInfo.name,
    a->cont->baseInfo.age,a->cont->baseInfo.gender,a->cont->baseInfo.phonenum,a->cont->baseInfo.email,
    a->cont->clockInfo.mon_in,a->cont->clockInfo.mon_out,
    a->cont->clockInfo.tue_in,a->cont->clockInfo.tue_out,
    a->cont->clockInfo.wed_in,a->cont->clockInfo.wed_out,
    a->cont->clockInfo.thu_in,a->cont->clockInfo.thu_out,
    a->cont->clockInfo.fri_in,a->cont->clockInfo.fri_out,
    a->cont->pws.ID,a->cont->pws.WeekWorkSecond,
    a->cont->pws.LateTimes,a->cont->pws.EarlyLeave,
    a->cont->pws.AbandonTImes,a->cont->pws.ClkLakeTimes);
    return s;
}
Node* StringToNode(char* s){
    Node * a = (Node*)malloc(sizeof(Node));
    a->cont = (Content*)malloc(sizeof(Content));
    a->keyvalue = 0;
    a->Red1Black0 = 0;
    a->lson = NULL;
    a->rson = NULL;
    a->dad = NULL;

    sscanf(s,"key=%d id=%d name=%s age=%d gender=%c phonenum=%ld email=%s %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d",
    &a->keyvalue,&a->cont->baseInfo.id,a->cont->baseInfo.name,
    &a->cont->baseInfo.age,&a->cont->baseInfo.gender,&a->cont->baseInfo.phonenum,a->cont->baseInfo.email,
    &a->cont->clockInfo.mon_in,&a->cont->clockInfo.mon_out,
    &a->cont->clockInfo.tue_in,&a->cont->clockInfo.tue_out,
    &a->cont->clockInfo.wed_in,&a->cont->clockInfo.wed_out,
    &a->cont->clockInfo.thu_in,&a->cont->clockInfo.thu_out,
    &a->cont->clockInfo.fri_in,&a->cont->clockInfo.fri_out,
    &a->cont->pws.ID,&a->cont->pws.WeekWorkSecond,
    &a->cont->pws.LateTimes,&a->cont->pws.EarlyLeave,
    &a->cont->pws.AbandonTImes,&a->cont->pws.ClkLakeTimes);
    return a;
}

Node *root = NULL;
int AddEmployee(Stru_BaseInfo a){
    if(root==NULL){printf("please creat a new tab or load from file.\n");return 0;}
    Node * node = CreatRBTree();
    node->cont->baseInfo = a;
    node->keyvalue = a.id;
    node->cont->clockInfo.mon_in = 90000;
    node->cont->clockInfo.mon_out = 90000; 
    node->cont->clockInfo.tue_in = 90000;
    node->cont->clockInfo.tue_out = 90000;
    node->cont->clockInfo.wed_in = 90000;
    node->cont->clockInfo.wed_out = 90000;
    node->cont->clockInfo.thu_in = 90000;
    node->cont->clockInfo.thu_out = 90000;
    node->cont->clockInfo.fri_in = 90000;
    node->cont->clockInfo.fri_out = 90000;
    node->cont->pws.ID=0;
    node->cont->pws.WeekWorkSecond=0;
    node->cont->pws.LateTimes=0;
    node->cont->pws.EarlyLeave=0;
    node->cont->pws.AbandonTImes=0;
    node->cont->pws.ClkLakeTimes=0;
    AddNode(root,node);
}

int DelEmployee(int id){
    if(root==NULL){printf("please creat a new tab or load from file.\n");return 0;}
    Node * a = FindNode(root,id);
    if(a==NULL){printf("The ID:%d Don't Exist!\n",id); return 0;}
    RemoveNode(a);
}
int ClockIn(int id ){
    if(root==NULL){printf("please creat a new tab or load from file.\n");return 0;}
    Node * a = FindNode(root,id);
    if(a==NULL){printf("The ID:%d Don't Exist!\n",id); return 0;}
    char s[7];
    s[6] = '\0';
    sprintf(s,"%d",id);
    //123 456
    for(int i=1;i<=2;i++){
        char reg = s[i];
        s[i]=s[6-i];
        s[6-i]=reg;
    }
    int checkid;
    sscanf(s,"%d",&checkid);
    checkid+=id;
    printf("Your Check_num: %d\n",checkid);
    int inputcheckid;
    scanf("%d",inputcheckid);
    if(inputcheckid == checkid){
        int dayinweek = usr_time_GetDayInWeek();
        int * p = (int *)&(a->cont->clockInfo);
        p+=(dayinweek-1)*2;
        if(*p=90000){
            printf("Hello %s you are clocking in\n",a->cont->baseInfo.name);
        }else{
            p++;
            printf("Hello %s you are clocking out\n",a->cont->baseInfo.name);
        }
        *p = usr_time_GetSecInDay();
    }else{
        printf("your checkid is error, clock in fail!\n");
    }
}
int SaveFile(char* filename){
    if(root==NULL){printf("please creat a new tab or load from file.\n");return 0;}
    SaveRBTree(root,filename,NodeToString);
}
int LoadFile(char* filename){
    root = LoadRBTree(filename,StringToNode);
}
Stru_FullInfo** GetAllClockInfo(int * outputnum, int maxnum){
    if(root==NULL){printf("please creat a new tab or load from file.\n");return 0;}
    SomeNodes somenode = GetAllNodes(root,maxnum);
    Stru_FullInfo** res = (Stru_FullInfo**)malloc(sizeof(Stru_FullInfo*)*somenode.num);
    for(int i=0; i<somenode.num; i++){
        res[i] = somenode.datas[i]->cont;
    }
    *outputnum = somenode.num;
    return res;
}
void CreatANewTab(){
    root = CreatRBTree();
}