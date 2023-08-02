//
// Month.cpp
// Implementation of the Month class.
// Created by 洪宸宇 on 14/7/2023
// 添加注释 29/7/2023
//

#include <stdexcept>
#include "Month.hpp"

using std::invalid_argument;

const string Month::m_Months[13] = {
    "", "January", "February", "March", "April", "May", "June", "July", "August", 
    "September", "October", "November", "December"
};

// 构造函数
// 传入月份值进行赋值
Month::Month(unsigned int Value)
{
    Set(Value);
}

// 构造函数
// 传入单词进行赋值
Month::Month(const string& Month)
{
    Set(Month);
}

// 构造函数
// 传入单词进行赋值
Month::Month(const char* Month)
{
    Set(Month);
}

// 拷贝构造函数
Month::Month(const Month& Month)
{
    Set(Month.m_Month);
}

// 重载赋值运算符
// 传入类对象进行赋值
Month& Month::operator=(const Month& Month)
{
    Set(Month.m_Month);
    return *this;
}

// 重载赋值运算符
// 传入单词进行赋值
Month& Month::operator=(const string& Month)
{
    Set(Month);
    return *this;
}

// 重载赋值运算符
// 传入单词进行赋值
Month& Month::operator=(const char* Month)
{
    Set(Month);
    return *this;
}

// 重载赋值运算符
// 传入月份值进行赋值
Month& Month::operator=(unsigned int Value)
{
    Set(Value);
    return *this;
}

// Set函数
// 修改月份值与单词
// 传入月份值
// 无返回值
void Month::Set(unsigned int Value)
{
    if (Value < 1 || Value > 12)
        throw invalid_argument("Invalid month!");
    m_Value = Value;
    m_Month = m_Months[Value];
}

// Set函数
// 修改月份值与单词
// 传入单词
// 无返回值
void Month::Set(const string& Month)
{
    if (IsValid(Month)) {
        Set(ToValue(Month));
    }
    else {
        throw invalid_argument("Invalid month!");
    }
}

// Set函数
// 修改月份值与单词
// 传入单词
// 无返回值
void Month::Set(const char* Month)
{
    Set(string(Month));
}

// ToValue函数
// 月份单词返回对应的数值
// 传入单词
// 返回月份值
unsigned int Month::ToValue(const string Month)
{
    for (int i = 1; i <= 12; i++)
        if (Month == m_Months[i])
            return i;
    throw invalid_argument("Invalid month!");
}

// ToValue函数
// 月份单词返回对应的数值
// 传入单词
// 返回月份值
unsigned int Month::ToValue(const char* Month)
{
    return ToValue(string(Month));
}

// ToValue函数
// 月份对象返回对应的数值
// 传入月份对象
// 返回月份值
unsigned int Month::ToValue(const Month& Month)
{
    return Month.ToValue();
}

// ToValue函数
// 月份对象返回对应的数值
// 传入月份对象不传入参数
// 返回月份值
unsigned int Month::ToValue() const
{
    return m_Value;
}

// ToName函数
// 月份值返回对应的单词
// 传入月份值
// 返回月份单词
string Month::ToName(unsigned int Value)
{
    if (Value < 1 || Value > 12)
        throw invalid_argument("Invalid month!");
    return m_Months[Value];
}

// ToName函数
// 月份值返回对应的单词
// 传入月份值
// 返回月份单词
string Month::ToName(const Month& Month)
{
    return Month.ToName();
}

// ToName函数
// 月份值返回对应的单词
// 无传入值
// 返回月份单词
string Month::ToName() const
{
    return m_Month;
}

// 重载==运算符
// 传入月份对象进行比较
// 返回bool值
bool Month::operator==(const Month& Month) const
{
    return m_Value == Month.m_Value;
}

// 重载==运算符
// 传入月份值进行比较
// 返回bool值
bool Month::operator==(unsigned int Value) const
{
    return m_Value == Value;
}

// 重载==运算符，友元函数
// 传入月份值和月份对象进行比较
// 返回bool值
bool operator==(unsigned int Value, const Month& Month)
{
    return Value == Month.m_Value;
}

// 重载==运算符
// 传入月份单词进行比较
// 返回bool值
bool Month::operator==(const char* Month) const
{
    return m_Month == Month;
}

// 重载==运算符，友元函数
// 传入月份单词和月份对象进行比较
// 返回bool值
bool operator==(const char* aMonth, const Month& Month)
{
    return aMonth == Month.m_Month;
}

// 重载!=运算符
// 传入月份对象进行比较
// 返回bool值
bool Month::operator!=(const Month& Month) const
{
    return m_Value != Month.m_Value;
}

// 重载!=运算符
// 传入月份值进行比较
// 返回bool值
bool Month::operator!=(unsigned int Value) const
{
    return m_Value != Value;
}

// 重载!=运算符，友元函数
// 传入月份值和月份对象进行比较
// 返回bool值
bool operator!=(unsigned int Value, const Month& Month)
{
    return Value != Month.m_Value;
}

// 重载!=运算符
// 传入月份单词进行比较
// 返回bool值
bool Month::operator!=(const char* Month) const
{
    return m_Month != Month;
}

