//
// WeekDayFestival.cpp
// Implementation of the WeekDayFestival class.
// Created by 洪宸宇 on 14/7/2023
// 添加注释 29/7/2023
//

#include "WeekDayFestival.hpp"
#include "DateFestival.hpp"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

using std::invalid_argument;
using std::stringstream;
using std::ostream;
using std::istream;
using std::ofstream;
using std::ifstream;
using std::endl;
using std::to_string;

// 将星期序数转换为字符串
const string WeekDayFestival::WeekTypeStr[5] = { "Last", "First", "Second", "Third", "Fourth" };

// 构造函数
// 传入节日名称，月份对象，星期类型，星期对象，年份
WeekDayFestival::WeekDayFestival(const string& Name, const Month& Month, const WeekType& WeekType, const WeekDay& WeekDay, const unsigned int Year)
    : Festival(Name), m_Month(Month), m_WeekType(WeekType), m_WeekDay(WeekDay) {
    // 检查年份是否合法
    if (Year < Min_year) {
        throw invalid_argument("Invalid year!");
    }
    m_StartYear = Year;
    m_FestivalKind = 2;
}  

// 构造函数
// 传入节日名称，月份序数，星期类型序数，星期序数，年份
WeekDayFestival::WeekDayFestival(const string& Name, unsigned int Month, unsigned int WeekType, unsigned int WeekDay, const unsigned int Year)
    : Festival(Name), m_Month(Month), m_WeekDay(WeekDay) {
    m_WeekType = IntToWeekType(WeekType);
    // 检查年份是否合法
    if (Year < Min_year) {
        throw invalid_argument("Invalid year!");
    }
    m_StartYear = Year;
    m_FestivalKind = 2;
}


// 构造函数
// 传入节日名称，月份字符串，星期类型字符串，星期字符串，年份
WeekDayFestival::WeekDayFestival(const string& Name, const string& Month, const string& WeekType, const string& WeekDay, const unsigned int Year)
    : Festival(Name), m_Month(Month), m_WeekDay(WeekDay) {
    // 检查星期类型字符串是否合法
    for (int i = 0; i < 5; ++i) {
        if (WeekType == WeekTypeStr[i]) {
            m_WeekType = IntToWeekType(i);
            m_StartYear = Year;
            m_FestivalKind = 2;
            return;
        }
    }
    throw invalid_argument("Invalid WeekType!");
}

WeekDayFestival::~WeekDayFestival() {}

// Add函数
// 向节日列表中添加节日
// 传入节日名称，月份对象，星期类型，星期对象，年份
// 返回节日指针
FesPtr WeekDayFestival::Add(const string& Name, const Month& Month, const WeekType& WeekType, const WeekDay& WeekDay, const unsigned int Year) {
    // 检查节日是否已存在,若存在则抛出异常
    for (auto festival : m_AllFestival)
    {
        if (festival->name == Name)
        {
            throw invalid_argument("Festival already exists!");
        }
    }
    m_AllFestival.push_back(FesPtr(new WeekDayFestival(Name, Month, WeekType, WeekDay, Year)));
    return m_AllFestival.back();
}

// Add函数
// 向节日列表中添加节日
// 传入节日名称，月份序数，星期类型序数，星期序数，年份
// 返回节日指针
FesPtr WeekDayFestival::Add(const string& Name, unsigned int Month, unsigned int WeekType, unsigned int WeekDay, const unsigned int Year) {
    // 检查节日是否已存在,若存在则抛出异常
    for (auto festival : m_AllFestival)
    {
        if (festival->name == Name)
        {
            throw invalid_argument("Festival already exists!");
        }
    }
    m_AllFestival.push_back(FesPtr(new WeekDayFestival(Name, Month, WeekType, WeekDay, Year)));
    return m_AllFestival.back();
}

// Add函数
// 向节日列表中添加节日
// 传入节日名称，月份字符串，星期类型字符串，星期字符串，年份
// 返回节日指针
FesPtr WeekDayFestival::Add(const string& Name, const string& Month, const string& WeekType, const string& WeekDay, const unsigned int Year) {
    // 检查节日是否已存在,若存在则抛出异常
    for (auto festival : m_AllFestival)
    {
        if (festival->name == Name)
        {
            throw invalid_argument("Festival already exists!");
        }
    }
    m_AllFestival.push_back(FesPtr(new WeekDayFestival(Name, Month, WeekType, WeekDay, Year)));
    return m_AllFestival.back();
}

