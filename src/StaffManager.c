#include <stdio.h>
#include "../lib/mylib.h"
#include "StaffManager.h"
void ShowWeekSummay(void);
void ShowInfomations(void);
void start_staff_manager(void){
    int choose;
    int id;
    char s[200];
    int inputnum;
    while(1){
    printf("\
=====================\n\
||  staff_manager  || \n\
=====================\n\
Please choose function:\n\
1:Load File\n\
2:Creat a new tab\n\
3:Add employee\n\
4:Delete employee\n\
5:Clock in\n\
6:Show week summary\n\
7:Show informations\n\
8:Save as file\n\
9:Exit\n\
");
    scanf("%d",&choose);
    switch(choose){
        case 1:
            printf("Please input filename:\n");
            scanf("%s",s);
            LoadFile(s);
            break;
        case 2:
            CreatANewTab();
            printf("Creat succeed!\n");
            break;
        case 3:
            printf("please input infomation:(seperated by space)\nid name age gender(m/w) phonenum email\n");
            Stru_BaseInfo a;
            inputnum =scanf("%d %s %d %c %ld %s",&a.id,a.name,&a.age,&a.gender,&a.phonenum,a.email);
            printf("num = %d\n%d\n%s\n%d\n%c\n%ld\n%s",inputnum,a.id,a.name,a.age,a.gender,a.phonenum,a.email);
            if(inputnum==6){
                AddEmployee(a);
                printf("Add employee succeed!\n");
            }else{
                printf("your input is wrong\n");
                fflush(stdin);
            }
            break;
        case 4:
            printf("please input the ID you wanna delete:\n");
            scanf("%d",&id);
            DelEmployee(id);
            break;
        case 5:
            printf("please input your ID:\n");
            scanf("%d",&id);
            ClockIn(id);
            break;
        case 6:
            ShowWeekSummay();
            break;
        case 7:
            ShowInfomations();
            break;
        case 8:
            printf("Please input filename:\n");
            scanf("%s",s);
            SaveFile(s);
            break;
        case 9:
            return ;
        default:
            break;
    }
    }
}
void dump(Stru_FullInfo * a){
    printf("%d %s %d %c %ld %s\n",a->baseInfo.id,a->baseInfo.name,a->baseInfo.age,a->baseInfo.gender,a->baseInfo.phonenum,a->baseInfo.email);
}

void ShowWeekSummay(void){
    //工号，工作时长，迟到次数，早退次数，旷工次数，缺卡次数
    int num;
    Stru_FullInfo** a = GetAllClockInfo(&num,1000);
    printf("ID\tName\t");
}
void ShowInfomations(void){
    int num;
    Stru_FullInfo** a = GetAllClockInfo(&num,1000);
    for(int i=0 ; i<num ; i++){
        dump(a[i]);
    }
}