#include <stdio.h>
#include "../lib/ClockMachine/ClockMachine.h"
#include "StaffManager.h"

#define WORK_START_TIME 32400
#define WORK_END_TIME 61200


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
    for(int i=0 ; i<num ; i++){
        a[i]->pws.ID = a[i]->baseInfo.id;
        a[i]->pws.WeekWorkSecond = ((a[i]->clockInfo.mon_out == 90000 || a[i]->clockInfo.mon_in==90000)?0:(a[i]->clockInfo.mon_out-a[i]->clockInfo.mon_in))+
        ((a[i]->clockInfo.tue_out == 90000 || a[i]->clockInfo.tue_in==90000)?0:(a[i]->clockInfo.tue_out-a[i]->clockInfo.tue_in))+
        ((a[i]->clockInfo.wed_out == 90000 || a[i]->clockInfo.wed_in==90000)?0:(a[i]->clockInfo.wed_out-a[i]->clockInfo.wed_in))+
        ((a[i]->clockInfo.thu_out == 90000 || a[i]->clockInfo.thu_in==90000)?0:(a[i]->clockInfo.thu_out-a[i]->clockInfo.thu_in))+
        ((a[i]->clockInfo.fri_out == 90000 || a[i]->clockInfo.fri_in==90000)?0:(a[i]->clockInfo.fri_out-a[i]->clockInfo.fri_in));
        a[i]->pws.LateTimes = ((a[i]->clockInfo.mon_in>WORK_START_TIME)?1:0) +
        ((a[i]->clockInfo.tue_in>WORK_START_TIME)?1:0) +
        ((a[i]->clockInfo.wed_in>WORK_START_TIME)?1:0) +
        ((a[i]->clockInfo.thu_in>WORK_START_TIME)?1:0) +
        ((a[i]->clockInfo.fri_in>WORK_START_TIME)?1:0);

        a[i]->pws.EarlyLeave = ((a[i]->clockInfo.mon_out==90000)?1:(a[i]->clockInfo.mon_out<WORK_END_TIME))+
        ((a[i]->clockInfo.tue_out==90000)?1:(a[i]->clockInfo.tue_out<WORK_END_TIME))+
        ((a[i]->clockInfo.wed_out==90000)?1:(a[i]->clockInfo.wed_out<WORK_END_TIME))+
        ((a[i]->clockInfo.thu_out==90000)?1:(a[i]->clockInfo.thu_out<WORK_END_TIME))+
        ((a[i]->clockInfo.fri_out==90000)?1:(a[i]->clockInfo.fri_out<WORK_END_TIME));

        a[i]->pws.AbandonTImes = ((a[i]->clockInfo.mon_in==90000 && a[i]->clockInfo.mon_out==90000)?1:0)+
        ((a[i]->clockInfo.tue_in==90000 && a[i]->clockInfo.tue_out==90000)?1:0)+
        ((a[i]->clockInfo.wed_in==90000 && a[i]->clockInfo.wed_out==90000)?1:0)+
        ((a[i]->clockInfo.thu_in==90000 && a[i]->clockInfo.thu_out==90000)?1:0)+
        ((a[i]->clockInfo.fri_in==90000 && a[i]->clockInfo.fri_out==90000)?1:0);

        a[i]->pws.ClkLakeTimes =0;
        int *p = (int *)&a[i]->pws;
        for(int i=0;i<10;i++){
            if(p[i]==90000){a[i]->pws.ClkLakeTimes++;}
        }
    }
    //
    printf("ID\tWork time\tLate time\tEarly leave time\tAbandon times\tClkLakeTimes\n");
    for(int i=0 ; i<num ; i++){
        printf("%d\t%dh%dmin\t\t%d\t\t%d\t\t\t%d\t\t%d\n",a[i]->pws.ID,a[i]->pws.WeekWorkSecond/3600,a[i]->pws.WeekWorkSecond%3600/60,
        a[i]->pws.LateTimes,a[i]->pws.EarlyLeave ,a[i]->pws.AbandonTImes,a[i]->pws.ClkLakeTimes);
    }
}
void ShowInfomations(void){
    int num;
    Stru_FullInfo** a = GetAllClockInfo(&num,1000);
    for(int i=0 ; i<num ; i++){
        dump(a[i]);
    }
}