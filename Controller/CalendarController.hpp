//
// CalendarController.hpp
// Declaration of the Calendar class.
// Created by 洪宸宇 on 14/7/2023
// 添加注释 29/7/2023
//

#ifndef CalendarController_hpp
#define CalendarController_hpp

#include "Month.hpp"
#include "WeekDay.hpp"
#include "Date.hpp"
#include "Festival.hpp"
#include "DateFestival.hpp"
#include "WeekDayFestival.hpp"

using namespace std;

// 控制器的返回值
enum class CalendarControllerResult
{
    SUCCESS = 0, // 成功
    INVALID_YEAR = 1, // 无效年份
    INVALID_MONTH = 2, // 无效月份
    INVALID_DAY = 3, // 无效日子
    INVALID_FORMAT = 4, // 无效格式
    INVALID_DATE = 5, // 无效日期
    INVALID_WEEKDAY = 6, // 无效星期
    INVALID_INPUT = 7, // 无效输入
    INVALID_WEEKTYPE = 8, // 无效星期类型
    FILE_NOT_EXIST = 9, // 文件不存在
    FESTIVAL_ALREADY_EXIST = 10, // 节日已存在
    FESTIVAL_NOT_EXIST = 11, // 节日不存在
    SHOULDNT_STRETCH_OVER_A_FULL_YEAR = 12, // 不应该跨越整年
    ERROR = 13, // 未知错误
};

using RES = CalendarControllerResult;

// 枚举类型转换为字符串
const string ResString[] = {
    "Success!",
    "Invalid year! Please try again!",
    "Invalid month! Please try again!",
    "Invalid day! Please try again!",
    "Invalid format! Please try again!",
    "Invalid date! Please try again!",
    "Invalid WeekDay! Please try again!",
    "Invalid input! Please try again!",
    "Invalid WeekType! Please try again!",
    "File does not exist! Please try again!",
    "Festival already exists! Please try again!",
    "Festival does not exist! Please try again!",
    "Shouldn't stretch over a full year! Please try again!",
    "Error! Please try again!",
};

// Calendar类，用于表示日历
// 调用六个基本类，实现日历的功能
// 私有成员变量包括文件名，搜索结果
// 公有成员：
// 构造函数，读取文件信息，将节日信息存入m_AllFestival中
// 析构函数，保存文件信息,分别存入两个不同的文件
// AddDateFestival：增加日期节日
// AddWeekDayFestival：增加星期节日
// DelFestival：删除节日
// Reset类函数，修改节日名称与日期
// SearchFestival：查找某一特定节日，返回节日信息在m_FestivalMessage中
// SortFestival：排序节日，返回节日信息在m_FestivalList中
// CountDown：节日倒数日，返回节日信息在m_FestivalCount中
// ShowCalendar：获取某年某月的日历，返回日历信息在m_CalendarList中
// GetError：返回错误信息
// 内嵌类m_Data，用于存储搜索结果
// Set类函数，改变搜索结果
// 常引用，获取搜索结果data
class Calendar 
{
public:
    // 读取文件信息
    Calendar(const string& dateFestivalFileName, const string& weekDayFestivalFileName);
    // 析构，并保存文件信息
    ~Calendar();

    // 增加（分两种不同节日）,删除节日
    RES AddDateFestival(const string& name, const unsigned int month, const unsigned int day, unsigned int year);
    RES AddWeekDayFestival(const string& name, const unsigned int month, const unsigned int weekType, const unsigned int weekDay, unsigned int year);
    RES DelFestival(const string& name);

    // 修改节日名称与日期（分两种不同节日）
    RES ResetDateFestivalName(const string& name, const string& newName);
    RES ResetDateFestivalDate(const string& name, unsigned int newMonth, unsigned int newDay);
    RES ResetDateFestivalStartYear(const string& name, unsigned int newYear);
    RES ResetWeekDayFestivalName(const string& name, const string& newName);
    RES ResetWeekDayFestivalDate(const string& name, unsigned int newMonth, unsigned int newWeekType, unsigned int newWeekDay);
    RES ResetWeekDayFestivalStartYear(const string& name, unsigned int newYear);

    // 查找并排序显示节日
    RES SearchFestival(const string& name);
    RES SearchFestival(const string& name, unsigned int year);
    RES SortFestival(const unsigned int Year1, const unsigned int Month1, const unsigned int Day1, 
        const unsigned int Year2, const unsigned int Month2, const unsigned int Day2, unsigned int sortMethod);

    // 节日倒数日
    RES CountDown(const string& name);
    
    // 获取某年某月的日历
    RES ShowCalendar(const unsigned int year, const unsigned int month);

    // 返回错误信息
    RES GetError(invalid_argument& e) const;

    // 搜索结果
    class m_Data
    {
    public:
        // 构造函数与析构函数
        m_Data() = default;
        ~m_Data() = default;

        // 设置搜索结果
        void SetCalendarList(const vector<string>& calendarList) {m_CalendarList = calendarList;};
        void SetFestivalMessage(const string& festivalMessage) {m_FestivalMessage = festivalMessage;}
        void SetFestivalList(const vector<string>& festivalList) {m_FestivalList = festivalList;}
        void SetFestivalCount(const unsigned int festivalCount) {m_FestivalCount = festivalCount;}

        // 获取搜索结果
        const vector<string>& calendarlist = m_CalendarList;
        const string& festivalmessage = m_FestivalMessage;
        const vector<string>& festivallist = m_FestivalList;
        const unsigned int& festivalcount = m_FestivalCount;
        
    private:
        vector<string> m_CalendarList;
        string m_FestivalMessage;
        vector<string> m_FestivalList;
        unsigned int m_FestivalCount;
    };

    // 改变搜索结果
    void SetCalendarList(const vector<string>& calendarList);
    void SetFestivalMessage(const string& festivalMessage);
    void SetFestivalList(const vector<string>& festivalList);
    void SetFestivalCount(const unsigned int festivalCount);

    // 输出搜索结果
    const m_Data& data = m_Data;

private:
    // 文件名
    string m_DateFestivalFileName;
    string m_WeekDayFestivalFileName;

    // 搜索结果
    m_Data m_Data;

    static unsigned int Month_Day[2][13]; // 每月的天数
    static const string WeekTypeStr[5]; // 星期类型
};

#endif /* Calendar_hpp */