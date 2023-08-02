//
// main.cpp
// Defines the entry point for the console application.
// Created by 洪宸宇 on 14/7/2023
// 添加注释 29/7/2023
//

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "CalendarController.hpp"

using namespace std;

// 实现功能的函数
void InitialMenu(Calendar& calendar); // 初始菜单，选择功能
void ShowCalendar(Calendar& calendar); // 显示日历
void AddFestival(Calendar& calendar); // 添加节日
void DeleteFestival(Calendar& calendar); // 删除节日
void ResetFestival(Calendar& calendar); // 重置节日
void ShowMessage(Calendar& calendar); // 显示节日信息
void SearchFestival(Calendar& calendar); // 查找节日
void SortFestival(Calendar& calendar); // 排序节日
void FestivalTimer(Calendar& calendar); // 节日倒计时   

int main(int argc, const char * argv[]) {
    // 输入相应的文件
    // 文件名可以自行修改
    Calendar calendar("D:\\VScode\\cpp(code runner)\\test\\DateFestival.txt",
        "D:\\VScode\\cpp(code runner)\\test\\WeekDayFestival.txt");
    // 进入初始菜单
    InitialMenu(calendar);
    return 0;
}

// 初始菜单
// 选择功能
// 传入参数：日历类对象
// 返回值：无
void InitialMenu(Calendar& calendar)
{
    cout << "Welcome to the Calendar System!" << endl;
    cout << "-----------INITIALING----------" << endl;
    string Selection = "N";
    // 不选择退出时循环
    while (Selection != "Y" || Selection != "y")
    {
        // 选择功能：
        // 1. 显示某月日历
        // 2. 添加节日，包括日期节日和星期节日
        // 3. 删除节日
        // 4. 重置节日，包括节日名称和日期，以及起始年份
        // 5. 显示节日信息
        // 6. 排序节日，按照日期或名称排序
        // 7. 节日倒计时
        cout << "*******************************************" << endl;
        cout << "Please select the function you want to use:" << endl
             << "1. Show the calendar of a month" << endl
             << "2. Add a festival" << endl
             << "3. Delete a festival" << endl
             << "4. Reset a festival" << endl
             << "5. Show the message of a festival" << endl
             << "6. Search the festivals" << endl
             << "7. Sort the festivals" << endl
             << "8. Festival timer" << endl
             << "9. Exit" << endl;
        cout << "*******************************************" << endl;
        cin.sync();
        getline(cin, Selection);
        // 根据选择调用相应的函数
        if (Selection == "1")
        {
            ShowCalendar(calendar);
        }
        else if (Selection == "2")
        {
            AddFestival(calendar);
        }
        else if (Selection == "3")
        {
            DeleteFestival(calendar);
        }
        else if (Selection == "4")
        {
            ResetFestival(calendar);
        }
        else if (Selection == "5")
        {
            ShowMessage(calendar);
        }
        else if (Selection == "6")
        {
            SearchFestival(calendar);
        }
        else if (Selection == "7")
        {
            SortFestival(calendar);
        }
        else if (Selection == "8")
        {
            FestivalTimer(calendar);
        }
        else if (Selection == "9")
        {
            break;
        }
        else
        {
            cout << "Invalid input!" << endl;
        }
    }
    // 退出时保存数据
    cout << "Saving data..." << endl;
    cout << "Thank you for using this system. Hope to see you soon!" << endl;
}

// 显示日历
// 传入参数：日历类对象
// 返回值：无
void ShowCalendar(Calendar& calendar)
{
    unsigned int year, month;
    bool flag = false;
    // 根据标记判断是否成功，若不成功则重新输入
    while (flag == false)
    {
        cin.sync();
        cout << "Please input the year (1900~9999): " << endl;
        cin >> year;
        cout << "Please input the month (1~12): " << endl;
        cin >> month;
        // 尝试调用日历类的函数，若成功则标记为成功，否则输出错误信息
        auto result = calendar.ShowCalendar(year, month);
        if (result == RES::SUCCESS)
        {
            flag = true;
        }
        else
        {
            cout << ResString[static_cast<int> (result)] << endl;
        }
    }

    // 输出日历
    auto res = calendar.data.calendarlist;
    unsigned int FirstDay; // 获取第一天是星期几
    unsigned int LastDay; // 获取这个月有几天
    // 利用输入流分别赋值
    istringstream iss(res[0]);
    iss >> FirstDay >> LastDay;
    cout << "          " << year << "/" << month << "          " << endl;
    // 打印日历表头
    cout << "***************************" << endl;
    cout << "Sun Mon Tue Wed Thu Fri Sat" << endl;

    // 输出第一行的空格
    for (int i = 0; i < FirstDay; ++i) {
        cout << "    ";
    }

    // 输出日期
    for (int day = 1; day <= LastDay; ++day) {
        // 格式化输出日期，保持两位数
        cout << setw(3) << day << " ";

        // 换行处理
        if ((day + FirstDay) % 7 == 0) {
            cout << endl;
        }
    }

    // 输出最后一行的换行
    cout << endl;
    cout << "***************************" << endl;
    // 输出节日
    for (auto i = 1; i < res.size(); ++i)
    {
        cout << res[i] << endl;
    }
    cout << endl;
    return;
}

