//
// WeekDay.cpp
// Implementation of the WeekDay class.
// Created by 洪宸宇 on 14/7/2023
// 添加注释 29/7/2023
//

#include <stdexcept>
#include "WeekDay.hpp"

using std::invalid_argument;

const string WeekDay::m_WeekDays[8] = {
    "", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
};

// 构造函数
// 传入星期值进行赋值
WeekDay::WeekDay(unsigned int Value)
{
    Set(Value);
}

// 构造函数
// 传入单词进行赋值
WeekDay::WeekDay(const string& WeekDay)
{
    Set(WeekDay);
}

// 构造函数
// 传入单词进行赋值
WeekDay::WeekDay(const char* WeekDay)
{
    Set(WeekDay);
}

// 拷贝构造函数
WeekDay::WeekDay(const WeekDay& WeekDay)
{
    Set(WeekDay.m_WeekDay);
}

// 重载赋值运算符
// 传入类对象进行赋值
WeekDay& WeekDay::operator=(const WeekDay& WeekDay)
{
    Set(WeekDay.m_WeekDay);
    return *this;
}

// 重载赋值运算符
// 传入单词进行赋值
WeekDay& WeekDay::operator=(const string& WeekDay)
{
    Set(WeekDay);
    return *this;
}

// 重载赋值运算符
// 传入单词进行赋值
WeekDay& WeekDay::operator=(const char* WeekDay)
{
    Set(WeekDay);
    return *this;
}

// 重载赋值运算符
// 传入星期值进行赋值
WeekDay& WeekDay::operator=(unsigned int Value)
{
    Set(Value);
    return *this;
}

// Set函数
// 修改星期值与单词
// 传入星期值
// 无返回值
void WeekDay::Set(unsigned int Value)
{
    if (Value < 1 || Value > 7)
        throw invalid_argument("Invalid WeekDay!");
    m_Value = Value;
    m_WeekDay = m_WeekDays[Value];
}

// Set函数
// 修改星期值与单词
// 传入单词
// 无返回值
void WeekDay::Set(const string& WeekDay)
{
    if (IsValid(WeekDay)){
        Set(ToValue(WeekDay));
    }
    else{
        throw invalid_argument("Invalid WeekDay!");
    }
}

// Set函数
// 修改星期值与单词
// 传入单词
// 无返回值
void WeekDay::Set(const char* WeekDay)
{
    Set(string(WeekDay));
}

// ToValue函数
// 星期单词返回对应的数值
// 传入单词
// 返回星期值
unsigned int WeekDay::ToValue(string WeekDay)
{
    for (int i = 1; i <= 7; i++){
        if (WeekDay == m_WeekDays[i])
            return i;
    }
    throw invalid_argument("Invalid WeekDay!");
}

// ToValue函数
// 星期单词返回对应的数值
// 传入单词
// 返回星期值
unsigned int WeekDay::ToValue(const char* WeekDay)
{
    return ToValue(string(WeekDay));
}

// ToValue函数
// 星期对象返回对应的数值
// 传入星期对象
// 返回星期值
unsigned int WeekDay::ToValue(const WeekDay& WeekDay)
{
    return WeekDay.m_Value;
}

// ToValue函数
// 星期对象返回对应的数值
// 传入星期对象不传入参数
// 返回星期值
unsigned int WeekDay::ToValue() const
{
    return m_Value;
}

// ToName函数
// 星期值返回对应的单词
// 传入星期值
// 返回星期单词
string WeekDay::ToName(unsigned int Value)
{
    if (Value < 1 || Value > 7)
        throw invalid_argument("Invalid WeekDay!");
    return m_WeekDays[Value];
}

// ToName函数
// 星期值返回对应的单词
// 传入星期值
// 返回星期单词
string WeekDay::ToName(const WeekDay& WeekDay)
{
    return WeekDay.ToName();
}

// ToName函数
// 星期值返回对应的单词
// 无传入值
// 返回星期单词
string WeekDay::ToName() const
{
    return m_WeekDay;
}

// 重载==运算符
// 传入星期对象进行比较
// 返回bool值
bool WeekDay::operator==(const WeekDay& WeekDay) const
{
    return m_Value == WeekDay.m_Value;
}

// 重载==运算符
// 传入星期值进行比较
// 返回bool值
bool WeekDay::operator==(unsigned int Value) const
{
    return m_Value == Value;
}

// 重载==运算符，友元函数
// 传入星期值和星期对象进行比较
// 返回bool值
bool operator==(unsigned int Value, const WeekDay& WeekDay)
{
    return Value == WeekDay.m_Value;
}

// 重载==运算符
// 传入星期单词进行比较
// 返回bool值
bool WeekDay::operator==(const char* WeekDay) const
{
    return m_WeekDay == WeekDay;
}

// 重载==运算符，友元函数
// 传入星期单词和星期对象进行比较
// 返回bool值
bool operator==(const char* aWeekDay, const WeekDay& WeekDay)
{
    return aWeekDay == WeekDay.m_WeekDay;
}

// 重载!=运算符
// 传入星期对象进行比较
// 返回bool值
bool WeekDay::operator!=(const WeekDay& WeekDay) const
{
    return m_Value != WeekDay.m_Value;
}

// 重载!=运算符
// 传入星期值进行比较
// 返回bool值
bool WeekDay::operator!=(unsigned int Value) const
{
    return m_Value != Value;
}

// 重载!=运算符，友元函数
// 传入星期值和星期对象进行比较
// 返回bool值
bool operator!=(unsigned int Value, const WeekDay& WeekDay)
{
    return Value != WeekDay.m_Value;
}

// 重载!=运算符
// 传入星期单词进行比较
// 返回bool值
bool WeekDay::operator!=(const char* WeekDay) const
{
    return m_WeekDay != WeekDay;
}

