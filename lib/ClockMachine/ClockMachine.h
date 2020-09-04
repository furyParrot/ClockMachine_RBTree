#pragma once
//记录着每个人的基础信息
typedef struct Stru_BaseInfo{
    int id;
    char name[20];
    int age;
    char gender;
    long phonenum;
    char email[100];
}Stru_BaseInfo;

//记录着每天打卡时刻的秒数
typedef struct Stru_ClockInfo{
    int mon_in,mon_out,tue_in,tue_out,wed_in,wed_out,thu_in,thu_out,fri_in,fri_out;

}Stru_ClockInfo;

typedef struct PersonWeekSummary{

}PersonWeekSummary;

//记录着一个人的完整信息，包含个人信息和一周打卡信息
typedef struct Stru_FullInfo{
    Stru_BaseInfo baseInfo;
    Stru_ClockInfo clockInfo;nkjfwqe
}Stru_FullInfo;

typedef Stru_FullInfo Content;

typedef struct Node
{
    int keyvalue;
    int Red1Black0;
    Content * cont;
    struct Node * lson;
    struct Node * rson;
    struct Node * dad;
} Node;

typedef struct SomeNodes {
    Node** datas;
    int num;
} SomeNodes;

//记录了一周的表格，包含了若干人，以及年日。
void CreatANewTab();
int AddEmployee(Stru_BaseInfo a);
int DelEmployee(int id);
int ClockIn(int id );
int SaveFile(char* filename);
int LoadFile(char* filename);
Stru_FullInfo** GetAllClockInfo(int * outputnum, int maxnum);

char* NodeToString(Node* a);
Node* StringToNode(char* s);