// 添加节日
// 传入参数：日历类对象
// 返回值：无
void AddFestival(Calendar& calendar)
{
    unsigned int FestivalType = 0;
    bool flag = false;
    // 根据标记判断是否成功添加，若不成功则重新输入
    while (flag == false)
    {
        cin.sync();
        // 选择添加的节日类型
        cout << "Which kind of festival do you want to add:" << endl
            << "1. Date festival" << endl
            << "2. Weekday festival" << endl;
        cin >> FestivalType;
        // 根据选择调用相应的函数
        // 添加日期节日
        if (FestivalType == 1)
        {
            unsigned int year, month, day;
            string name;
            cin.sync();
            cout << "Please input the name of the festival: " << endl;
            getline(cin, name);
            cout << "Please input the month (1~12): " << endl;
            cin >> month;
            cout << "Please input the day (1~31): " << endl;
            cin >> day;
            cout << "Please input the start year of the festival (1900~9999)" << endl
                << "If the festival was founded before 1900, please input 1900: " << endl;
            cin >> year;
            // 尝试调用日历类的函数，若成功则标记为成功，否则输出错误信息
            auto result = calendar.AddDateFestival(name, month, day, year);
            if (result == RES::SUCCESS)
            {
                flag = true;
            }
            else
            {
                cout << ResString[static_cast<int> (result)] << endl;
            }
        }    
        // 添加星期节日
        else if (FestivalType == 2)
        {
            unsigned int year, month, weektype, weekday;
            string name;
            cin.sync();
            cout << "Please input the name of the festival: " << endl;
            getline(cin, name);
            cout << "Please input the month (1~12): " << endl;
            cin >> month;
            cout << "Please input the weektype: " << endl
                << "1. The first week" << endl
                << "2. The second week" << endl
                << "3. The third week" << endl
                << "4. The fourth week" << endl
                << "0. The last week" << endl;
            cin >> weektype;
            cout << "Please input the weekday (1~7): " << endl;
            cin >> weekday;
            cout << "Please input the start year of the festival (1900~9999)" << endl
                << "If the festival was founded before 1900, please input 1900: " << endl;
            cin >> year;
            // 尝试调用日历类的函数，若成功则标记为成功，否则输出错误信息
            auto result = calendar.AddWeekDayFestival(name, month, weektype, weekday, year);
            if (result == RES::SUCCESS)
            {
                flag = true;
            }
            else
            {
                cout << ResString[static_cast<int> (result)] << endl;
            }
        }
        // 输入错误，重新输入
        else
        {
            cout << "Invalid input!" << endl;
        }
    }
    cout << "Success!" << endl;
    return;
}

// 删除节日
// 传入参数：日历类对象
// 返回值：无
void DeleteFestival(Calendar& calendar)
{
    bool flag = false;
    // 根据标记判断是否成功删除，若不成功则重新输入
    while (flag == false)
    {
        cout << "Please input the name of the festival you want to delete: " << endl;
        cin.sync();
        string name;
        getline(cin, name);
        // 尝试调用日历类的函数，若成功则标记为成功，否则输出错误信息
        auto result = calendar.DelFestival(name);
        if (result == RES::SUCCESS)
        {
            flag = true;
        }
        else
        {
            cout << ResString[static_cast<int> (result)] << endl;
        }
    }
    cout << "Success!" << endl;
    return;
}

