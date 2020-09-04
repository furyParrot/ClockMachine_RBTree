#pragma once

int usr_time_Init(void);        //初始化时间，返回离自动关闭剩余剩余的秒数
int usr_time_GetDayInWeek();    //获取当前星期，1-7
int usr_time_GetSecInDay();     //获取当前时刻的秒数（从当日0:00起）

int usr_time_GetYear();
int usr_time_GetDayInYear();