// 重载!=运算符，友元函数
// 传入月份单词和月份对象进行比较
// 返回bool值
bool operator!=(const char* aMonth, const Month& Month)
{
    return aMonth != Month.m_Month;
}

// 重载<运算符
// 传入月份对象进行比较
// 返回bool值
bool Month::operator<(const Month& Month) const
{
    return m_Value < Month.m_Value;
}

// 重载<运算符
// 传入月份值进行比较
// 返回bool值
bool Month::operator<(unsigned int Value) const
{
    return m_Value < Value;
}

// 重载<运算符，友元函数
// 传入月份值和月份对象进行比较
// 返回bool值
bool operator<(unsigned int Value, const Month& Month)
{
    return Value < Month.m_Value;
}

// 重载<运算符
// 传入月份单词进行比较
// 返回bool值
bool Month::operator<(const char* aMonth) const
{
    return (*this) < Month(aMonth);
}

// 重载<运算符，友元函数
// 传入月份单词和月份对象进行比较
// 返回bool值
bool operator<(const char* aMonth, const Month& bMonth)
{
    return Month(aMonth) < bMonth;
}

// 重载<=运算符
// 传入月份对象进行比较
// 返回bool值
bool Month::operator<=(const Month& Month) const
{
    return m_Value <= Month.m_Value;
}

// 重载<=运算符
// 传入月份值进行比较
// 返回bool值
bool Month::operator<=(unsigned int Value) const
{
    return m_Value <= Value;
}

// 重载<=运算符，友元函数
// 传入月份值和月份对象进行比较
// 返回bool值
bool operator<=(unsigned int Value, const Month& Month)
{
    return Value <= Month.m_Value;
}

// 重载<=运算符
// 传入月份单词进行比较
// 返回bool值
bool Month::operator<=(const char* aMonth) const
{
    return (*this) <= Month(aMonth);
}

// 重载<=运算符，友元函数
// 传入月份单词和月份对象进行比较
// 返回bool值
bool operator<=(const char* aMonth, const Month& bMonth)
{
    return Month(aMonth) <= bMonth;
}

// 重载>运算符
// 传入月份对象进行比较
// 返回bool值
bool Month::operator>(const Month& Month) const
{
    return m_Value > Month.m_Value;
}

// 重载>运算符
// 传入月份值进行比较
// 返回bool值
bool Month::operator>(unsigned int Value) const
{
    return m_Value > Value;
}

// 重载>运算符，友元函数
// 传入月份值和月份对象进行比较
// 返回bool值
bool operator>(unsigned int Value, const Month& Month)
{
    return Value > Month.m_Value;
}

// 重载>运算符
// 传入月份单词进行比较
// 返回bool值
bool Month::operator>(const char* aMonth) const
{
    return (*this) > Month(aMonth);
}

// 重载>运算符，友元函数
// 传入月份单词和月份对象进行比较
// 返回bool值
bool operator>(const char* aMonth, const Month& bMonth)
{
    return Month(aMonth) > bMonth;
}

// 重载>=运算符
// 传入月份对象进行比较
// 返回bool值
bool Month::operator>=(const Month& Month) const
{
    return m_Value >= Month.m_Value;
}

// 重载>=运算符
// 传入月份值进行比较
// 返回bool值
bool Month::operator>=(unsigned int Value) const
{
    return m_Value >= Value;
}

// 重载>=运算符，友元函数
// 传入月份值和月份对象进行比较
// 返回bool值
bool operator>=(unsigned int Value, const Month& Month)
{
    return Value >= Month.m_Value;
}

// 重载>=运算符
// 传入月份单词进行比较
// 返回bool值
bool Month::operator>=(const char* aMonth) const
{
    return (*this) >= Month(aMonth);
}

// 重载>=运算符，友元函数
// 传入月份单词和月份对象进行比较
// 返回bool值
bool operator>=(const char* aMonth, const Month& bMonth)
{
    return Month(aMonth) >= bMonth;
}

// 重载前置自增运算符
// 月份值加一
// 返回自增后的月份对象
Month& Month::operator++()
{
    if (m_Value == 12) {
        this->Set(1);
    }
    else {
        this->Set(m_Value + 1);
    }
    return *this;
}

// 重载后置自增运算符
// 月份值加一
// 返回自增前的月份对象
Month Month::operator++(int)
{
    Month Temp(*this);
    ++(*this);
    return Temp;
}

// 重载前置自减运算符
// 月份值减一
// 返回自减后的月份对象
Month& Month::operator--()
{
    if (m_Value == 1) {
        Set(12);
    }
    else {
        Set(m_Value - 1);
    }
    return *this;
}

// 重载后置自减运算符
// 月份值减一
// 返回自减前的月份对象
Month Month::operator--(int)
{
    Month Temp(*this);
    --(*this);
    return Temp;
}

// IsValid函数
// 判断月份单词是否合法
// 传入月份单词
// 返回bool值
bool Month::IsValid(const string& Month)
{
    for (int i = 1; i <= 12; i++) {
        if (Month == m_Months[i])
            return true;
    }
    return false;
}