// Del函数
// 从节日列表中删除节日
// 传入节日名称
// 返回void
void WeekDayFestival::Del(const string& Name)
{
    // 根据节日名称查找节日，若找到则删除，否则抛出异常
    for (auto festival = m_AllFestival.begin(); festival != m_AllFestival.end(); ++festival)
    {
        if ((*festival)->name == Name)
        {
            (*festival).reset();
            m_AllFestival.erase(festival);
            return;
        }
    }
    throw invalid_argument("Festival does not exist!");
}

// ResetName函数
// 重设节日名称
// 传入新的节日名称
// 返回void
void WeekDayFestival::ResetName(const string& NewName)
{
    Reset(NewName);
    return;
}

// ResetName函数
// 重设节日名称
// 传入节日名称，新的节日名称
// 返回void
void WeekDayFestival::ResetName(const string& Name, const string& NewName)
{
    // 根据节日名称查找节日，若找到则重设名称，否则抛出异常
    for (auto festival : m_AllFestival)
    {
        if (festival->name == Name)
        {
            festival->Reset(NewName);
            return;
        }
    }
    throw invalid_argument("Festival does not exist!");
}

// ResetDate函数
// 重设节日日期
// 传入月份对象，星期类型，星期对象
// 返回void
void WeekDayFestival::ResetDate(const Month& NewMonth, const WeekType& NewWeekType, const WeekDay& NewWeekDay)
{
    m_Month = NewMonth;
    m_WeekType = NewWeekType;
    m_WeekDay = NewWeekDay;
    return;
}

// ResetDate函数
// 重设节日日期
// 传入节日名称，月份对象，星期类型，星期对象
// 返回void
void WeekDayFestival::ResetDate(const string& Name, const Month& NewMonth, const WeekType& NewWeekType, const WeekDay& NewWeekDay)
{
    // 根据节日名称查找节日，若找到则重设日期，否则抛出异常
    for (auto festival : m_AllFestival)
    {
        if (festival->name == Name)
        {
            static_cast<WeekDayFestival*> (festival.get())->ResetDate(NewMonth, NewWeekType, NewWeekDay);
            return;
        }
    }
    throw invalid_argument("Festival does not exist!");
}

// ResetDate函数
// 重设节日日期
// 传入月份序数，星期类型序数，星期序数
// 返回void
void WeekDayFestival::ResetDate(unsigned int NewMonth, unsigned int NewWeekType, unsigned int NewWeekDay)
{
    m_WeekType = IntToWeekType(NewWeekType);
    m_Month = NewMonth;
    m_WeekDay = NewWeekDay;
    return;
}

// ResetDate函数
// 重设节日日期
// 传入节日名称，月份序数，星期类型序数，星期序数
// 返回void
void WeekDayFestival::ResetDate(const string& Name, unsigned int NewMonth, unsigned int NewWeekType, unsigned int NewWeekDay)
{
    // 根据节日名称查找节日，若找到则重设日期，否则抛出异常
    for (auto festival : m_AllFestival)
    {
        if (festival->name == Name)
        {
            static_cast<WeekDayFestival*> (festival.get())->ResetDate(NewMonth, NewWeekType, NewWeekDay);
            return;
        }
    }
    throw invalid_argument("Festival does not exist!");
}

// ResetMonth函数
// 重设节日月份
// 传入月份值
// 返回void
void WeekDayFestival::ResetMonth(const unsigned int NewMonth)
{
    m_Month = NewMonth;
    return;
}

// ResetMonth函数
// 重设节日月份
// 传入节日名称，月份值
// 返回void
void WeekDayFestival::ResetMonth(const string& Name, const unsigned int NewMonth)
{
    // 根据节日名称查找节日，若找到则重设月份，否则抛出异常
    for (auto festival : m_AllFestival)
    {
        if (festival->name == Name)
        {
            static_cast<WeekDayFestival*> (festival.get())->ResetMonth(NewMonth);
            return;
        }
    }
    throw invalid_argument("Festival does not exist!");
}

