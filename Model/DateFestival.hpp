//
// DateFestival.hpp
// Declaration of the DateFestival class.
// Created by 洪宸宇 on 14/7/2023
// 添加注释 29/7/2023
//

#ifndef DateFestival_hpp
#define DateFestival_hpp

#include "Date.hpp"
#include "Festival.hpp"

typedef shared_ptr<Festival> FesPtr;

// DateFestival类，用于表示节日（以月份和日期表示,不包括农历）
// 由Festival类派生而来，增加了日期成员
// 私有成员：
// m_Date: 日期
// 构造函数，传入节日名称和日期，或者传入节日名称和月份和日期
// 公有成员：
// Add: 增加节日，传入节日名称和日期，或者传入节日名称和月份和日期
// Del: 删除节日，传入节日名称
// Reset类：修改节日名称和日期、月份、日期、年份
// Search类：查找节日，传入节日名称或者日期、月份、日期、年份
// 重载比较运算符：比较两个节日的日期，==、!=、<、>、<=、>=
// Sort类：排序节日，传入两个日期或者两个年份、月份、日期
// ReadFromFile: 从指定文件读取节日信息
// WriteToFile: 将节日信息写入指定文件
// ToString: 格式化显示节日信息，与Date类的ToString类似
// 重载<<运算符：输出节日信息
// 常引用：date
class DateFestival : public Festival
{
public:
    // 禁止拷贝构造和赋值
    DateFestival(const DateFestival& Source) = delete;
    DateFestival& operator=(const DateFestival& Source) = delete;
    // 析构函数
    virtual ~DateFestival();

    // 增加或根据条件删除节日
    static FesPtr Add(const string& Name, const Date& Date);
    static FesPtr Add(const string& Name, const unsigned int Month, const unsigned int Day, const unsigned int Year = Min_year);
    static FesPtr ListAdd(const string& Name, const Date& Date); // 添加到搜索列表
    static void Del(const string& Name);

    // 修改节日名称与日期
    void ResetName(const string& NewName);
    static void ResetName(const string& Name, const string& NewName);
    void ResetDate(const Date& NewDate);
    static void ResetDate(const string& Name, const Date& NewDate);
    void ResetDate(const unsigned int NewMonth, const unsigned int NewDay, const unsigned int NewYear = Min_year);
    static void ResetDate(const string& Name, const unsigned int NewMonth, const unsigned int NewDay, const unsigned int NewYear = Min_year);
    void ResetYear(const unsigned int NewYear);
    static void ResetYear(const string& Name, const unsigned int NewYear);
    void ResetMonth(const unsigned int NewMonth);
    static void ResetMonth(const string& Name, const unsigned int NewMonth);
    void ResetDay(const unsigned int NewDay);
    static void ResetDay(const string& Name, const unsigned int NewDay);

    // 查找指定节日
    static FesPtr SearchName(const string& Name);
    // 查找两个日期之间的节日，存在搜索列表中，返回搜索列表的拷贝
    static vector<FesPtr> SearchDay(const Date& Date);
    static vector<FesPtr> SearchDay(const unsigned int Month, const unsigned int Day, const unsigned int Year = Min_year);
    static vector<FesPtr> SearchMonth(const unsigned int Month, const unsigned int Year = Min_year);
    static vector<FesPtr> Search(const Date& Date1, const Date& Date2);
    static vector<FesPtr> Search(const unsigned int Year1, const unsigned int Month1, const unsigned int Day1, 
        const unsigned int Year2,const unsigned int Month2, const unsigned int Day2);

    // 重载比较运算符
    bool operator==(const DateFestival& Source) const;
    bool operator!=(const DateFestival& Source) const;
    bool operator<(const DateFestival& Source) const;
    bool operator>(const DateFestival& Source) const;
    bool operator<=(const DateFestival& Source) const;
    bool operator>=(const DateFestival& Source) const;

    // 节日排序
    static vector<FesPtr> SortByNameUp(const Date& Date1, const Date& Date2);
    static vector<FesPtr> SortByNameUp(const unsigned int Year1, const unsigned int Month1, const unsigned int Day1, 
        const unsigned int Year2,const unsigned int Month2, const unsigned int Day2);
    static vector<FesPtr> SortByDateUp(const Date& Date1, const Date& Date2);
    static vector<FesPtr> SortByDateUp(const unsigned int Year1, const unsigned int Month1, const unsigned int Day1, 
        const unsigned int Year2,const unsigned int Month2, const unsigned int Day2);
    static vector<FesPtr> SortByNameDown(const Date& Date1, const Date& Date2);
    static vector<FesPtr> SortByNameDown(const unsigned int Year1, const unsigned int Month1, const unsigned int Day1, 
        const unsigned int Year2,const unsigned int Month2, const unsigned int Day2);
    static vector<FesPtr> SortByDateDown(const Date& Date1, const Date& Date2);
    static vector<FesPtr> SortByDateDown(const unsigned int Year1, const unsigned int Month1, const unsigned int Day1, 
        const unsigned int Year2,const unsigned int Month2, const unsigned int Day2);

    // 从指定文件读取节日信息
    static void ReadFromFile(const string& FileName);

    // 将节日信息写入指定文件
    static void WriteToFile(const string& FileName);

    //格式化显示
    enum class FestivalFormat{backslash, hyphen, character};
    static enum FestivalFormat DeFesFormat;
    string ToString(const enum FestivalFormat& aformat = DeFesFormat) const;
    static string ToString(const DateFestival& Festival, const enum FestivalFormat& aformat = DeFesFormat);
    static string ToString(const string& Festival, const Date& Date, const enum FestivalFormat& aformat = DeFesFormat);
    static string ToString(const string& Festival, unsigned int Month, unsigned int Day, const enum FestivalFormat& aformat = DeFesFormat);

    // 重载输出运算符
    friend ostream& operator<<(ostream& Output, const DateFestival& Source);
    friend ostream& operator<<(ostream& Output, const enum FestivalFormat& aformat);

    // 直接获取节日信息
    const Date& date = m_Date;

private:
    Date m_Date;

    // 构造函数
    DateFestival(const string& Name, const Date& Date);
    DateFestival(const string& Name, const unsigned int Month, const unsigned int Day, const unsigned int Year = Min_year);
    static const unsigned int Min_year = 1900;
    static vector<string> m_AllDays; // 所有日期

};

#endif /* DateFestival_hpp */