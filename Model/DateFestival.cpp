//
// DateFestival.cpp
// Implementation of the DateFestival class.
// Created by 洪宸宇 on 14/7/2023
// 添加注释 29/7/2023
//

#include "DateFestival.hpp"
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

using std::ostream;
using std::istream;
using std::ofstream;
using std::ifstream;
using std::endl;
using std::to_string;
using std::invalid_argument;
using std::stringstream;

vector<string> DateFestival::m_AllDays = { "None", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th",
                                          "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th",
                                          "17th", "18th", "19th", "20th", "21st", "22nd", "23rd", "24th",
                                          "25th", "26th", "27th", "28th", "29th", "30th", "31st"};
DateFestival::FestivalFormat DateFestival::DeFesFormat = DateFestival::FestivalFormat::backslash;

// 构造函数
// 传入节日名称，日期对象
DateFestival::DateFestival(const string& Name, const Date& Date) : m_Date(Date), Festival(Name) {m_FestivalKind = 1;}

// 构造函数
// 传入节日名称，月份，日期，年份
DateFestival::DateFestival(const string& Name, const unsigned int Month, const unsigned int Day, const unsigned int Year) 
    : m_Date(Year, Month, Day), Festival(Name) {m_FestivalKind = 1;}

// 析构函数
// 释放所有智能指针等资源
DateFestival::~DateFestival() {}

// Add函数
// 传入节日名称，日期对象
// 返回智能指针
FesPtr DateFestival::Add(const string& Name, const Date& Date)
{
    // 判断是否已经存在，若存在则抛出异常
    for (auto festival : m_AllFestival)
    {
        if (festival->name == Name)
        {
            throw invalid_argument("Festival already exists!");
        }
    }
    FesPtr festivalPtr = FesPtr(new DateFestival(Name, Date));
    m_AllFestival.push_back(festivalPtr);
    return festivalPtr;
}

// Add函数
// 传入节日名称，月份，日期，年份
// 返回智能指针
FesPtr DateFestival::Add(const string& Name, const unsigned int Month, const unsigned int Day, const unsigned int Year)
{
    Add(Name, Date(Year, Month, Day));
}

// ListAdd函数，用于添加到搜索列表  
// 传入节日名称，日期对象
// 返回智能指针
FesPtr DateFestival::ListAdd(const string& Name, const Date& Date)
{
    // 判断是否已经存在m_SearchList中，若存在则抛出异常
    for (auto festival : m_SearchList)
    {
        if (festival->name == Name)
        {
            throw invalid_argument("Festival already exists!");
        }
    }
    m_SearchList.push_back(FesPtr(new DateFestival(Name, Date)));
    return m_SearchList.back();
}

// Del函数，用于删除节日
// 传入节日名称
// 无返回值
void DateFestival::Del(const string& Name)
{
    // 判断是否存在，若不存在则抛出异常
    for (auto it = m_AllFestival.begin(); it != m_AllFestival.end(); ++it)
    {
        if ((*it)->name == Name)
        {
            (*it).reset();
            m_AllFestival.erase(it);
            return;
        }
    }
    throw invalid_argument("Festival does not exist!");
}

// ResetName函数，用于重置节日名称
// 传入节日名称，新的节日名称
// 无返回值
void DateFestival::ResetName(const string& Name, const string& NewName)
{
    // 根据名称判断是否存在，若不存在则抛出异常
    for (auto& festival : m_AllFestival)
    {
        if (festival->name == Name)
        {
            festival->Reset(NewName);
            return;
        }
    }
    throw invalid_argument("Festival does not exist!");
}

// ResetName函数，用于重置节日名称
// 传入新的节日名称
// 无返回值
void DateFestival::ResetName(const string& NewName)
{
    Reset(NewName);
    return;
}

// ResetDate函数，用于重置节日日期
// 传入节日名称，日期对象
// 无返回值
void DateFestival::ResetDate(const string& Name, const Date& Date)
{
    // 根据名称判断是否存在，若不存在则抛出异常
    for (auto& festival : m_AllFestival)
    {
        if (festival->name == Name)
        {
            static_cast<DateFestival*> (festival.get())->m_Date = Date;
            return;
        }
    }
    throw invalid_argument("Festival does not exist!");
}