// ResetWeekType函数
// 重设节日星期类型
// 传入星期类型值
// 返回void
void WeekDayFestival::ResetWeekType(const unsigned int NewWeekType)
{
    m_WeekType = IntToWeekType(NewWeekType);
    return;
}

// ResetWeekType函数
// 重设节日星期类型
// 传入节日名称，星期类型值
// 返回void
void WeekDayFestival::ResetWeekType(const string& Name, const unsigned int NewWeekType)
{
    // 根据节日名称查找节日，若找到则重设星期类型，否则抛出异常
    for (auto festival : m_AllFestival)
    {
        if (festival->name == Name)
        {
            static_cast<WeekDayFestival*> (festival.get())->ResetWeekType(NewWeekType);
            return;
        }
    }
    throw invalid_argument("Festival does not exist!");
}

// ResetWeekDay函数
// 重设节日星期
// 传入星期值
// 返回void
void WeekDayFestival::ResetWeekDay(const unsigned int NewWeekDay)
{
    m_WeekDay = NewWeekDay;
    return;
}

// ResetWeekDay函数
// 重设节日星期
// 传入节日名称，星期值
// 返回void
void WeekDayFestival::ResetWeekDay(const string& Name, const unsigned int NewWeekDay)
{
    // 根据节日名称查找节日，若找到则重设星期，否则抛出异常
    for (auto festival : m_AllFestival)
    {
        if (festival->name == Name)
        {
            static_cast<WeekDayFestival*> (festival.get())->ResetWeekDay(NewWeekDay);
            return;
        }
    }
    throw invalid_argument("Festival does not exist!");
}

// ResetStartYear函数
// 重设节日起始年份
// 传入年份值
// 返回void
void WeekDayFestival::ResetStartYear(const unsigned int NewStartYear)
{
    m_StartYear = NewStartYear;
    return;
}

// ResetStartYear函数
// 重设节日起始年份
// 传入节日名称，年份值
// 返回void
void WeekDayFestival::ResetStartYear(const string& Name, const unsigned int NewStartYear)
{
    // 根据节日名称查找节日，若找到则重设起始年份，否则抛出异常
    for (auto festival : m_AllFestival)
    {
        if (festival->name == Name)
        {
            static_cast<WeekDayFestival*> (festival.get())->ResetStartYear(NewStartYear);
            return;
        }
    }
    throw invalid_argument("Festival does not exist!");
}

// SearchName函数
// 按名称查找节日，得到节日指针
// 传入节日名称
// 返回节日指针
FesPtr WeekDayFestival::SearchName(const string& Name)
{
    // 根据节日名称查找节日，若找到则返回节日指针，否则抛出异常
    for (auto festival : m_AllFestival)
    {
        if (festival->name == Name)
        {
            return festival;
        }
    }
    throw invalid_argument("Festival does not exist!");
}

// SearchDay函数
// 查找某一天的所有节日，得到节日指针列表
// 传入月份，星期类型，星期，年份
// 返回节日指针列表m_SearchList的拷贝
vector<FesPtr> WeekDayFestival::SearchDay(const Month& Month, const WeekType& WeekType, const WeekDay& WeekDay, const unsigned int Year)
{
    Festival::ClearSearchList(m_SearchList);
    // 起始年份需要小于等于查找年份，月份、星期类型、星期需要相等
    for (auto festival : m_AllFestival)
    {
        if (static_cast<WeekDayFestival*> (festival.get())->m_Month == Month 
            && static_cast<WeekDayFestival*> (festival.get())->m_WeekType == WeekType 
            && static_cast<WeekDayFestival*> (festival.get())->m_WeekDay == WeekDay 
            && static_cast<WeekDayFestival*> (festival.get())->m_StartYear <= Year)
        {
            m_SearchList.push_back(festival);
        }
    }
    // 若查找结果为空，则抛出异常
    if (m_SearchList.empty())
    {
        throw invalid_argument("Festival does not exist!");
    }
    return m_SearchList;
}