// 重载!=运算符，友元函数
// 传入星期单词和星期对象进行比较
// 返回bool值
bool operator!=(const char* aWeekDay, const WeekDay& WeekDay)
{
    return aWeekDay != WeekDay.m_WeekDay;
}

// 重载<运算符
// 传入星期对象进行比较
// 返回bool值
bool WeekDay::operator<(const WeekDay& WeekDay) const
{
    return m_Value < WeekDay.m_Value;
}

// 重载<运算符
// 传入星期值进行比较
// 返回bool值
bool WeekDay::operator<(unsigned int Value) const
{
    return m_Value < Value;
}

// 重载<运算符，友元函数
// 传入星期值和星期对象进行比较
// 返回bool值
bool operator<(unsigned int Value, const WeekDay& WeekDay)
{
    return Value < WeekDay.m_Value;
}

// 重载<运算符
// 传入星期单词进行比较
// 返回bool值
bool WeekDay::operator<(const char* WeekDay) const
{
    return m_WeekDay < WeekDay;
}

// 重载<运算符，友元函数
// 传入星期单词和星期对象进行比较
// 返回bool值
bool operator<(const char* aWeekDay, const WeekDay& WeekDay)
{
    return aWeekDay < WeekDay.m_WeekDay;
}

// 重载<=运算符
// 传入星期对象进行比较
// 返回bool值
bool WeekDay::operator<=(const WeekDay& WeekDay) const
{
    return m_Value <= WeekDay.m_Value;
}

// 重载<=运算符
// 传入星期值进行比较
// 返回bool值
bool WeekDay::operator<=(unsigned int Value) const
{
    return m_Value <= Value;
}

// 重载<=运算符，友元函数
// 传入星期值和星期对象进行比较
// 返回bool值
bool operator<=(unsigned int Value, const WeekDay& WeekDay)
{
    return Value <= WeekDay.m_Value;
}

// 重载<=运算符
// 传入星期单词进行比较
// 返回bool值
bool WeekDay::operator<=(const char* WeekDay) const
{
    return m_WeekDay <= WeekDay;
}

// 重载<=运算符，友元函数
// 传入星期单词和星期对象进行比较
// 返回bool值
bool operator<=(const char* aWeekDay, const WeekDay& WeekDay)
{
    return aWeekDay <= WeekDay.m_WeekDay;
}

// 重载>运算符
// 传入星期对象进行比较
// 返回bool值
bool WeekDay::operator>(const WeekDay& WeekDay) const
{
    return m_Value > WeekDay.m_Value;
}

// 重载>运算符
// 传入星期值进行比较
// 返回bool值
bool WeekDay::operator>(unsigned int Value) const
{
    return m_Value > Value;
}

// 重载>运算符，友元函数
// 传入星期值和星期对象进行比较
// 返回bool值
bool operator>(unsigned int Value, const WeekDay& WeekDay)
{
    return Value > WeekDay.m_Value;
}

// 重载>运算符
// 传入星期单词进行比较
// 返回bool值
bool WeekDay::operator>(const char* WeekDay) const
{
    return m_WeekDay > WeekDay;
}

// 重载>运算符，友元函数
// 传入星期单词和星期对象进行比较
// 返回bool值
bool operator>(const char* aWeekDay, const WeekDay& WeekDay)
{
    return aWeekDay > WeekDay.m_WeekDay;
}

// 重载>=运算符
// 传入星期对象进行比较
// 返回bool值
bool WeekDay::operator>=(const WeekDay& WeekDay) const
{
    return m_Value >= WeekDay.m_Value;
}

// 重载>=运算符
// 传入星期值进行比较
// 返回bool值
bool WeekDay::operator>=(unsigned int Value) const
{
    return m_Value >= Value;
}

// 重载>=运算符，友元函数
// 传入星期值和星期对象进行比较
// 返回bool值
bool operator>=(unsigned int Value, const WeekDay& WeekDay)
{
    return Value >= WeekDay.m_Value;
}

// 重载>=运算符
// 传入星期单词进行比较
// 返回bool值
bool WeekDay::operator>=(const char* aWeekDay) const
{
    return m_WeekDay >= aWeekDay;
}

// 重载>=运算符，友元函数
// 传入星期单词和星期对象进行比较
// 返回bool值
bool operator>=(const char* aWeekDay, const WeekDay& bWeekDay)
{
    return aWeekDay >= bWeekDay.m_WeekDay;
}

// 重载前置自增运算符
// 星期值加一
// 返回自增后的星期对象
WeekDay& WeekDay::operator++()
{
    if (m_Value == 7) {
        this->Set(1);
    }
    else {
        this->Set(m_Value + 1);
    }
    return *this;
}

// 重载后置自增运算符
// 星期值加一
// 返回自增前的星期对象
WeekDay WeekDay::operator++(int)
{
    WeekDay temp = *this;
    ++*this;
    return temp;
}

// 重载前置自减运算符
// 星期值减一
// 返回自减后的星期对象
WeekDay& WeekDay::operator--()
{
    if (m_Value == 1) {
        this->Set(7);
    }
    else {
        this->Set(m_Value - 1);
    }
    return *this;
}

// 重载后置自减运算符
// 星期值减一
// 返回自减前的星期对象
WeekDay WeekDay::operator--(int)
{
    WeekDay temp = *this;
    --*this;
    return temp;
}

// IsValid函数
// 判断星期单词是否合法
// 传入星期单词
// 返回bool值
bool WeekDay::IsValid(const string& WeekDay)
{
    for (int i = 1; i <= 7; i++) {
        if (WeekDay == m_WeekDays[i])
            return true;
    }
    return false;
}