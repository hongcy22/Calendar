//
// Date.hpp
// Declaration of the Date class.
// Created by 洪宸宇 on 14/7/2023
// 添加注释 29/7/2023
//

#ifndef Date_hpp
#define Date_hpp

#include <string>
#include <iostream>
#include <vector>
#include "Month.hpp"

using std::string;
using std::ostream;
using std::istream;
using std::vector;

// Date类，用于表示日期
// 日期范围：1900/1/1 ~ 9999/12/31
// 私有成员变量：
//     m_Year：年份
//     m_Month：月份
//     m_Day：日期
// 静态私有成员变量：
//     Max_Year：最大年份
//     Min_Year：最小年份
//     Max_Month：最大月份
//     Min_Month：最小月份
//     Min_Day：最小日期
//     Month_Day：每月天数
//     m_AllDay：所有日期，数值与字符串的映射
// 公有成员函数：
//     构造函数，重载构造函数，默认1900/1/1
//     拷贝构造函数，重载赋值运算符
//     Set相关函数：设置日期、年份、月份、日期
//     重载比较运算符：==、!=、<、>、<=、>=、+、-、+=、-=
//     重载自增、自减运算符：++、--
//     重载减法运算符：-，计算两个日期之间的天数
//     CalculateDays：计算离指定日期的天数
//     Now：显示当前日期
//     ToWeekDay：计算指定日期是星期几
//     IsLeapYear：判断是否为闰年
//     IsValid：判断日期是否合法
//     GetMaxDay：获取该月最大的天数
//     IsFullYear：判断两个日期间是否满一年
//     ToString：将日期转换为字符串，可指定格式
//     重载输入输出运算符：<<、>>
//     常引用：year、month、day
class Date 
{
public:
    // 构造函数
    Date(unsigned int aYear = 1900, unsigned int aMonth = 1, unsigned int aDay = 1);
    Date(unsigned int aYear = 1900, const Month& amonth = Month(1), unsigned int aDay = 1);
    Date(const Date& date);
    Date& operator=(const Date& date);

    // 改变日期
    void SetDate(unsigned int aYear, unsigned int aMonth, unsigned int aDay);
    void SetYear(unsigned int aYear);
    void SetMonth(unsigned int aMonth);
    void SetMonth(const char* aMonth);
    void SetMonth(const string& aMonth);
    void SetMonth(const Month aMonth);
    void SetDay(unsigned int aDay);

    // 重载运算符
    bool operator==(const Date& date) const;
    bool operator!=(const Date& date) const;
    bool operator<(const Date& date) const;
    bool operator>(const Date& date) const;
    bool operator<=(const Date& date) const;
    bool operator>=(const Date& date) const;
    Date& operator+(unsigned int days);
    Date& operator-(unsigned int days);
    Date& operator+=(unsigned int days);
    Date& operator-=(unsigned int days);

    // 重载自增、自减运算符
    Date& operator++();
    Date operator++(int);
    Date& operator--();
    Date operator--(int);

    // 重载减法运算符,计算两个日期之间的天数
    long long operator-(const Date& date) const;

    // 计算离指定日期的天数（默认为1900/1/1）
    long long CalculateDays() const;
    static long long CalculateDays(const Date& date1);
    static long long CalculateDays(unsigned int aYear, unsigned int aMonth, unsigned int aDay);

    // 显示当前日期
    static Date Now();

    // 计算指定日期是星期几
    unsigned int ToWeekDay() const;
    static unsigned int ToWeekDay(const Date& date);
    static unsigned int ToWeekDay(unsigned int aYear, unsigned int aMonth, unsigned int aDay);

    // 判断是否为闰年
    bool IsLeapYear() const;
    static bool IsLeapYear(unsigned int aYear);

    // 判断日期是否合法
    bool IsValid() const;
    static bool IsValid(unsigned int aYear, unsigned int aMonth, unsigned int aDay);

    // 获取该月最大的天数
    unsigned int GetMaxDay() const;
    static unsigned int GetMaxDay(unsigned int aYear, unsigned int aMonth);
    static unsigned int GetMaxDay(const Date& date);
    static unsigned int GetMaxDay(unsigned int aYear, const Month& aMonth);

    // 判断两个日期间是否满一年
    bool IsFullYear(const Date& date) const;
    bool IsFullYear(unsigned int aYear, unsigned int aMonth, unsigned int aDay) const;
    static bool IsFullYear(const Date& date1, const Date& date2);
    static bool IsFullYear(unsigned int aYear1, unsigned int aMonth1, unsigned int aDay1, 
        unsigned int aYear2, unsigned int aMonth2, unsigned int aDay2);

    // 格式化显示,默认为"yyyy/mm/dd"
    enum class Format{backslash, hyphen, character}; // 日期格式枚举类
    static enum Format DefaultFormat;
    static string ToString(const Date& aDate, const enum Format& aformat = DefaultFormat);
    static string ToString(unsigned int aYear, unsigned int aMonth, unsigned int aDay, const enum Format& aformat = DefaultFormat);
    string ToString(const enum Format& aformat = DefaultFormat) const;

    // 重载输入输出运算符
    friend istream& operator>>(istream& is, Date& date);
    friend ostream& operator<<(ostream& os, const Date& date);
    friend ostream& operator<<(ostream& os, const enum Format& aformat);

    const unsigned int& year = m_Year; // 年份常引用
    const Month& month = m_Month; // 月份常引用
    const unsigned int& day = m_Day; // 日期常引用
    
private:
    unsigned int m_Year; // 年份
    Month m_Month; // 月份
    unsigned int m_Day; // 日期

    static unsigned int Max_Year; // 最大年份
    static unsigned int Min_Year; // 最小年份
    static unsigned int Max_Month; // 最大月份
    static unsigned int Min_Month; // 最小月份
    static unsigned int Min_Day; // 最小日期
    static unsigned int Month_Day[2][13]; // 每月的天数
    static vector<string> m_AllDay; // 所有日期
};

#endif /* Date_hpp */