// SearchDay函数
// 查找某一天的所有节日，得到节日指针列表
// 传入月份，星期类型值，星期值，年份
// 返回节日指针列表m_SearchList的拷贝
vector<FesPtr> WeekDayFestival::SearchDay(unsigned int aMonth, unsigned int WeekType, unsigned int aWeekDay, const unsigned int Year)
{
    return SearchDay(Month(aMonth), IntToWeekType(WeekType), WeekDay(aWeekDay), Year);
}

// SearchMonth函数
// 查找某一月的所有节日，得到节日指针列表
// 传入月份，年份
// 返回节日指针列表m_SearchList的拷贝
vector<FesPtr> WeekDayFestival::SearchMonth(const Month& Month, const unsigned int Year)
{
    Festival::ClearSearchList(m_SearchList);
    // 起始年份需要小于等于查找年份，月份需要相等
    for (auto festival : m_AllFestival)
    {
        if (static_cast<WeekDayFestival*> (festival.get())->m_Month == Month 
            && static_cast<WeekDayFestival*> (festival.get())->m_StartYear <= Year)
        {
            m_SearchList.push_back(festival);
        }
    }
    // 若查找结果为空，则抛出异常
    if (m_SearchList.empty())
    {
        throw invalid_argument("Festival does not exist!");
    }
    return m_SearchList;
}

// SearchMonth函数
// 查找某一月的所有节日，得到节日指针列表
// 传入月份值，年份
// 返回节日指针列表m_SearchList的拷贝
vector<FesPtr> WeekDayFestival::SearchMonth(unsigned int aMonth, const unsigned int Year)
{
    return SearchMonth(Month(aMonth), Year);
}

// SearchWeek函数
// 查找某一周的所有节日，得到节日指针列表
// 传入月份，星期类型，年份
// 返回节日指针列表m_SearchList的拷贝
vector<FesPtr> WeekDayFestival::SearchWeek(const Month& Month, const WeekType& WeekType, const unsigned int Year)
{
    Festival::ClearSearchList(m_SearchList);
    // 起始年份需要小于等于查找年份，月份、星期类型需要相等
    for (auto festival : m_AllFestival)
    {
        if (static_cast<WeekDayFestival*> (festival.get())->m_Month == Month 
            && static_cast<WeekDayFestival*> (festival.get())->m_WeekType == WeekType 
            && static_cast<WeekDayFestival*> (festival.get())->m_StartYear <= Year)
        {
            m_SearchList.push_back(festival);
        }
    }
    // 若查找结果为空，则抛出异常
    if (m_SearchList.empty())
    {
        throw invalid_argument("Festival does not exist!");
    }
    return m_SearchList;
}

// SearchWeek函数
// 查找某一周的所有节日，得到节日指针列表
// 传入月份值，星期类型值，年份
// 返回节日指针列表m_SearchList的拷贝
vector<FesPtr> WeekDayFestival::SearchWeek(unsigned int aMonth, unsigned int WeekType, const unsigned int Year)
{
    return SearchWeek(Month(aMonth), IntToWeekType(WeekType), Year);
}

