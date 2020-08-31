将作为一个打卡机模块来出现，

拥有以下功能：

三个结构体：


//记录着一个人的基本信息
typedef struct Stru_BaseInfo{
    char name[20];
    int age;
    char gender;
    int id;
    long phonenum;
    char email[100];
}Stru_BaseInfo;

//记录着每天打卡时刻的秒数
typedef struct Stru_ClockInfo{
    int mon_in,mon_out,tue_in,tue_out,wed_in,wed_out,thu_in,thu_out,fri_in,fri_out;

}Stru_ClockInfo;

typedef struct Stru_FullInfo{
    PersonalInfo prsInfo;
    ClockInInfo clkInfo;
}Stru_FullInfo;


1，添加员工  int AddEmployee(Stru_BaseInfo)   //添加员工，返回值代表成功
            int AddEmployee(Stru_BaseInfo a , Stru_ClockInfo b)

2，删除员工  int DelEmployee(int id)   //删除员工，返回值代表成功
3，查看考勤表,(遍历红黑树)
4，上、下班打卡  int SomeBodyClockIn(int id) 
                //返回值是1就是打卡成功，返回0就是查无此人。

5，导出考勤文件
        char* LoadVerbFile(char* filename);
6，加载考勤文件
7，加载考勤文件（仅个人信息）。