// ResetDate函数，用于重置节日日期
// 传入日期对象
// 无返回值
void DateFestival::ResetDate(const Date& Date)
{
    m_Date = Date;
    return;
}

// ResetDate函数，用于重置节日日期
// 传入节日名称，月份，日期，年份
// 无返回值
void DateFestival::ResetDate(const string& Name, const unsigned int Month, const unsigned int Day, const unsigned int Year)
{
    ResetDate(Name, Date(Year, Month, Day));
}

// ResetDate函数，用于重置节日日期
// 传入月份，日期，年份
// 无返回值
void DateFestival::ResetDate(const unsigned int Month, const unsigned int Day, const unsigned int Year)
{
    ResetDate(Date(Year, Month, Day));
}

// ResetYear函数，用于重置节日年份
// 传入节日名称，年份
// 无返回值
void DateFestival::ResetYear(const string& Name, const unsigned int Year)
{
    // 根据名称判断是否存在，若不存在则抛出异常
    for (auto& festival : m_AllFestival)
    {
        if (festival->name == Name)
        {
            static_cast<DateFestival*> (festival.get())->m_Date.SetYear(Year);
            return;
        }
    }
    throw invalid_argument("Festival does not exist!");
}

// ResetYear函数，用于重置节日年份
// 传入年份
// 无返回值
void DateFestival::ResetYear(const unsigned int Year)
{
    m_Date.SetYear(Year);
    return;
}

// ResetMonth函数，用于重置节日月份
// 传入节日名称，月份
// 无返回值
void DateFestival::ResetMonth(const string& Name, const unsigned int Month)
{
    // 根据名称判断是否存在，若不存在则抛出异常
    for (auto& festival : m_AllFestival)
    {
        if (festival->name == Name)
        {
            static_cast<DateFestival*> (festival.get())->m_Date.SetMonth(Month);
            return;
        }
    }
    throw invalid_argument("Festival does not exist!");
}

// ResetMonth函数，用于重置节日月份
// 传入月份
// 无返回值
void DateFestival::ResetMonth(const unsigned int Month)
{
    m_Date.SetMonth(Month);
    return;
}

// ResetDay函数，用于重置节日日期
// 传入节日名称，日期
// 无返回值
void DateFestival::ResetDay(const string& Name, const unsigned int Day)
{
    // 根据名称判断是否存在，若不存在则抛出异常
    for (auto& festival : m_AllFestival)
    {
        if (festival->name == Name)
        {
            static_cast<DateFestival*> (festival.get())->m_Date.SetDay(Day);
            return;
        }
    }
    throw invalid_argument("Festival does not exist!");
}

// ResetDay函数，用于重置节日日期
// 传入日期
// 无返回值
void DateFestival::ResetDay(const unsigned int Day)
{
    m_Date.SetDay(Day);
    return;
}

// SearchName函数，根据节日名称得到节日指针
// 传入节日名称
// 返回节日指针
FesPtr DateFestival::SearchName(const string& Name)
{
    // 根据名称判断是否存在，若不存在则抛出异常
    for (auto& festival : m_AllFestival)
    {
        if (festival->name == Name)
        {
            return festival;
        }
    }
    throw invalid_argument("Festival does not exist!");
}

// SearchDay函数，搜索某一天有哪些节日
// 传入日期对象
// 返回节日指针列表
vector<FesPtr> DateFestival::SearchDay(const Date& Date)
{
    // 清空搜索列表
    Festival::ClearSearchList(m_SearchList);
    for (auto& festival : m_AllFestival)
    {
        // 判断日期是否相同,并且设立年份在前
        if (static_cast<DateFestival*> (festival.get())->m_Date.month == Date.month &&
            static_cast<DateFestival*> (festival.get())->m_Date.day == Date.day &&
            static_cast<DateFestival*> (festival.get())->m_Date.year <= Date.year)
        {
            m_SearchList.push_back(festival);
        }
    }
    // 若搜索列表为空，则抛出异常
    if (m_SearchList.empty())
    {
        throw invalid_argument("Festival does not exist!");
    }
    return m_SearchList;
}