// Search函数
// 查找某一时间段的所有节日，得到节日指针列表
// 传入起始日期，终止日期
// 返回节日指针列表m_SearchList的拷贝
vector<FesPtr> WeekDayFestival::Search(const Date& Date1, const Date& Date2)
{
    // 用户搜索的两个日期差距不能超过一年，否则没有意义
    if (Date::IsFullYear(Date1, Date2))
    {
        throw invalid_argument("Shouldn't stretch over a full year!");
    }
    // 清空节日指针列表
    Festival::ClearSearchList(m_SearchList);
    // 分两种情况讨论，利用AddList将节日指针加入m_SearchList
    // 1. 起始日期和终止日期在同一年
    if (Date1.year == Date2.year)
    {
        for (auto& festival : m_AllFestival)
        {
            // 确保最后加入m_SearchList的节日是DateFestival类型的，date表示的日期在Date1和Date2之间
            Date temp = WeekDayToDate(static_cast<WeekDayFestival*> (festival.get())->m_Month, 
                static_cast<WeekDayFestival*> (festival.get())->m_WeekType, 
                static_cast<WeekDayFestival*> (festival.get())->m_WeekDay, Date1.year);
            unsigned int ayear = static_cast<WeekDayFestival*> (festival.get())->m_StartYear;
            if (ayear <= Date1.year && temp >= Date1 && temp <= Date2)
            {
                DateFestival::ListAdd(festival->name, temp);
            }
        }
    }
    // 2. 起始日期和终止日期不在同一年
    else
    {
        for (auto& festival : m_AllFestival)
        {
            // 确保最后加入m_SearchList的节日是DateFestival类型的，date表示的日期在Date1和Date2之间
            Date temp = WeekDayToDate(static_cast<WeekDayFestival*> (festival.get())->m_Month, 
                static_cast<WeekDayFestival*> (festival.get())->m_WeekType, 
                static_cast<WeekDayFestival*> (festival.get())->m_WeekDay, Date1.year);
            unsigned int ayear = static_cast<WeekDayFestival*> (festival.get())->m_StartYear;
            if (ayear <= Date1.year && temp >= Date1)
            {
                DateFestival::ListAdd(festival->name, temp);
            }
            temp = WeekDayToDate(static_cast<WeekDayFestival*> (festival.get())->m_Month, 
                static_cast<WeekDayFestival*> (festival.get())->m_WeekType, 
                static_cast<WeekDayFestival*> (festival.get())->m_WeekDay, Date2.year);
            if (ayear <= Date2.year && temp <= Date2)
            {
                DateFestival::ListAdd(festival->name, temp);
            }
        }
    }
    // 若查找结果为空，则抛出异常
    if (m_SearchList.empty())
    {
        throw invalid_argument("Festival does not exist!");
    } 
    return m_SearchList;
}

// Search函数
// 查找某一时间段的所有节日，得到节日指针列表
// 传入起始年份，起始月份，起始日期，终止年份，终止月份，终止日期
// 返回节日指针列表m_SearchList的拷贝
vector<FesPtr> WeekDayFestival::Search(const unsigned int Year1, const unsigned int Month1, const unsigned int Day1, 
        const unsigned int Year2,const unsigned int Month2, const unsigned int Day2)
{
    auto result = Search(Date(Year1, Month1, Day1), Date(Year2, Month2, Day2));
    return result;
}

// 重载==运算符
// 判断两个WeekDayFestival对象的日期是否相等
// 传入一个WeekDayFestival对象
// 返回bool值
bool WeekDayFestival::operator==(const WeekDayFestival& Source) const
{
    return m_Month == Source.m_Month && m_WeekType == Source.m_WeekType 
        && m_WeekDay == Source.m_WeekDay;
}

// operator!=函数
// 判断两个WeekDayFestival对象的日期是否不相等
// 传入一个WeekDayFestival对象
// 返回bool值
bool WeekDayFestival::operator!=(const WeekDayFestival& Source) const
{
    return !(*this == Source);
}

// SortByNameUp函数
// 按照节日名称升序排序
// 传入起始日期，终止日期
// 返回节日指针列表
vector<FesPtr> WeekDayFestival::SortByNameUp(const Date& Date1, const Date& Date2)
{
    // 调用Search函数得到节日指针列表
    vector<FesPtr> result = Search(Date1, Date2);
    // 若查找结果为空，则抛出异常
    if (result.empty())
    {
        throw invalid_argument("Festival does not exist!");
    }
    // 利用lambda表达式对搜索列表进行排序
    sort(result.begin(), result.end(), [](const FesPtr& a, const FesPtr& b) {return a->name < b->name; });
    return result;
}

// SortByNameUp函数
// 按照节日名称升序排序
// 传入起始年份，起始月份，起始日期，终止年份，终止月份，终止日期
// 返回节日指针列表
vector<FesPtr> WeekDayFestival::SortByNameUp(const unsigned int Year1, const unsigned int Month1, const unsigned int Day1, 
        const unsigned int Year2,const unsigned int Month2, const unsigned int Day2)
{
    return SortByNameUp(Date(Year1, Month1, Day1), Date(Year2, Month2, Day2));
}        

