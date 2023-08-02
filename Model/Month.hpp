//
// Month.hpp
// Declaration of the Month class.
// Created by 洪宸宇 on 14/7/2023
// 添加注释 29/7/2023
//

#ifndef Month_hpp
#define Month_hpp

#include <string>
#include <stdexcept>

using std::string;

// Month类，用于表示月份
// 私有成员：
//      m_Month：月份
//      m_Value：月份值
//      m_Months：月份数组（每个月的数值与单词对应）
// 公有成员：
//      构造函数，传入月份值以及单词 
//      拷贝构造函数
//      赋值运算符重载，建立月份值与单词之间的联系
//      Set函数，传入月份值以及单词，修改月份值与单词
//      ToValue函数，传入单词，返回月份值
//      ToName函数，传入月份值，返回单词
//      重载运算符，判断月份值与单词，单词与单词是否相等
//      重载自增、自减运算符
//      IsValid函数，判断单词是否是合理月份
//     month：月份常引用
//     value：月份值常引用
class Month 
{
public:
    // 构造函数
    Month(unsigned int Value); 
    Month(const string& Month);
    Month(const char* Month);
    Month(const Month& Month); // 拷贝构造函数
     // 赋值运算符重载
    Month& operator=(const Month& Month);
    Month& operator=(const string& Month);
    Month& operator=(const char* Month);
    Month& operator=(unsigned int Value); // 传入月份值进行赋值

    // 设定和修改月份
    void Set(unsigned int Value); // 传入月份值进行修改
    void Set(const string& Month); // 传入单词进行修改
    void Set(const char* Month);

    // 获取月份
    static unsigned int ToValue(const string Month); // 传入单词，返回月份值
    static unsigned int ToValue(const char* Month);
    static unsigned int ToValue(const Month& Month);
    unsigned int ToValue() const;
    static string ToName(unsigned int Value); // 传入月份值，返回单词
    static string ToName(const Month& Month);
    string ToName() const;

    // 重载运算符,判断月份值与单词，单词与单词是否相等
    bool operator==(const Month& Month) const;
    bool operator==(unsigned int Value) const;
    friend bool operator==(unsigned int Value, const Month& Month);
    bool operator==(const char* Month) const;
    friend bool operator==(const char* aMonth, const Month& Month);

    bool operator!=(const Month& Month) const;
    bool operator!=(unsigned int Value) const;
    friend bool operator!=(unsigned int Value, const Month& Month);
    bool operator!=(const char* Month) const;
    friend bool operator!=(const char* aMonth, const Month& Month);

    bool operator<(const Month& Month) const;
    bool operator<(unsigned int Value) const;
    friend bool operator<(unsigned int Value, const Month& Month);
    bool operator<(const char* aMonth) const;
    friend bool operator<(const char* aMonth, const Month& bMonth);

    bool operator<=(const Month& Month) const;
    bool operator<=(unsigned int Value) const;
    friend bool operator<=(unsigned int Value, const Month& Month);
    bool operator<=(const char* aMonth) const;
    friend bool operator<=(const char* aMonth, const Month& bMonth);

    bool operator>(const Month& Month) const;
    bool operator>(unsigned int Value) const;
    friend bool operator>(unsigned int Value, const Month& Month);
    bool operator>(const char* aMonth) const;
    friend bool operator>(const char* aMonth, const Month& bMonth);
    
    bool operator>=(const Month& Month) const;
    bool operator>=(unsigned int Value) const;
    friend bool operator>=(unsigned int Value, const Month& Month);
    bool operator>=(const char* aMonth) const;
    friend bool operator>=(const char* aMonth, const Month& bMonth);

    //重载自增、自减运算符
    Month& operator++(); // 前置自增
    Month operator++(int); // 后置自增
    Month& operator--(); // 前置自减
    Month operator--(int); // 后置自减

    // 判断是否是合理月份
    static bool IsValid(const string& Month);

    const string& month = m_Month; // 月份常引用
    const unsigned int& value = m_Value; // 月份值常引用
private:
    string m_Month; // 月份
    unsigned int m_Value; // 月份值
    static const string m_Months[13]; // 月份数组
};

#endif /* Month_hpp */