// SearchDay函数，搜索某一天有哪些节日
// 传入节日名称，月份，日期，年份
// 返回节日指针列表
vector<FesPtr> DateFestival::SearchDay(const unsigned int Month, const unsigned int Day, const unsigned int Year)
{
    return SearchDay(Date(Year, Month, Day));
}

// SearchMonth函数，搜索某一月有哪些节日
vector<FesPtr> DateFestival::SearchMonth(const unsigned int Month, const unsigned int Year)
{
    // 清空搜索列表
    Festival::ClearSearchList(m_SearchList);
    for (auto& festival : m_AllFestival)
    {
        // 判断月份是否相同,并且设立年份在前
        if (static_cast<DateFestival*> (festival.get())->m_Date.month == Month &&
            static_cast<DateFestival*> (festival.get())->m_Date.year <= Year)
        {
            m_SearchList.push_back(festival);
        }
    }
    // 若搜索列表为空，则抛出异常
    if (m_SearchList.empty())
    {
        throw invalid_argument("Festival does not exist!");
    }
    return m_SearchList;
}

// Search函数，搜索任意两天之间有哪些节日
// 传入两个日期对象
// 返回节日指针列表
vector<FesPtr> DateFestival::Search(const Date& Date1, const Date& Date2)
{
    // 清空搜索列表
    Festival::ClearSearchList(m_SearchList);
    // 先不考虑2月29日的情况，分三种情况讨论
    // 1. 两个日期在同一年
    if (Date2.year == Date1.year)
    {
        for (auto& festival : m_AllFestival)
        {
            // 设置节日在该年的日期，再进行比较
            unsigned int ayear = static_cast<DateFestival*> (festival.get())->m_Date.year;
            Month amonth = static_cast<DateFestival*> (festival.get())->m_Date.month;
            unsigned int aday = static_cast<DateFestival*> (festival.get())->m_Date.day; 
            if (ayear <= Date1.year && (amonth != Month(2) || aday != 29)
                && Date(Date1.year, amonth, aday) >= Date1 
                && Date(Date1.year, amonth, aday) <= Date2)
            {
                m_SearchList.push_back(festival);
            }
        }
    }
    // 两个日期只跨了一年
    else if (Date2.year == (Date1.year + 1))
    {
        for (auto& festival : m_AllFestival)
        {
            // 分别设置节日在该两年的日期，再进行比较
            unsigned int ayear = static_cast<DateFestival*> (festival.get())->m_Date.year;
            Month amonth = static_cast<DateFestival*> (festival.get())->m_Date.month;
            unsigned int aday = static_cast<DateFestival*> (festival.get())->m_Date.day;
            if (ayear <= Date1.year && (amonth != Month(2) || aday != 29)
                && Date(Date1.year, amonth, aday) >= Date1)
            {
                m_SearchList.push_back(festival);
            }
            if (ayear <= Date2.year && (amonth != Month(2) || aday != 29)
                && Date(Date2.year, amonth, aday) <= Date2)
            {
                m_SearchList.push_back(festival);
            }
        }
    }
    // 两个日期跨了两年及以上，肯定包含所有节日
    else
    {
        for (auto& festival : m_AllFestival)
        {
            if (static_cast<DateFestival*> (festival.get())->m_Date.month != Month(2)
                || static_cast<DateFestival*> (festival.get())->m_Date.day != 29)
            {
                m_SearchList.push_back(festival);
            }
        }
    }
    // 针对2月29日的情况
    for (auto& festival : m_AllFestival)
    {
        if (static_cast<DateFestival*> (festival.get())->m_Date.month == Month(2)
            && static_cast<DateFestival*> (festival.get())->m_Date.day == 29)
        {
            bool flag = false;
            // 判断两年之间是否有闰年
            // 若两年之间有闰年，则该节日一定存在
            for (int i = Date1.year; i <= Date2.year; i++)
            {
                if (Date::IsLeapYear(i) && i != Date1.year && i != Date2.year)
                {
                    flag = true;
                    break;
                }
            }
            // 再判断这两年是否有闰年，有闰年再比较
            if (Date1.IsLeapYear() && Date(Date1.year, 2, 29) >= Date1 && Date(Date1.year, 2, 29) <= Date2)
            {
                flag = true;
            }
            if (Date2.IsLeapYear() && Date(Date2.year, 2, 29) <= Date2 && Date(Date2.year, 2, 29) >= Date1)
            {
                flag = true;
            }
            // 上述情况满足一次便可以添加该节日
            if (flag) 
            {
                m_SearchList.push_back(festival);
            }
        }
    }
    // 若搜索列表为空，则抛出异常
    if (m_SearchList.empty())
    {
        throw invalid_argument("Festival does not exist!");
    }
    return m_SearchList;    
}