// SortByNameDown函数
// 按照节日名称降序排序
// 传入起始日期，终止日期
// 返回节日指针列表
vector<FesPtr> WeekDayFestival::SortByNameDown(const Date& Date1, const Date& Date2)
{
    // 调用Search函数得到节日指针列表
    // 若查找结果为空，则抛出异常
    vector<FesPtr> result = Search(Date1, Date2);
    if (result.empty())
    {
        throw invalid_argument("Festival does not exist!");
    }
    // 利用lambda表达式对搜索列表进行排序
    sort(result.begin(), result.end(), [](const FesPtr& a, const FesPtr& b) {return a->name > b->name; });
    return result;
}

// SortByNameDown函数
// 按照节日名称降序排序
// 传入起始年份，起始月份，起始日期，终止年份，终止月份，终止日期
// 返回节日指针列表
vector<FesPtr> WeekDayFestival::SortByNameDown(const unsigned int Year1, const unsigned int Month1, const unsigned int Day1, 
        const unsigned int Year2,const unsigned int Month2, const unsigned int Day2)
{
    return SortByNameDown(Date(Year1, Month1, Day1), Date(Year2, Month2, Day2));
}

// SortByDateUp函数
// 按照日期升序排序
// 传入起始日期，终止日期
// 返回节日指针列表
vector<FesPtr> WeekDayFestival::SortByDateUp(const Date& Date1, const Date& Date2)
{
    // 调用Search函数得到节日指针列表
    // 若查找结果为空，则抛出异常
    vector<FesPtr> result = Search(Date1, Date2);
    if (result.empty())
    {
        throw invalid_argument("Festival does not exist!");
    }
    // 利用lambda表达式对搜索列表进行排序
    sort(result.begin(), result.end(), [](const FesPtr& Source1, const FesPtr& Source2)
    {
        return static_cast<DateFestival*> (Source1.get())->date < static_cast<DateFestival*> (Source2.get())->date;
    });
    return result;
}

// SortByDateUp函数
// 按照日期升序排序
// 传入起始年份，起始月份，起始日期，终止年份，终止月份，终止日期
// 返回节日指针列表
vector<FesPtr> WeekDayFestival::SortByDateUp(const unsigned int Year1, const unsigned int Month1, const unsigned int Day1, 
        const unsigned int Year2,const unsigned int Month2, const unsigned int Day2)
{
    return SortByDateUp(Date(Year1, Month1, Day1), Date(Year2, Month2, Day2));
}

// SortByDateDown函数
// 按照日期降序排序
// 传入起始日期，终止日期
// 返回节日指针列表
vector<FesPtr> WeekDayFestival::SortByDateDown(const Date& Date1, const Date& Date2)
{
    // 调用Search函数得到节日指针列表
    // 若查找结果为空，则抛出异常
    vector<FesPtr> result = Search(Date1, Date2);
    if (result.empty())
    {
        throw invalid_argument("Festival does not exist!");
    }
    // 利用lambda表达式对搜索列表进行排序   
    sort(result.begin(), result.end(), [](const FesPtr& Source1, const FesPtr& Source2)
    {
        return static_cast<DateFestival*> (Source1.get())->date > static_cast<DateFestival*> (Source2.get())->date;
    });
    return result;
}

// SortByDateDown函数
// 按照日期降序排序
// 传入起始年份，起始月份，起始日期，终止年份，终止月份，终止日期
// 返回节日指针列表
vector<FesPtr> WeekDayFestival::SortByDateDown(const unsigned int Year1, const unsigned int Month1, const unsigned int Day1, 
        const unsigned int Year2,const unsigned int Month2, const unsigned int Day2)
{
    return SortByDateDown(Date(Year1, Month1, Day1), Date(Year2, Month2, Day2));
}

// ToString函数
// 返回节日信息的字符串
string WeekDayFestival::ToString() const
{
    // 按照以下格式：
    // 节日名称：第几个星期几在几月
    return name + ": the " + WeekTypeStr[static_cast<int> (m_WeekType)] + " " + m_WeekDay.weekday + " of " + m_Month.month;
}

// ToString函数
// 传入节日对象
// 返回节日信息的字符串
string WeekDayFestival::ToString(const WeekDayFestival& Source)
{
    return Source.ToString();
}

// ToString函数、
// 传入节日名称，月份，星期类型，星期
// 返回节日信息的字符串
string WeekDayFestival::ToString(const string& Name, unsigned int Month, unsigned int WeekType, unsigned int WeekDay)
{
    return ToString(WeekDayFestival(Name, Month, WeekType, WeekDay));
}