// 重置节日
// 传入参数：日历类对象
// 返回值：无
void ResetFestival(Calendar& calendar)
{
    bool flag = false;
    unsigned int FestivalType = 0;
    // 根据标记判断是否成功重置，若不成功则重新输入
    while (flag == false)
    {
        cin.sync();
        // 选择重置的节日类型
        cout << "Which kind of festival do you want to reset:" << endl
            << "1. Date festival" << endl
            << "2. Weekday festival" << endl;
        cin >> FestivalType;
        // 根据选择调用相应的函数
        // 重置日期节日
        if (FestivalType == 1)
        {
            string name;
            unsigned int ChangeType = 0;
            cin.sync();
            cout << "Please input the name of the festival: " << endl;
            getline(cin, name);
            // 选择重置的部分
            // 1.重置名称
            // 2.重置日期
            // 3.重置起始年份
            cout << "Which part of the festival do you want to reset:" << endl
                << "1. Name" << endl
                << "2. Date" << endl
                << "3. Start year" << endl;
            cin >> ChangeType;
            // 根据选择调用相应的函数
            // 重置名称
            if (ChangeType == 1)
            {
                string newname;
                cin.sync();
                cout << "Please input the new name of the festival: " << endl;
                getline(cin, newname);
                // 尝试调用日历类的函数，若成功则标记为成功，否则输出错误信息
                auto result = calendar.ResetDateFestivalName(name, newname);
                if (result == RES::SUCCESS)
                {
                    flag = true;
                }
                else
                {
                    cout << ResString[static_cast<int> (result)] << endl;
                }
            }
            // 重置日期
            else if (ChangeType == 2)
            {
                unsigned int month, day;
                cout << "Please input the new month (1~12): " << endl;
                cin >> month;
                cout << "Please input the new day (1~31): " << endl;
                cin >> day;
                // 尝试调用日历类的函数，若成功则标记为成功，否则输出错误信息
                auto result = calendar.ResetDateFestivalDate(name, month, day);
                if (result == RES::SUCCESS)
                {
                    flag = true;
                }
                else
                {
                    cout << ResString[static_cast<int> (result)] << endl;
                }
            }
            // 重置起始年份
            else if (ChangeType == 3)
            {
                unsigned int year;
                cout << "Please input the new start year of the festival (1900~9999)" << endl
                    << "If the festival was founded before 1900, please input 1900: " << endl;
                cin >> year;
                // 尝试调用日历类的函数，若成功则标记为成功，否则输出错误信息
                auto result = calendar.ResetDateFestivalStartYear(name, year);
                if (result == RES::SUCCESS)
                {
                    flag = true;
                }
                else
                {
                    cout << ResString[static_cast<int> (result)] << endl;
                }
            }
            // 输入错误，重新输入
            else
            {
                cout << "Invalid input!" << endl;
            }
        }
        // 重置星期节日
        else if (FestivalType == 2)
        {
            string name;
            unsigned int ChangeType = 0;
            cin.sync();
            cout << "Please input the name of the festival: " << endl;
            getline(cin, name);
            // 选择重置的部分
            // 1.重置名称
            // 2.重置日期
            // 3.重置起始年份
            cout << "Which part of the festival do you want to reset:" << endl
                << "1. Name" << endl
                << "2. Date" << endl
                << "3. Start Year" << endl;
            cin >> ChangeType;
            // 根据选择调用相应的函数
            // 重置名称
            if (ChangeType == 1)
            {
                string newname;
                cin.sync();
                cout << "Please input the new name of the festival: " << endl;
                getline(cin, newname);
                // 调用日历类的函数，若成功则标记为成功，否则输出错误信息
                auto result = calendar.ResetWeekDayFestivalName(name, newname);
                if (result == RES::SUCCESS)
                {
                    flag = true;
                }
                else
                {
                    cout << ResString[static_cast<int> (result)] << endl;
                }
            }
            // 重置日期
            else if (ChangeType == 2)
            {
                unsigned int month, weektype, weekday;
                cout << "Please input the new month (1~12): " << endl;
                cin >> month;
                cout << "Please input the new weektype: " << endl
                    << "1. The first week" << endl
                    << "2. The second week" << endl
                    << "3. The third week" << endl
                    << "4. The fourth week" << endl
                    << "0. The last week" << endl;
                cin >> weektype;
                cout << "Please input the new weekday (1~7): " << endl;
                cin >> weekday;
                // 调用日历类的函数，若成功则标记为成功，否则输出错误信息
                auto result = calendar.ResetWeekDayFestivalDate(name, month, weektype, weekday);
                if (result == RES::SUCCESS)
                {
                    flag = true;
                }
                else
                {
                    cout << ResString[static_cast<int> (result)] << endl;
                }
            }
            // 重置起始年份
            else if (ChangeType == 3)
            {
                unsigned int year;
                cout << "Please input the new start year of the festival (1900~9999)" << endl
                    << "If the festival was founded before 1900, please input 1900: " << endl;
                cin >> year;
                // 调用日历类的函数，若成功则标记为成功，否则输出错误信息
                auto result = calendar.ResetWeekDayFestivalStartYear(name, year);
                if (result == RES::SUCCESS)
                {
                    flag = true;
                }
                else
                {
                    cout << ResString[static_cast<int> (result)] << endl;
                }
            }
            // 输入错误，重新输入
            else
            {
                cout << "Invalid input!" << endl;
            }
        }
        // 输入错误，重新输入
        else
        {
            cout << "Invalid input!" << endl;
        }
    }
    cout << "Success!" << endl;
    return;
}

