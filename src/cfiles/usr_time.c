#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include "../head/usr_time.h"
#ifdef __TEST__
time_t start_timet;
int usr_time_Init(void){//返回离自动关闭剩余的秒数
    time(&start_timet);
    return 6*(24*5+5);//6秒等于一小时，共5天零5小时。
}
time_t time_rt;
int usr_time_GetDayInWeek(){
    time(&time_rt);
    int res = (int)((time_rt-start_timet+42)/144)+1;
    res = (res<1)?1:((res>5)?5:res);
    return res;
}
int usr_time_GetSecInDay(){
    time(&time_rt);
    return ((time_rt-start_timet+42)%144)*600;
}
#else
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

#endif