// operator<<函数
// 重载输出运算符
// 传入输出流对象，节日对象
// 返回输出流对象
ostream& operator<<(ostream& Out, const WeekDayFestival& Source)
{
    Out << Source.ToString();
    return Out;
}

// ReadFromFile函数
// 从文件中读取节日信息
// 传入文件名
// 返回void
void WeekDayFestival::ReadFromFile(const string& FileName)
{
    ifstream fin(FileName);
    if (!fin.is_open())
    {
        throw invalid_argument("File does not exist!");
    }
    string input;
    // 每次读取一行
    while (getline(fin, input))
    {
        stringstream ss(input);
        string name;
        string temp;
        string month;
        string weektype;
        string weekday;
        unsigned int year;
        // 遇到：，读取节日名称
        getline(ss, name, ':');
        getline(ss, temp, 'e');
        ss >> weektype >> weekday >> temp >> month >> year;
        if (ss.fail())
        {
            throw invalid_argument("Invalid input!");
        }
        Add(name, month, weektype, weekday, year);
    }
    fin.close();
}

// WriteToFile函数
// 将节日信息写入文件
// 传入文件名
// 返回void
void WeekDayFestival::WriteToFile(const string& FileName)
{
    ofstream fout(FileName);
    if (!fout.is_open())
    {
        throw invalid_argument("File does not exist!");
    }
    // 按照以下格式写入文件：
    // 节日名称：第几个星期几在几月
    // 便于从文件读入
    for (const auto& festival : m_AllFestival)
    {
        fout << festival->name << ": the " 
            << WeekTypeStr[static_cast<int> (static_cast<WeekDayFestival*> (festival.get())->m_WeekType)] 
            << " " << static_cast<WeekDayFestival*> (festival.get())->m_WeekDay.weekday 
            << " of " << static_cast<WeekDayFestival*> (festival.get())->m_Month.month
            << " " << static_cast<WeekDayFestival*> (festival.get())->m_StartYear << endl;
    }
    fout.close();
}

// WeekDayToDate函数
// 换算某年的星期几到底在哪一天
// 传入月份，星期类型，星期，年份
// 返回日期
Date WeekDayFestival::WeekDayToDate(unsigned int Month, unsigned int WeekType, unsigned int WeekDay, const unsigned int Year)
{
    // 分两种情况，一种是从月初开始找，一种是从月末开始找
    if (WeekType == 0)
    {
        for (Date i = Date(Year, Month, Date::GetMaxDay(Year, Month)); i >= Date(Year, Month, 1); --i)
        {
            if (i.ToWeekDay() == WeekDay)
            {
                return i;
            }
        }
    }
    else
    {
        for (Date i = Date(Year, Month, 1); i <= Date(Year, Month, Date::GetMaxDay(Year, Month)); ++i)
        {
            if (i.ToWeekDay() == WeekDay)
            {
                --WeekType;
                if (WeekType == 0)
                {
                    return i;
                }
            }
        }
    }
    // 如果找不到，抛出异常
    throw invalid_argument("Invalid input!");
}

// WeekDayToDate函数
// 重载WeekDayToDate函数
// 传入月份，星期类型，星期，年份
// 返回日期
Date WeekDayFestival::WeekDayToDate(const Month& Month, const WeekType& WeekType, const WeekDay& WeekDay, const unsigned int Year)
{
    return WeekDayFestival::WeekDayToDate(Month.value, static_cast<int> (WeekType), WeekDay.value, Year);
}

// IntToWeekType函数
// 将数字转换为星期类型,建立映射，0为最后一个，1为第一个，以此类推
// 传入数字
// 返回星期类型
WeekDayFestival::WeekType WeekDayFestival::IntToWeekType(const unsigned int Int)
{
    switch (Int) {
        case 1:
            return WeekType::First;
        case 2:
            return WeekType::Second;
        case 3:
            return WeekType::Third;
        case 4:
            return WeekType::Fourth;
        case 0:
            return WeekType::Last;
        default:
            throw invalid_argument("Invalid WeekType!");
    }
}