// Search函数，搜索任意两天之间有哪些节日
// 传入参数为两个日期的年月日
// 返回值为搜索列表
vector<FesPtr> DateFestival::Search(const unsigned int Year1, const unsigned int Month1, const unsigned int Day1, 
        const unsigned int Year2,const unsigned int Month2, const unsigned int Day2)
{
    return Search(Date(Year1, Month1, Day1), Date(Year2, Month2, Day2));
}

// 重载==运算符
// 根据日期判断两个节日是否相同
// 传入参数为一个DateFestival类的引用
// 返回值为bool类型
bool DateFestival::operator==(const DateFestival& Source) const
{
    return m_Date == Source.m_Date;
}

// 重载!=运算符
// 根据日期判断两个节日是否不同
// 传入参数为一个DateFestival类的引用
// 返回值为bool类型
bool DateFestival::operator!=(const DateFestival& Source) const
{
    return m_Date != Source.m_Date;
}

// 重载<运算符
// 根据日期判断两个节日的先后
// 传入参数为一个DateFestival类的引用
// 返回值为bool类型
bool DateFestival::operator<(const DateFestival& Source) const
{
    return m_Date < Source.m_Date;
}

// 重载>运算符
// 根据日期判断两个节日的先后
// 传入参数为一个DateFestival类的引用
// 返回值为bool类型
bool DateFestival::operator>(const DateFestival& Source) const
{
    return m_Date > Source.m_Date;
}

// 重载<=运算符
// 根据日期判断两个节日的先后
// 传入参数为一个DateFestival类的引用
// 返回值为bool类型
bool DateFestival::operator<=(const DateFestival& Source) const
{
    return m_Date <= Source.m_Date;
}

// 重载>=运算符
// 根据日期判断两个节日的先后
// 传入参数为一个DateFestival类的引用
// 返回值为bool类型
bool DateFestival::operator>=(const DateFestival& Source) const
{
    return m_Date >= Source.m_Date;
}

// SortByNameUp函数，按照节日名称升序排序
// 传入参数为两个日期的Date类
// 返回值为排序后的节日列表
vector<FesPtr> DateFestival::SortByNameUp(const Date& Date1, const Date& Date2)
{
    // 利用Search函数搜索出所有符合条件的节日
    // 若搜索列表为空，则抛出异常
    vector<FesPtr> result = Search(Date1, Date2);
    if (result.empty())
    {
        throw invalid_argument("Festival does not exist!");
    }
    // 利用lambda表达式对搜索列表进行排序
    sort(result.begin(), result.end(), [](const FesPtr& Source1, const FesPtr& Source2)
    {
        return Source1->name < Source2->name;
    });
    return result;
}

// SortByNameUp函数，按照节日名称升序排序
// 传入参数为两个日期的年月日
// 返回值为排序后的节日列表
vector<FesPtr> DateFestival::SortByNameUp(const unsigned int Year1, const unsigned int Month1, const unsigned int Day1, 
        const unsigned int Year2,const unsigned int Month2, const unsigned int Day2)
{
    return SortByNameUp(Date(Year1, Month1, Day1), Date(Year2, Month2, Day2));
}

