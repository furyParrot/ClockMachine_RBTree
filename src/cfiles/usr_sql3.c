#include <sqlite3.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../head/usr_sql3.h"

#ifdef __USE_SQLITE__
static sqlite3 * db;
static char* tabname_using;
static char *errorMsg;
void sql_OpenDB(const char* address){
    sqlite3_open(address,&db);
}
void sql_CloseDB(void){
    int res = sqlite3_close(db);
}
int sql_IsIdExit(int id){
    char* final = (char*)malloc(200);
    sprintf(final,"select * from %s",tabname_using);
    int nrow,ncolumn;
    char ** db_result;
    int res = sqlite3_get_table(db,final,&db_result,&nrow,&ncolumn,&errorMsg);
    int id_sele=0;
    for(int i=0;i<(nrow+1)*ncolumn;i+=ncolumn)
    {
        sscanf(db_result[i],"%d",&id_sele);
        if(id_sele==id){
            return i;
        }
    }
    return 0;
}
void sql_OpenOrCreatTab(const char* tabname){
    char* s1 = "create table if not exists ";
    char* s3 = "(id int(6),name char(20),mon_in int(20),mon_out int(20),tue_in int(20),tue_out int(20),wed_in int(20),wed_out int(20),thu_in int(20),thu_out int(20),fri_in int(20),fri_out int(20))";
    char* final = (char*)malloc(strlen(tabname)+strlen(s1)+strlen(s3));
    sprintf(final,"%s%s%s",s1,tabname,s3);
    sqlite3_exec(db,final,0,0,&errorMsg);
    tabname_using = (char* )tabname;
}
void sql_NewLine(int id,char* name){
    char final[200];
    sprintf(final,"insert into %s values(%d,'%s',90000,90000,90000,90000,90000,90000,90000,90000,90000,90000)",tabname_using,id,name);
    sqlite3_exec(db,final,0,0,&errorMsg);
}
void sql_DelLine(int id){
    char final[200];
    sprintf(final,"delete from %s where id=%d",tabname_using,id);
    sqlite3_exec(db,final,0,0,&errorMsg);
}
void sql_clock(int id,int dayInWeek,int secondInADay, int in1_out2 ,int min_workHour){
    char week[5];
    switch (dayInWeek)
    {
    case 1: strcpy(week, "mon_"); break;
    case 2: strcpy(week, "tue_"); break;
    case 3: strcpy(week, "wed_"); break;
    case 4: strcpy(week, "thu_"); break;
    case 5: strcpy(week, "fri_"); break;
    default:return;
    }
    char final[200];
    if(in1_out2==1){
        sprintf(final,"update %s set %s%s=%d where id=%d",tabname_using,week,"in",secondInADay,id);
        sqlite3_exec(db,final,0,0,&errorMsg);
        return;
    }
    sprintf(final,"update %s set %s%s=%d where id=%d",tabname_using,week,"out",secondInADay,id);
    //查询今天的上班打卡时间，并计算时常

    char select_query[100];
    sprintf(select_query,"select * from %s",tabname_using);
    int nrow,ncolumn;
    char ** db_result;
    sqlite3_get_table(db,select_query,&db_result,&nrow,&ncolumn,&errorMsg);
    int clkin_timep;
    sscanf(db_result[2*dayInWeek+sql_IsIdExit(id)],"%d",&clkin_timep);
    if (clkin_timep==90000){
        printf("您今日没有上班打卡！\n");
        return;
    }
    sqlite3_exec(db,final,0,0,&errorMsg);
    printf("%d:下班打卡成功\n",id);
    int hour_ = (secondInADay - clkin_timep)/3600;
    int min = ((secondInADay - clkin_timep)%3600) / 60;
    printf("您今天的工作时长是：%d小时%d分\n",hour_,min);
    if (hour_>=min_workHour)
        return;
    else
        printf("您的工作时常不足，还差%d分钟\n",(min_workHour*3600-(secondInADay-clkin_timep))/60);
}
void sql_showAll(void){
    char select_query[100];
    sprintf(select_query,"select * from %s",tabname_using);
    int nrow,ncolumn;
    char ** db_result;
    sqlite3_get_table(db,select_query,&db_result,&nrow,&ncolumn,&errorMsg);
    int i,j;
    int sec;
    for(i=0;i<(nrow+1)*ncolumn;i+=ncolumn)
    {
        for(j=0;j<ncolumn;j++)
        {
            if(j>1&&i>0){
                sscanf(db_result[i+j],"%d",&sec);
                if(sec>86400){
                    printf("无\t");
                }else{
                    printf("%d:%d\t",sec/3600,(sec%3600)/60);
                }
            }else{
                printf("%s\t",db_result[i+j]);
            }
        }
        printf("\n");
    }
}
void sql_showWeekReport(int min_WorkHour){
    
    char select_query[100];
    sprintf(select_query,"select * from %s",tabname_using);
    int nrow,ncolumn;
    char ** db_result;
    sqlite3_get_table(db,select_query,&db_result,&nrow,&ncolumn,&errorMsg);
    printf("\n\
**************************************************************\n\
**                          周报！                          **\n\
**************************************************************\n\
姓名：\t\t平均时长：\t缺卡次数:\t工时不足次数：\n");
    for(int i = ncolumn; i < (nrow+1) * ncolumn; i += ncolumn){
        int in[5]={90000,90000,90000,90000,90000};
        int out[5]={90000,90000,90000,90000,90000};
        for(int m = 2;m<12;m++){
            sscanf(db_result[i+m],"%d",(m%2==0)?(in+(m-2)/2):(out+(m-3)/2));
        }
        int sum=0;
        int lossTimes =0;
        int NotEnoughTimes =0;
        for(int index = 0;index<5;index++){
            if(in[index]!=90000 && out[index]!=90000){
                int dayWorkSec = out[index]-in[index];
                sum+= dayWorkSec;
                if(dayWorkSec<min_WorkHour*3600) NotEnoughTimes++;
                continue;
            }
            NotEnoughTimes++;
            if(in[index]==90000) lossTimes++;
            if(out[index]==90000) lossTimes++;
        }
        char* name = db_result[i+1];
        int aver_h = sum/5/3600;
        int aver_m = ((sum/5)%3600)/60;
        printf("%s\t\t%d时%d分\t\t%d\t\t%d\n",name,aver_h,aver_m,lossTimes,NotEnoughTimes);
    }
    printf("\n\n\n");
}

