//
// Date.cpp
// Implementation of the Date class.
// Created by 洪宸宇 on 14/7/2023
// 添加注释 29/7/2023
//

#include "Date.hpp"
#include <string>
#include <iostream>
#include <stdexcept>
#include <ctime>

using std::string;
using std::ostream;
using std::istream;
using std::invalid_argument;
using std::to_string;

unsigned int Date::Max_Year = 9999;
unsigned int Date::Min_Year = 1900;
unsigned int Date::Max_Month = 12;
unsigned int Date::Min_Month = 1;
unsigned int Date::Min_Day = 1;

// 每月天数，第一维为平年，第二维为闰年
unsigned int Date::Month_Day[2][13] = {
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

// 所有日期，数值与字符串的映射
vector<string> Date::m_AllDay = { "None", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th",
                                          "9th", "10th", "11th", "12th", "13th", "14th", "15th", "16th",
                                          "17th", "18th", "19th", "20th", "21st", "22nd", "23rd", "24th",
                                          "25th", "26th", "27th", "28th", "29th", "30th", "31st"};

Date::Format Date::DefaultFormat = Date::Format::backslash;

// 构造函数
// 传入年月日值，构造日期
Date::Date(unsigned int aYear, unsigned int aMonth, unsigned int aDay) : m_Month(aMonth)
{
    SetDate(aYear, aMonth, aDay);
}

// 构造函数
// 传入年日值，月份对象，构造日期
Date::Date(unsigned int aYear, const Month& aMonth, unsigned int aDay) : m_Month(aMonth)
{
    SetDate(aYear, aMonth.value, aDay);
}

// 拷贝构造函数
Date::Date(const Date& date) : m_Month(date.m_Month)
{
    m_Year = date.year;
    m_Month = date.month;
    m_Day = date.day;
}

// 重载赋值运算符
Date& Date::operator=(const Date& date)
{
    m_Year = date.year;
    m_Month = date.month;
    m_Day = date.day;
    return *this;
}

// SetDate函数
// 传入年月日值，设置日期
// 无返回值
void Date::SetDate(unsigned int aYear, unsigned int aMonth, unsigned int aDay)
{
    // 检查年月日值是否合法,不合法则抛出异常
    if (aYear < Min_Year || aYear > Max_Year) {
        throw invalid_argument("Invalid year!");
    }
    if (aMonth < Min_Month || aMonth > Max_Month) {
        throw invalid_argument("Invalid month!");
    }
    if (aDay < Min_Day || aDay > Month_Day[IsLeapYear(aYear)][aMonth]) {
        throw invalid_argument("Invalid day!");
    }
    m_Year = aYear;
    m_Month = Month(aMonth);
    m_Day = aDay;
}

// SetYear函数
// 传入年值，设置年份
// 无返回值
void Date::SetYear(unsigned int aYear)
{
    // 检查年值是否合法,不合法则抛出异常
    if (aYear < Min_Year || aYear > Max_Year) {
        throw invalid_argument("Invalid year!");
    }
    m_Year = aYear;
}

// SetMonth函数
// 传入月值，设置月份
// 无返回值
void Date::SetMonth(unsigned int aMonth)
{
    m_Month = Month(aMonth);
}

// SetMonth函数
// 传入月份单词，设置月份
// 无返回值
void Date::SetMonth(const char* aMonth)
{
    m_Month = Month(aMonth);
}

// SetMonth函数
// 传入月份单词，设置月份
// 无返回值
void Date::SetMonth(const string& aMonth)
{
    m_Month = Month(aMonth);
}

// SetMonth函数
// 传入月份对象，设置月份
// 无返回值
void Date::SetMonth(const Month aMonth)
{
    m_Month = aMonth;
}

// SetDay函数
// 传入日值，设置日
// 无返回值
void Date::SetDay(unsigned int aDay)
{
    // 检查日值是否合法,不合法则抛出异常
    if (aDay < Min_Day || aDay > Month_Day[IsLeapYear(m_Year)][m_Month.value]) {
        throw invalid_argument("Invalid day!");
    }
    m_Day = aDay;
}

// 重载==运算符
// 传入日期对象，比较两个日期是否相等
bool Date::operator==(const Date& date) const
{
    return m_Year == date.year && m_Month == date.month && m_Day == date.day;
}

// 重载!=运算符
// 传入日期对象，比较两个日期是否不等
bool Date::operator!=(const Date& date) const
{
    return !(*this == date);
}

// 重载<运算符
// 传入日期对象，比较两个日期的大小
bool Date::operator<(const Date& date) const
{
    return this->CalculateDays() < date.CalculateDays();
}

// 重载>运算符
// 传入日期对象，比较两个日期的大小
bool Date::operator>(const Date& date) const
{
    return this->CalculateDays() > date.CalculateDays();
}

// 重载<=运算符
// 传入日期对象，比较两个日期的大小
bool Date::operator<=(const Date& date) const
{
    return !(*this > date);
}

// 重载>=运算符
// 传入日期对象，比较两个日期的大小
bool Date::operator>=(const Date& date) const
{
    return !(*this < date);
}

// 重载+运算符
// 传入天数
// 返回增加指定天数后的日期
Date& Date::operator+(unsigned int days)
{
    for (unsigned int i = 0; i < days; ++i) {
        ++(*this);
    }
    return *this;
}

// 重载-运算符
// 传入天数
// 返回减少指定天数后的日期
Date& Date::operator-(unsigned int days)
{
    for (unsigned int i = 0; i < days; ++i) {
        --(*this);
    }
    return *this;
}

// 重载+=运算符
// 传入天数
// 返回增加指定天数后的日期
Date& Date::operator+=(unsigned int days)
{
    return *this + days;
}

// 重载-=运算符
// 传入天数
// 返回减少指定天数后的日期
Date& Date::operator-=(unsigned int days)
{
    return *this - days;
}

// 重载前置自增运算符
// 返回增加一天后的日期
Date& Date::operator++()
{
    if (m_Day == Month_Day[IsLeapYear(m_Year)][m_Month.value]) {
        m_Day = Min_Day;
        ++m_Month;
        if (m_Month == "January") {
            ++m_Year;
        }
    } else {
        ++m_Day;
    }
    return *this;
}

// 重载后置自增运算符
// 返回增加一天前的日期
Date Date::operator++(int)
{
    Date temp(*this);
    ++(*this);
    return temp;
}

// 重载前置自减运算符
// 返回减少一天后的日期
Date& Date::operator--()
{
    if (m_Day == Min_Day) {
        --m_Month;
        if (m_Month == "December") {
            --m_Year;
        }
        m_Day = Month_Day[IsLeapYear(m_Year)][m_Month.value];
    } else {
        --m_Day;
    }
    return *this;
}

// 重载后置自减运算符
// 返回减少一天前的日期
Date Date::operator--(int)
{
    Date temp(*this);
    --(*this);
    return temp;
}

// 重载-运算符
// 传入日期对象，返回两个日期相差的天数
long long Date::operator-(const Date& date) const
{
    return this->CalculateDays() - date.CalculateDays();
}

// CalculateDays函数
// 返回从1900/1/1到当前日期的天数
long long Date::CalculateDays() const
{
    unsigned int days = 0;
    for (unsigned int i = Min_Year; i < m_Year; ++i) {
        days += 365 + IsLeapYear(i);
    }
    for (unsigned int i = Min_Month; i < m_Month.value; ++i) {
        days += Month_Day[IsLeapYear(m_Year)][i];
    }
    days += m_Day;
    return days;
}

// CalculateDays函数
// 传入日期对象，返回从1900/1/1到指定日期的天数
long long Date::CalculateDays(const Date& date1)
{
    return date1.CalculateDays();
}

// CalculateDays函数
// 传入年月日，返回从1900/1/1到指定日期的天数
long long Date::CalculateDays(unsigned int aYear, unsigned int aMonth, unsigned int aDay)
{
    return Date(aYear, aMonth, aDay).CalculateDays();
}

// IsLeapYear函数
// 判断当前日期所在年份是否为闰年
// 返回bool值
bool Date::IsLeapYear() const
{
    return IsLeapYear(m_Year);
}

// IsLeapYear函数
// 传入年份，判断指定年份是否为闰年
// 返回bool值
bool Date::IsLeapYear(unsigned int aYear)
{
    return (aYear % 4 == 0 && aYear % 100 != 0) || aYear % 400 == 0;
}

// IsValid函数
// 判断当前日期是否合法
// 返回bool值
bool Date::IsValid() const
{
    return IsValid(m_Year, m_Month.value, m_Day);
}

// IsValid函数
// 传入年月日，判断指定日期是否合法
// 返回bool值
bool Date::IsValid(unsigned int aYear, unsigned int aMonth, unsigned int aDay)
{
    return (aYear >= Min_Year && aYear <= Max_Year 
    && aMonth >= Min_Month && aMonth <= Max_Month 
    && aDay >= Min_Day && aDay <= Month_Day[IsLeapYear(aYear)][aMonth]);
}

// GetMaxDay函数
// 返回当前日期所在月份的最大天数
unsigned int Date::GetMaxDay() const
{
    return Month_Day[IsLeapYear(m_Year)][m_Month.value];
}

// GetMaxDay函数
// 传入年月日
// 返回指定日期所在月份的最大天数
unsigned int Date::GetMaxDay(unsigned int aYear, unsigned int aMonth)
{
    return Month_Day[IsLeapYear(aYear)][aMonth];
}

// GetMaxDay函数
// 传入日期对象
// 返回指定日期所在月份的最大天数
unsigned int Date::GetMaxDay(const Date& date)
{
    return date.GetMaxDay();
}

// GetMaxDay函数
// 传入月份对象和年份
// 返回指定日期所在月份的最大天数
unsigned int Date::GetMaxDay(unsigned int aYear, const Month& aMonth)
{
    return Month_Day[IsLeapYear(aYear)][aMonth.value];
}

// IsFullYear函数
// 判断当前日期与指定日期是否相差一年
// 传入日期值
// 返回bool值
bool Date::IsFullYear(const Date& date) const
{
    if (m_Month == "February" && m_Day == 29) {
        return date >= Date(m_Year + 1, m_Month, m_Day - 1);
    }
    else {
        return date >= Date(m_Year + 1, m_Month, m_Day);
    }
}

// IsFullYear函数
// 判断两个日期是否相差一年
// 传入日期年月日值
// 返回bool值
bool Date::IsFullYear(unsigned int aYear, unsigned int aMonth, unsigned int aDay) const
{
    return IsFullYear(Date(aYear, aMonth, aDay));
}

// IsFullYear函数
// 判断两个日期是否相差一年
// 传入两个日期对象
// 返回bool值
bool Date::IsFullYear(const Date& date1, const Date& date2)
{
    return date1.IsFullYear(date2);
}

// IsFullYear函数
// 判断两个日期是否相差一年
// 传入两个日期年月日值
// 返回bool值
bool Date::IsFullYear(unsigned int aYear1, unsigned int aMonth1, unsigned int aDay1, 
        unsigned int aYear2, unsigned int aMonth2, unsigned int aDay2)
{
    return Date(aYear1, aMonth1, aDay1).IsFullYear(Date(aYear2, aMonth2, aDay2));
}

// ToString函数
// 传入日期对象和格式，分别为斜杠“/”、连字符“-”、字符
// 返回当前日期的字符串形式
string Date::ToString(const Date& aDate, const enum Format& aformat)
{
    string str;
    // 根据格式选择输出形式
    switch (aformat) {
        case Format::backslash:
            str = to_string(aDate.year) + "/" + to_string(aDate.month.value) + "/" + to_string(aDate.day);
            break;
        case Format::hyphen:
            str = to_string(aDate.year) + "-" + to_string(aDate.month.value) + "-" + to_string(aDate.day);
            break;
        case Format::character:
            str = aDate.month.month + " " + Date::m_AllDay[aDate.day] + ", " + to_string(aDate.year);
            break;
        default:
            throw invalid_argument("Invalid format!");
            break;
    }
    return str;
}

// ToString函数
// 传入年月日和格式，分别为斜杠“/”、连字符“-”、字符
// 返回指定日期的字符串形式
string Date::ToString(unsigned int aYear, unsigned int aMonth, unsigned int aDay, const enum Format& aformat)
{
    return ToString(Date(aYear, aMonth, aDay), aformat);
}

// ToString函数
// 传入格式，分别为斜杠“/”、连字符“-”、字符
// 返回当前日期的字符串形式
string Date::ToString(const enum Format& aformat) const
{
    return ToString(*this, aformat);
}

// 重载<<运算符
// 传入日期对象
// 返回输出流对象
ostream& operator<<(ostream& os, const Date& date)
{
    os << date.ToString(Date::DefaultFormat);
    return os;
}

// 重载<<运算符,更改格式
// 传入格式
// 返回输出流对象,并将默认格式设为传入格式
ostream& operator<<(ostream& os, const enum Date::Format& aformat)
{
    Date::DefaultFormat = aformat;
    return os;
}

// 重载>>运算符
// 传入输入流对象和日期对象
// 返回输入流对象，并将输入流中的值赋给日期对象
istream& operator>>(istream& is, Date& date)
{
    char Temp;
    int year, month, day;
    is >> year >> Temp >> month >> Temp >> day;
    date = Date(year, month, day);
    return is;
}

// Now函数
// 返回当前日期
Date Date::Now()
{
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return Date(ltm->tm_year + 1900, ltm->tm_mon + 1, ltm->tm_mday);
}

// ToWeekDay函数
// 返回当前日期的星期数
unsigned int Date::ToWeekDay() const
{
    return ToWeekDay(m_Year, m_Month.value, m_Day);
}

// ToWeekDay函数
// 传入年月日
// 返回指定日期的星期数
unsigned int Date::ToWeekDay(unsigned int aYear, unsigned int aMonth, unsigned int aDay)
{
    // 判断日期是否合法,不合法则抛出异常
    if (!IsValid(aYear, aMonth, aDay)) {
        throw invalid_argument("Invalid date!");
    }
    unsigned int WeekDay = (CalculateDays(aYear, aMonth, aDay))% 7;
    if (WeekDay == 0) {
        WeekDay = 7;
    }
    return  WeekDay;
}

// ToWeekDay函数
// 传入日期对象
// 返回指定日期的星期数
unsigned int Date::ToWeekDay(const Date& date)
{
    return date.ToWeekDay();
}