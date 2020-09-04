#include "usr_time.h"
#include <time.h>
#include <stdio.h>
time_t a ;
struct tm* b;
int usr_time_Init(void){//返回离自动关闭剩余的秒数
    time(&a);
    b = localtime(&a);
    if(b->tm_wday>5){
        return (12-(b->tm_wday))*86400+(24-(b->tm_hour)*3600)+(60-(b->tm_min)*60+(b->tm_sec));
    }
    return (5-(b->tm_wday))*86400+(86400-usr_time_GetSecInDay());
}
int usr_time_GetDayInWeek(){
    time(&a);
    return localtime(&a)->tm_wday;
}
int usr_time_GetSecInDay(){
    time(&a);
    b = localtime(&a);
    return (b->tm_hour)*3600+(b->tm_min)*60+(b->tm_sec);
}
int usr_time_GetYear(){
    time(&a);
    return localtime(&a)->tm_year;
}

int usr_time_GetDayInYear(){
    time(&a);
    return localtime(&a)->tm_yday;
}