#else
//姓名，年龄，性别，工号，手机号，邮箱地址


void sql_OpenDB(const char* address){
}
void sql_CloseDB(void){
    int res = sqlite3_close(db);
}
int sql_IsIdExit(int id){
    char* final = (char*)malloc(200);
    sprintf(final,"select * from %s",tabname_using);
    int nrow,ncolumn;
    char ** db_result;
    int res = sqlite3_get_table(db,final,&db_result,&nrow,&ncolumn,&errorMsg);
    int id_sele=0;
    for(int i=0;i<(nrow+1)*ncolumn;i+=ncolumn)
    {
        sscanf(db_result[i],"%d",&id_sele);
        if(id_sele==id){
            return i;
        }
    }
    return 0;
}
void sql_OpenOrCreatTab(const char* tabname){
    char* s1 = "create table if not exists ";
    char* s3 = "(id int(6),name char(20),mon_in int(20),mon_out int(20),tue_in int(20),tue_out int(20),wed_in int(20),wed_out int(20),thu_in int(20),thu_out int(20),fri_in int(20),fri_out int(20))";
    char* final = (char*)malloc(strlen(tabname)+strlen(s1)+strlen(s3));
    sprintf(final,"%s%s%s",s1,tabname,s3);
    sqlite3_exec(db,final,0,0,&errorMsg);
    tabname_using = (char* )tabname;
}
void sql_NewLine(int id,char* name){
    char final[200];
    sprintf(final,"insert into %s values(%d,'%s',90000,90000,90000,90000,90000,90000,90000,90000,90000,90000)",tabname_using,id,name);
    sqlite3_exec(db,final,0,0,&errorMsg);
}
void sql_DelLine(int id){
    char final[200];
    sprintf(final,"delete from %s where id=%d",tabname_using,id);
    sqlite3_exec(db,final,0,0,&errorMsg);
}
void sql_clock(int id,int dayInWeek,int secondInADay, int in1_out2 ,int min_workHour){
    char week[5];
    switch (dayInWeek)
    {
    case 1: strcpy(week, "mon_"); break;
    case 2: strcpy(week, "tue_"); break;
    case 3: strcpy(week, "wed_"); break;
    case 4: strcpy(week, "thu_"); break;
    case 5: strcpy(week, "fri_"); break;
    default:return;
    }
    char final[200];
    if(in1_out2==1){
        sprintf(final,"update %s set %s%s=%d where id=%d",tabname_using,week,"in",secondInADay,id);
        sqlite3_exec(db,final,0,0,&errorMsg);
        return;
    }
    sprintf(final,"update %s set %s%s=%d where id=%d",tabname_using,week,"out",secondInADay,id);
    //查询今天的上班打卡时间，并计算时常

    char select_query[100];
    sprintf(select_query,"select * from %s",tabname_using);
    int nrow,ncolumn;
    char ** db_result;
    sqlite3_get_table(db,select_query,&db_result,&nrow,&ncolumn,&errorMsg);
    int clkin_timep;
    sscanf(db_result[2*dayInWeek+sql_IsIdExit(id)],"%d",&clkin_timep);
    if (clkin_timep==90000){
        printf("您今日没有上班打卡！\n");
        return;
    }
    sqlite3_exec(db,final,0,0,&errorMsg);
    printf("%d:下班打卡成功\n",id);
    int hour_ = (secondInADay - clkin_timep)/3600;
    int min = ((secondInADay - clkin_timep)%3600) / 60;
    printf("您今天的工作时长是：%d小时%d分\n",hour_,min);
    if (hour_>=min_workHour)
        return;
    else
        printf("您的工作时常不足，还差%d分钟\n",(min_workHour*3600-(secondInADay-clkin_timep))/60);
}
void sql_showAll(void){
    char select_query[100];
    sprintf(select_query,"select * from %s",tabname_using);
    int nrow,ncolumn;
    char ** db_result;
    sqlite3_get_table(db,select_query,&db_result,&nrow,&ncolumn,&errorMsg);
    int i,j;
    int sec;
    for(i=0;i<(nrow+1)*ncolumn;i+=ncolumn)
    {
        for(j=0;j<ncolumn;j++)
        {
            if(j>1&&i>0){
                sscanf(db_result[i+j],"%d",&sec);
                if(sec>86400){
                    printf("无\t");
                }else{
                    printf("%d:%d\t",sec/3600,(sec%3600)/60);
                }
            }else{
                printf("%s\t",db_result[i+j]);
            }
        }
        printf("\n");
    }
}
void sql_showWeekReport(int min_WorkHour){
    
    char select_query[100];
    sprintf(select_query,"select * from %s",tabname_using);
    int nrow,ncolumn;
    char ** db_result;
    sqlite3_get_table(db,select_query,&db_result,&nrow,&ncolumn,&errorMsg);
    printf("\n\
**************************************************************\n\
**                          周报！                          **\n\
**************************************************************\n\
姓名：\t\t平均时长：\t缺卡次数:\t工时不足次数：\n");
    for(int i = ncolumn; i < (nrow+1) * ncolumn; i += ncolumn){
        int in[5]={90000,90000,90000,90000,90000};
        int out[5]={90000,90000,90000,90000,90000};
        for(int m = 2;m<12;m++){
            sscanf(db_result[i+m],"%d",(m%2==0)?(in+(m-2)/2):(out+(m-3)/2));
        }
        int sum=0;
        int lossTimes =0;
        int NotEnoughTimes =0;
        for(int index = 0;index<5;index++){
            if(in[index]!=90000 && out[index]!=90000){
                int dayWorkSec = out[index]-in[index];
                sum+= dayWorkSec;
                if(dayWorkSec<min_WorkHour*3600) NotEnoughTimes++;
                continue;
            }
            NotEnoughTimes++;
            if(in[index]==90000) lossTimes++;
            if(out[index]==90000) lossTimes++;
        }
        char* name = db_result[i+1];
        int aver_h = sum/5/3600;
        int aver_m = ((sum/5)%3600)/60;
        printf("%s\t\t%d时%d分\t\t%d\t\t%d\n",name,aver_h,aver_m,lossTimes,NotEnoughTimes);
    }
    printf("\n\n\n");
}


#endif