// ShowMessage函数
// 用于显示节日信息
// 输入：日历类
// 输出：无
void ShowMessage(Calendar& calendar)
{
    bool flag = false;
    // 根据标记判断是否成功重置，若不成功则重新输入
    while (flag == false)
    {
        cin.sync();
        // 输入节日名称
        cout << "Please input the name of the festival you want to know: " << endl;
        string name;
        getline(cin, name);
        // 尝试调用日历类的函数，若成功则标记为成功，否则输出错误信息
        auto result = calendar.SearchFestival(name);
        if (result == RES::SUCCESS)
        {
            flag = true;
        }
        else
        {
            cout << ResString[static_cast<int> (result)] << endl;
        }
    }
    // 输出节日信息
    cout << calendar.data.festivalmessage << endl;
    return;
}

// SearchFestival函数
// 用于查询节日信息,在某年哪天
// 输入：日历类
// 输出：无
void SearchFestival(Calendar& calendar)
{
    bool flag = false;
    // 根据标记判断是否成功重置，若不成功则重新输入
    while (flag == false)
    {
        cin.sync();
        string name;
        unsigned int year;
        // 输入节日名称
        cout << "Please input the name of the festival you want to know: " << endl;
        getline(cin, name);
        cout << "Please input the year: " << endl;
        cin >> year;
        // 尝试调用日历类的函数，若成功则标记为成功，否则输出错误信息
        auto result = calendar.SearchFestival(name, year);
        if (result == RES::SUCCESS)
        {
            flag = true;
        }
        else
        {
            cout << ResString[static_cast<int> (result)] << endl;
        }
    }
    // 输出节日信息
    cout << calendar.data.festivalmessage << endl;
    return;
}

// SortFestival函数
// 用于排序节日
// 输入：日历类
// 输出：无
void SortFestival(Calendar& calendar)
{
    bool flag = false;
    while (flag == false)
    {
        cin.sync();
        // 输入两个日期和排序方法
        unsigned int year1;
        unsigned int year2;
        unsigned int month1;
        unsigned int month2;
        unsigned int day1;
        unsigned int day2;
        unsigned int SortMethod;
        cout << "Please input the start year (1900~9999): " << endl;
        cin >> year1;
        cout << "Please input the start month (1~12): " << endl;
        cin >> month1;
        cout << "Please input the start day (1~31): " << endl;
        cin >> day1;
        cout << "Please input the end year (1900~9999): " << endl;
        cin >> year2;
        cout << "Please input the end month (1~12): " << endl;
        cin >> month2;
        cout << "Please input the end day (1~31): " << endl;
        cin >> day2;
        // 1.按照名称升序
        // 2.按照名称降序
        // 3.按照日期升序
        // 4.按照日期降序
        cout << "Please input the sort method: " << endl
            << "1. Sort by name up" << endl
            << "2. Sort by name down" << endl
            << "3. Sort by date up" << endl
            << "4. Sort by date down" << endl;
        cin >> SortMethod;
        // 调用日历类的函数，若成功则标记为成功，否则输出错误信息
        auto result = calendar.SortFestival(year1, month1, day1, year2, month2, day2, SortMethod);
        if (result == RES::SUCCESS)
        {
            flag = true;
        }
        else
        {
            cout << ResString[static_cast<int> (result)] << endl;
        }
    }

    // 输出排序结果
    for (auto res : calendar.data.festivallist)
    {
        cout << res << endl;
    }
    return;
}

// FestivalTimer函数
// 用于倒计时
// 输入：日历类
// 输出：无
void FestivalTimer(Calendar& calendar)
{
    bool flag = false;
    // 根据标记判断是否成功重置，若不成功则重新输入
    while (flag == false)
    {
        // 输入节日名称
        cout << "Please input the name of the festival you want to count down: " << endl;
        cin.sync();
        string name;
        getline(cin, name);
        // 尝试调用日历类的函数，若成功则标记为成功，否则输出错误信息
        auto result = calendar.CountDown(name);
        if (result == RES::SUCCESS)
        {
            flag = true;
        }
        else
        {
            cout << ResString[static_cast<int> (result)] << endl;
        }
    }
    // 输出倒计时结果
    cout << calendar.data.festivalcount << endl;
    return;
}  