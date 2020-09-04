#include "ClockMachine.h"
#include "../RBTree/RBTree.h"
#include <stdio.h>
#include <stdlib.h>

char* NodeToString(Node* a){
    char *s = (char *)malloc(1001);
    sprintf(s,"key=%d id=%d name=%s age=%d gender=%c phonenum=%ld email=%s %d %d %d %d %d %d %d %d %d %d",
    a->keyvalue,a->cont->baseInfo.id,a->cont->baseInfo.name,
    a->cont->baseInfo.age,a->cont->baseInfo.gender,a->cont->baseInfo.phonenum,a->cont->baseInfo.email,
    a->cont->clockInfo.mon_in,a->cont->clockInfo.mon_out,
    a->cont->clockInfo.tue_in,a->cont->clockInfo.tue_out,
    a->cont->clockInfo.wed_in,a->cont->clockInfo.wed_out,
    a->cont->clockInfo.thu_in,a->cont->clockInfo.thu_out,
    a->cont->clockInfo.fri_in,a->cont->clockInfo.fri_out);
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

    sscanf(s,"key=%d id=%d name=%s age=%d gender=%c phonenum=%ld email=%s %d %d %d %d %d %d %d %d %d %d",
    &a->keyvalue,&a->cont->baseInfo.id,a->cont->baseInfo.name,
    &a->cont->baseInfo.age,&a->cont->baseInfo.gender,&a->cont->baseInfo.phonenum,a->cont->baseInfo.email,
    &a->cont->clockInfo.mon_in,&a->cont->clockInfo.mon_out,
    &a->cont->clockInfo.tue_in,&a->cont->clockInfo.tue_out,
    &a->cont->clockInfo.wed_in,&a->cont->clockInfo.wed_out,
    &a->cont->clockInfo.thu_in,&a->cont->clockInfo.thu_out,
    &a->cont->clockInfo.fri_in,&a->cont->clockInfo.fri_out);
    return a;
}
int AddEmployee(Stru_BaseInfo a){
    
}

int DelEmployee(int id){

}
int ClockIn(int id ){

}
int SaveFile(TableOfOneWeek* a){

}
int LoadFile(char* filename){

}
Stru_FullInfo** GetAllClockInfo(Node* root){

}