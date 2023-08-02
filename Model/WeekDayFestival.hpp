//
// WeekDayFestival.hpp
// Declaration of the WeekDayFestival class.
// Created by 洪宸宇 on 14/7/2023
// 添加注释 29/7/2023
//

#ifndef WeekDayFestival_hpp
#define WeekDayFestival_hpp

#include "Festival.hpp"
#include "WeekDay.hpp"
#include "Month.hpp"
#include "Date.hpp"

typedef shared_ptr<Festival> FesPtr;

// WeekDayFestival类，用于表示星期节日
// 由Festival类派生而来，增加了星期类型和星期成员
// 私有成员：
// m_WeekType: 星期类型
// m_WeekDay: 星期
// m_Month: 月份
// m_StartYear: 起始年份
// 构造函数，传入节日名称和星期类型和星期，或者传入节日名称和月份和星期类型和星期
// 公有成员：
// Add: 增加节日，传入节日名称和星期类型和星期，或者传入节日名称和月份和星期类型和星期
// Del: 删除节日，传入节日名称
// Reset类：修改节日名称和星期类型和星期、月份、年份
// Search类：查找节日，传入节日名称或者月份和星期类型和星期、月份、年份
// Sort类：排序节日，传入两个日期
// ReadFromFile从指定文件读取节日信息
// WriteToFile将节日信息写入指定文件
// ToString返回节日信息的字符串
// 重载输出运算符
// 重载比较运算符==和!=
// WeekDayToDate将星期节日转换为日期
// IntToWeekType将整数转换为星期类型
// 常引用：
// month: 月份
// weektype: 星期类型
// weekday: 星期
// startyear: 起始年份
class WeekDayFestival : public Festival
{
public:
    // 星期类型，第几个星期
    enum class WeekType { First = 1, Second = 2, Third = 3, Fourth = 4, Last = 0};

    // 禁止拷贝构造和赋值
    WeekDayFestival(const WeekDayFestival& Source) = delete;
    WeekDayFestival& operator=(const WeekDayFestival& Source) = delete;
    // 析构函数
    virtual ~WeekDayFestival();

    // 增加或根据条件删除节日
    static FesPtr Add(const string& Name, const Month& Month, const WeekType& WeekType, const WeekDay& WeekDay, const unsigned int Year = Min_year);
    static FesPtr Add(const string& Name, unsigned int Month, unsigned int WeekType, unsigned int WeekDay, const unsigned int Year = Min_year);
    static FesPtr Add(const string& Name, const string& Month, const string& WeekType, const string& WeekDay, const unsigned int Year = Min_year);
    static void Del(const string& Name);

    // 修改节日名称与日期
    void ResetName(const string& NewName);
    static void ResetName(const string& Name, const string& NewName);
    void ResetDate(const Month& NewMonth, const WeekType& NewWeekType, const WeekDay& NewWeekDay);
    static void ResetDate(const string& Name, const Month& NewMonth, const WeekType& NewWeekType, const WeekDay& NewWeekDay);
    void ResetDate(unsigned int NewMonth, unsigned int NewWeekType, unsigned int NewWeekDay);
    static void ResetDate(const string& Name, unsigned int NewMonth, unsigned int NewWeekType, unsigned int NewWeekDay);
    void ResetMonth(const unsigned int NewMonth);
    static void ResetMonth(const string& Name, const unsigned int NewMonth);
    void ResetWeekType(unsigned int NewWeekType);
    static void ResetWeekType(const string& Name, unsigned int NewWeekType);
    void ResetWeekDay(unsigned int NewWeekDay);
    static void ResetWeekDay(const string& Name, unsigned int NewWeekDay);
    void ResetStartYear(unsigned int NewStartYear);
    static void ResetStartYear(const string& Name, unsigned int NewStartYear);

    // 查找指定节日
    static FesPtr SearchName(const string& Name);
    // 查找两个日期之间的节日，存在搜索列表中，返回搜索列表的拷贝
    static vector<FesPtr> SearchDay(const Month& Month, const WeekType& WeekType, const WeekDay& WeekDay, const unsigned int Year = Min_year);
    static vector<FesPtr> SearchDay(unsigned int aMonth, unsigned int WeekType, unsigned int aWeekDay, const unsigned int Year = Min_year);
    static vector<FesPtr> SearchMonth(const Month& Month, const unsigned int Year = Min_year);
    static vector<FesPtr> SearchMonth(unsigned int aMonth, const unsigned int Year = Min_year);
    static vector<FesPtr> SearchWeek(const Month& Month, const WeekType& WeekType, const unsigned int Year = Min_year);
    static vector<FesPtr> SearchWeek(unsigned int Month, unsigned int WeekType, const unsigned int Year = Min_year);
    static vector<FesPtr> Search(const Date& Date1, const Date& Date2);
    static vector<FesPtr> Search(const unsigned int Year1, const unsigned int Month1, const unsigned int Day1, 
        const unsigned int Year2,const unsigned int Month2, const unsigned int Day2);

    // 重载比较运算符
    bool operator==(const WeekDayFestival& Source) const;
    bool operator!=(const WeekDayFestival& Source) const;

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
    string ToString() const;
    static string ToString(const WeekDayFestival& Source);
    static string ToString(const string& Name, unsigned int Month, unsigned int WeekType, unsigned int WeekDay);

    // 重载输出运算符
    friend ostream& operator<<(ostream& Out, const WeekDayFestival& Source);

    // 星期转换为日期
    static Date WeekDayToDate(const Month& Month, const WeekType& WeekType, const WeekDay& WeekDay, const unsigned int Year);
    static Date WeekDayToDate(unsigned int Month, unsigned int WeekType, unsigned int WeekDay, const unsigned int Year);

    // 整数转化为星期序数
    static WeekType IntToWeekType(const unsigned int Int);

    // 直接获取节日信息
    const WeekDay& weekday = m_WeekDay;
    const WeekType& weektype = m_WeekType;
    const Month& month = m_Month;
    const unsigned int& startyear = m_StartYear;
    
private:
    WeekDay m_WeekDay;
    WeekType m_WeekType;
    Month m_Month;
    unsigned int m_StartYear; // 起始年份

    // 构造函数
    WeekDayFestival(const string& Name, const Month& Month, const WeekType& WeekType, const WeekDay& WeekDay, const unsigned int Year = Min_year);
    WeekDayFestival(const string& Name, unsigned int Month, unsigned int WeekType, unsigned int WeekDay, const unsigned int Year = Min_year);
    WeekDayFestival(const string& Name, const string& Month, const string& WeekType, const string& WeekDay, const unsigned int Year = Min_year);
    static const unsigned int Min_year = 1900;
    static const string WeekTypeStr[5]; // 星期序数字符串
};

#endif /* WeekDayFestival_hpp */