#ifndef __USR_SQL3_H__
#define __USR_SQL3_H__
/* 封装了一些数据库操作 ，分别是：
*  打开、关闭数据库             sql_OpenDB      sql_CloseDB
*  检查id是否存在              sql_IsIdExit
*  打开表格                   sql_OpenOrCreatTab
*  新建一行数据                sql_NewLine
*  删除一行数据                sql_DelLine
*  打卡                       sql_clock
*  打印当前表格                sql_showAll
*  从当前表格生成并打印周报表    sql_showWeekReport
*/


typedef struct{
    char name[20];
    int age;
    char gender;
    int id;
    long phonenum;
    char email[100];
}PersonalInfo;
typedef struct{
    int mon_in,mon_out,tue_in,tue_out,wed_in,wed_out,thu_in,thu_out,fri_in,fri_out;
}ClockInInfo;
typedef struct{
    PersonalInfo prsInfo;
    ClockInInfo clkInfo;
}Employee;


void sql_OpenDB(const char * address);
void sql_CloseDB(void);
int sql_IsIdExit(int id);
void sql_OpenOrCreatTab(const char* address);
void sql_NewLine(int id, char* name);
void sql_DelLine(int id);
void sql_clock(int id,int dayInWeek,int secondInADay, int in1_out2, int min_workHour);
void sql_showAll(void);
void sql_showWeekReport(int min_WorkHour);
#endif