// SortByDateUp函数，按照日期升序排序
// 传入参数为两个日期的Date类
// 返回值为排序后的节日列表
vector<FesPtr> DateFestival::SortByDateUp(const Date& Date1, const Date& Date2)
{
    // 利用Search函数搜索出所有符合条件的节日
    // 若搜索列表为空，则抛出异常
    vector<FesPtr> result = Search(Date1, Date2);
    if (result.empty())
    {
        throw invalid_argument("Festival does not exist!");
    }
    // 利用lambda表达式对搜索列表进行排序
    sort(result.begin(), result.end(), [](const FesPtr& Source1, const FesPtr& Source2)
    {
        auto day1 = static_cast<DateFestival*> (Source1.get())->date.day;
        auto day2 = static_cast<DateFestival*> (Source2.get())->date.day;
        auto month1 = static_cast<DateFestival*> (Source1.get())->date.month;
        auto month2 = static_cast<DateFestival*> (Source2.get())->date.month;
        return Date(2000, month1, day1) < Date(2000, month2, day2); // 2000年是闰年，可以用来判断日期的先后
    });
    return result;
}

// SortByDateUp函数，按照日期升序排序
// 传入参数为两个日期的年月日
// 返回值为排序后的节日列表
vector<FesPtr> DateFestival::SortByDateUp(const unsigned int Year1, const unsigned int Month1, const unsigned int Day1, 
        const unsigned int Year2,const unsigned int Month2, const unsigned int Day2)
{
    return SortByDateUp(Date(Year1, Month1, Day1), Date(Year2, Month2, Day2));
}

// SortByNameDown函数，按照节日名称降序排序
// 传入参数为两个日期的Date类
// 返回值为排序后的节日列表
vector<FesPtr> DateFestival::SortByNameDown(const Date& Date1, const Date& Date2)
{
    // 利用Search函数搜索出所有符合条件的节日
    // 若搜索列表为空，则抛出异常
    vector<FesPtr> result = Search(Date1, Date2);
    if (result.empty())
    {
        throw invalid_argument("Festival does not exist!");
    }
    // 利用lambda表达式对搜索列表进行排序
    sort(result.begin(), result.end(), [](const FesPtr& Source1, const FesPtr& Source2)
    {
        return Source1->name > Source2->name;
    });
    return result;
}

// SortByNameDown函数，按照节日名称降序排序
// 传入参数为两个日期的年月日
// 返回值为排序后的节日列表
vector<FesPtr> DateFestival::SortByNameDown(const unsigned int Year1, const unsigned int Month1, const unsigned int Day1, 
        const unsigned int Year2,const unsigned int Month2, const unsigned int Day2)
{
    return SortByNameDown(Date(Year1, Month1, Day1), Date(Year2, Month2, Day2));
}

// SortByDateDown函数，按照日期降序排序
// 传入参数为两个日期的Date类
// 返回值为排序后的节日列表
vector<FesPtr> DateFestival::SortByDateDown(const Date& Date1, const Date& Date2)
{
    // 利用Search函数搜索出所有符合条件的节日
    // 若搜索列表为空，则抛出异常
    vector<FesPtr> result = Search(Date1, Date2);
    if (result.empty())
    {
        throw invalid_argument("Festival does not exist!");
    }
    // 利用lambda表达式对搜索列表进行排序
    sort(result.begin(), result.end(), [](const FesPtr& Source1, const FesPtr& Source2)
    {
        auto day1 = static_cast<DateFestival*> (Source1.get())->date.day;
        auto day2 = static_cast<DateFestival*> (Source2.get())->date.day;
        auto month1 = static_cast<DateFestival*> (Source1.get())->date.month;
        auto month2 = static_cast<DateFestival*> (Source2.get())->date.month;
        return Date(2000, month1, day1) > Date(2000, month2, day2); // 2000年是闰年，可以用来判断日期的先后
    });
    return result;
}

// SortByDateDown函数，按照日期降序排序
// 传入参数为两个日期的年月日
// 返回值为排序后的节日列表
vector<FesPtr> DateFestival::SortByDateDown(const unsigned int Year1, const unsigned int Month1, const unsigned int Day1, 
        const unsigned int Year2,const unsigned int Month2, const unsigned int Day2)
{
    return SortByDateDown(Date(Year1, Month1, Day1), Date(Year2, Month2, Day2));
}

