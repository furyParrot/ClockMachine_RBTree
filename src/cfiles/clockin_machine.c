#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "sqlite3.h"

#include "../head/clockin_machine.h"
#include "../head/usr_time.h"
#include "../head/usr_sql3.h"

sqlite3 *db = 0;
pthread_t thTrueClkInMachine, thDeadLineShutDown;
int minWorkHour =9;

//进行一些打卡机的初始化工作，并控制打卡机的开启停止
void clockin_machine_start(){
    int res;
    char *s;
    printf("clockin_machine is started!\n");
    sql_OpenDB("../data/clk_machine.sqlite");
    #ifdef __TEST__
    //新建一个test空表格，列为：员工编号，姓名，周1-5上下班打卡时间
    sql_OpenOrCreatTab("test");
    #else
    //查询当前的周，如果是数据库里没有的，就新建一个表格，以该周的周一的日子命名，如果有，就打开这个表
    struct tm* tms;
    time_t tt;
    time(&tt);
    tms = localtime(&tt);
    int year = tms->tm_year;
    int FirstDayOfThisWeek_InYear = (tms->tm_wday<6)?((tms->tm_yday)-(tms->tm_wday-1)):((tms->tm_yday)+8-(tms->tm_wday));
    char finalTabName[20]="                    ";
    sprintf(finalTabName,"tab_%d%d",year,FirstDayOfThisWeek_InYear);
    sql_OpenOrCreatTab(finalTabName);
    printf("当前表格为：%s\n",finalTabName);

    #endif

    //打开真正的打卡机线程
    res = pthread_create(&thTrueClkInMachine, NULL, (void *)TrueClkInMachine, NULL);
    res = pthread_create(&thDeadLineShutDown, NULL, (void *)DeadLineShutDown, NULL);

    //线程结束以后，打印该周总结
    pthread_join(thTrueClkInMachine, NULL);
    //如果计时器没有结束（用户主动推出），就杀掉计时器。
    pthread_kill(thDeadLineShutDown,SIGKILL);
    //展示一周总结
    ShowWeekSummary();
}

//直接计算出离最终结束剩余的时间，直接延时到终结，然后shut down掉打卡机线程，结束。
void DeadLineShutDown(void){
    int restTimeSec = usr_time_Init();
    sleep(restTimeSec);
    pthread_kill(thTrueClkInMachine,SIGKILL);
}
//打卡机，根据命令 进行功能选择。
void TrueClkInMachine(void){
    system("clear");
    while(1){
        printf("\n\
        **************************\n\
        **        打卡机        **\n\
        **************************\n\
        1:上班打卡\n\
        2:下班打卡\n\
        3:添加员工\n\
        4:删除员工\n\
        5:设置每日上班时长\n\
        6:查看周报\n\
        7:结束\n\
        8:浏览表格\n\
        ");
        int chooseindex;
        int res = scanf("%d",&chooseindex);
        if(res ==1){//输入成功
            switch (chooseindex)
            {
            case 1:
                ClockIn_local(1);
                break;
            case 2:
                ClockIn_local(2);
                break;
            case 3:
                AddEmployee();
                break;
            case 4:
                DelEmployee();
                break;
            case 5:
                SetWorkTimePerDay();
                break;
            case 6:
                ShowWeekSummary();
                break;
            case 7:
                return;
            case 8:
                sql_showAll();
                break;
            default:
                break;
            }
        }
    }
}
void ClockIn_local(int in1_out2){
    system("clear");
    int id;
    printf("输入工号：____________\b\b\b\b\b\b\b\b\b\b\b\b");

    //输入六位数字工号 
    int res;
    do{
        printf("请输入六位数字!\n");
        fflush(stdin);
        res = scanf("%d",&id);
    }while(res!=1 || id<100000 || id>999999);
    //检查数据库中是否有这个工号
    if(!sql_IsIdExit(id)){
        printf("这个ID不存在！\n");
        return;
    }
    //计算出校验码，（id除首位反序，并求和）
    char antiid[7];
    sprintf(antiid,"%d",id);
    char reg;
    for(int i =1;i<3;i++){
        reg = antiid[i];
        antiid[i]=antiid[6-i];
        antiid[6-i] = reg;
    }
    int antiid_num;
    sscanf(antiid,"%d",&antiid_num);
    antiid_num+=id;
    printf("%d\n请输入校验码：______\b\b\b\b\b\b",antiid_num);
    int input;
    scanf("%d",&input);
    if(input==antiid_num){
        sql_clock(id,usr_time_GetDayInWeek(),usr_time_GetSecInDay(),in1_out2,minWorkHour);
        printf("%d打卡成功！\n",id);
    }else{
        printf("校验码输入错误！打卡失败！\n");
    }
}

void AddEmployee(){
    system("clear");
    int id;
    printf("输入工号：____________\b\b\b\b\b\b\b\b\b\b\b\b");

    //输入六位数字工号 
    int res;
    do{
        printf("请输入六位数字!\n");
        fflush(stdin);
        res = scanf("%d",&id);
    }while(res!=1 || id<100000 || id>999999);
    //检查数据库中是否有这个工号
    if(sql_IsIdExit(id)){
        printf("这个ID已经存在！\n");
        return;
    }
    char name[20];
    printf("请输入姓名:________\b\b\b\b\b\b\b\b");
    scanf("%s",name);
    sql_NewLine(id,name);
}
void DelEmployee(){
    
    system("clear");
    int id;
    printf("输入工号：____________\b\b\b\b\b\b\b\b\b\b\b\b");

    //输入六位数字工号 
    int res;
    do{
        printf("请输入六位数字!\n");
        fflush(stdin);
        res = scanf("%d",&id);
    }while(res!=1 || id<100000 || id>999999);
    //检查数据库中是否有这个工号
    if(!sql_IsIdExit(id)){
        printf("这个ID不存在！\n");
        return;
    }
    sql_DelLine(id);
}
void SetWorkTimePerDay(){
    printf("请设置每日最短工作时间：____小时。\b\b\b\b\b\b");
    scanf("%d",&minWorkHour);
}
void ShowWeekSummary(){
    sql_showWeekReport(minWorkHour);
}