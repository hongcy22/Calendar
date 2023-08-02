//
// WeekDay.hpp
// Declaration of the WeekDay class.
// Created by 洪宸宇 on 14/7/2023
// 添加注释 29/7/2023
//

#ifndef WeekDay_hpp
#define WeekDay_hpp

#include <string>
#include <stdexcept>

using std::string;

// WeekDay类，用于表示星期几
// 私有成员：
//      m_WeekDay：星期
//      m_Value：星期值
//      m_WeekDays：星期数组（每个星期几的数值与单词对应）
// 公有成员：
//      构造函数，传入星期值以及单词
//      拷贝构造函数
//      赋值运算符重载，建立星期值与单词之间的联系
//      Set函数，传入星期值以及单词，修改星期值与单词
//      ToValue函数，传入单词，返回星期值
//      ToName函数，传入星期值，返回单词
//      重载运算符，判断星期值与单词，单词与单词是否相等
//      重载自增、自减运算符
//      IsValid函数，判断单词是否是合理星期几
//     weekday：星期常引用
//     value：星期值常引用
class WeekDay 
{
public:
    // 构造函数
    WeekDay(unsigned int Value); 
    WeekDay(const string& WeekDay);
    WeekDay(const char* WeekDay); 
    WeekDay(const WeekDay& WeekDay); // 拷贝构造函数
     // 赋值运算符重载
    WeekDay& operator=(const WeekDay& WeekDay);
    WeekDay& operator=(const string& WeekDay);
    WeekDay& operator=(const char* WeekDay);
    WeekDay& operator=(unsigned int Value); // 传入星期值进行赋值

    // 设定和修改星期几
    void Set(unsigned int Value); // 传入星期值进行修改
    void Set(const string& WeekDay); // 传入单词进行修改
    void Set(const char* WeekDay);

    // 获取星期几
    static unsigned int ToValue(const string WeekDay); // 传入单词，返回星期值
    static unsigned int ToValue(const char* WeekDay);
    static unsigned int ToValue(const WeekDay& WeekDay);
    unsigned int ToValue()const ;
    static string ToName(unsigned int Value); // 传入星期值，返回单词
    static string ToName(const WeekDay& WeekDay);
    string ToName()const ;

    // 重载运算符，判断星期值与单词，单词与单词是否相等
    bool operator==(const WeekDay& WeekDay) const;
    bool operator==(unsigned int Value) const;
    friend bool operator==(unsigned int Value, const WeekDay& WeekDay);
    bool operator==(const char* WeekDay) const;
    friend bool operator==(const char* aWeekDay, const WeekDay& WeekDay);

    bool operator!=(const WeekDay& WeekDay) const;
    bool operator!=(unsigned int Value) const;
    friend bool operator!=(unsigned int Value, const WeekDay& WeekDay);
    bool operator!=(const char* WeekDay) const;
    friend bool operator!=(const char* aWeekDay, const WeekDay& WeekDay);

    bool operator<(const WeekDay& WeekDay) const;
    bool operator<(unsigned int Value) const;
    friend bool operator<(unsigned int Value, const WeekDay& WeekDay);
    bool operator<(const char* aWeekDay) const;
    friend bool operator<(const char* aWeekDay, const WeekDay& bWeekDay);

    bool operator<=(const WeekDay& WeekDay) const;
    bool operator<=(unsigned int Value) const;
    friend bool operator<=(unsigned int Value, const WeekDay& WeekDay);
    bool operator<=(const char* aWeekDay) const;
    friend bool operator<=(const char* aWeekDay, const WeekDay& bWeekDay);

    bool operator>(const WeekDay& WeekDay) const;
    bool operator>(unsigned int Value) const;
    friend bool operator>(unsigned int Value, const WeekDay& WeekDay);
    bool operator>(const char* aWeekDay) const;
    friend bool operator>(const char* aWeekDay, const WeekDay& bWeekDay);
    
    bool operator>=(const WeekDay& WeekDay) const;
    bool operator>=(unsigned int Value) const;
    friend bool operator>=(unsigned int Value, const WeekDay& WeekDay);
    bool operator>=(const char* aWeekDay) const;
    friend bool operator>=(const char* aWeekDay, const WeekDay& bWeekDay);

    //重载自增、自减运算符
    WeekDay& operator++(); // 前置++
    WeekDay operator++(int); // 后置++
    WeekDay& operator--(); // 前置--
    WeekDay operator--(int); // 后置--

    // 判断是否是合理星期
    static bool IsValid(const string& WeekDay);

    const string& weekday = m_WeekDay; // 星期几的名称
    const unsigned int& value = m_Value; // 星期几的值
private:
    string m_WeekDay; // 星期几
    unsigned int m_Value; // 星期几的值
    static const string m_WeekDays[8]; // 星期几的名称
};

#endif /* WeekDay_hpp */