// Tostring函数，将节日信息转换为字符串
// 传入参数为输出格式，默认为斜杠格式
// 返回值为节日信息的字符串
string DateFestival::ToString(const enum FestivalFormat& aformat) const
{
    return ToString(*this, aformat);
}

// Tostring函数，将节日信息转换为字符串
// 传入参数为节日信息和输出格式，默认为斜杠格式
// 返回值为节日信息的字符串
string DateFestival::ToString(const DateFestival& Festival, const enum FestivalFormat& aformat)
{
    string result;
    // 分三种不同的格式，由日期决定
    // 斜杠格式：节日名称 月份/日期
    // 连字符格式：节日名称 月份-日期
    // 字符格式：节日名称 月份 日期
    switch (aformat)
    {
    case FestivalFormat::backslash:
        result = Festival.name + " " + to_string(Festival.date.month.value) + "/" + to_string(Festival.date.day);
        break;
    case FestivalFormat::hyphen:
        result = Festival.name + " " + to_string(Festival.date.month.value) + "-" + to_string(Festival.date.day);
        break;
    case FestivalFormat::character:
        result = Festival.name + " " + Festival.date.month.month + " " + DateFestival::m_AllDays[Festival.date.day];
        break;
    default:
        throw invalid_argument("Invalid format!");
        break;
    }
    return result;
}

// Tostring函数，将节日信息转换为字符串
// 传入参数为节日名称、日期和输出格式，默认为斜杠格式
// 返回值为节日信息的字符串
string DateFestival::ToString(const string& Festival, const Date& Date, const enum FestivalFormat& aformat)
{
    return DateFestival(Festival, Date).ToString(aformat);
}

// Tostring函数，将节日信息转换为字符串
// 传入参数为节日名称、年月日和输出格式，默认为斜杠格式
// 返回值为节日信息的字符串
string DateFestival::ToString(const string& Festival, const unsigned int Month, const unsigned int Day, 
    const enum FestivalFormat& aformat)
{
    return DateFestival(Festival, Date(1900, Month, Day)).ToString(aformat);
}

// 重载输出运算符
// 传入参数为输出流和节日信息
// 返回值为输出流
ostream& operator<<(ostream& os, const DateFestival& Source)
{
    // 利用ToString函数将节日信息转换为字符串
    os << Source.ToString();
    return os;
}

// 重载输出运算符，用于改变输出格式
// 传入参数为输出流和输出格式
// 返回值为输出流
ostream& operator<<(ostream& Output, const enum DateFestival::FestivalFormat& aformat)
{
    DateFestival::DeFesFormat = aformat;
    return Output;
}

// ReadFromFile函数，从文件中读取节日信息
// 传入参数为文件名
// 返回值为空
void DateFestival::ReadFromFile(const string& FileName)
{
    ifstream fin(FileName);
    if (!fin.is_open())
    {
        throw invalid_argument("File does not exist!");
    }
    string input;
    // 读取文件中的每一行，将节日信息添加到节日列表中
    //利用stringstream将字符串分割为节日名称和日期
    while (getline(fin, input))
    {
        stringstream ss(input);
        string name;
        unsigned int year;
        unsigned int month;
        unsigned int day;
        getline(ss, name, ':');
        ss >> month >> day >> year;
        if (ss.fail())
        {
            throw invalid_argument("Invalid input!");
        }
        Add(name, Date(year, month, day));
    }
    fin.close();
}

// WriteToFile函数，将节日信息写入文件
// 传入参数为文件名
// 返回值为空
void DateFestival::WriteToFile(const string& FileName)
{
    ofstream fout(FileName);
    if (!fout.is_open())
    {
        throw invalid_argument("File does not exist!");
    }
    // 将节日列表中的每一个节日信息写入文件
    // 按照一定格式，确保读取时更容易
    // 节日： 月份 日期 年份（起始年份）
    for (const auto& festival : m_AllFestival)
    {
        fout << static_cast<DateFestival*> (festival.get())->name << ": " 
            << static_cast<DateFestival*> (festival.get())->date.month.value << " " 
            << static_cast<DateFestival*> (festival.get())->date.day << " " 
            << static_cast<DateFestival*> (festival.get())->date.year << endl;
    }
    fout.close();
}