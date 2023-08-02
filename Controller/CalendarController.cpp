//
// CalendarController.cpp
// Implementation of the Calendar class.
// Created by 洪宸宇 on 14/7/2023
// 添加注释 14/7/2023
//

#include "CalendarController.hpp"
#include <algorithm>
#include <string>
#include <fstream>

using namespace std;

unsigned int Calendar::Month_Day[2][13] = {
    {0,31,28,31,30,31,30,31,31,30,31,30,31},
    {0,31,29,31,30,31,30,31,31,30,31,30,31}
};

const string Calendar::WeekTypeStr[5] = { "Last", "First", "Second", "Third", "Fourth" };

// 构造函数，从文件中读取节日信息
// 传入两个文件名
// 一个是DateFestival的文件名
// 一个是WeekDayFestival的文件名
Calendar::Calendar(const string& dateFestivalFileName, const string& weekDayFestivalFileName)
{
    m_DateFestivalFileName = dateFestivalFileName;
    m_WeekDayFestivalFileName = weekDayFestivalFileName;
    DateFestival::ReadFromFile(dateFestivalFileName);
    WeekDayFestival::ReadFromFile(weekDayFestivalFileName);
}

// 析构函数，将节日信息写入文件
Calendar::~Calendar()
{
    ofstream fout1((m_DateFestivalFileName));
    ofstream fout2(m_WeekDayFestivalFileName);
    auto namelist = DateFestival::ShowAllFestival();
    // 先获取名称对应的指针，再根据指针判断是哪种类型的节日
    for (auto& name : namelist)
    {
        FesPtr ptr = Festival::Search(name);
        // 1为DateFestival，2为WeekDayFestival
        // 按照对应类的格式写入文件
        if (ptr->festivalKind == 1)
        {
            fout1 << static_cast<DateFestival*> (ptr.get())->name << ": " 
            << static_cast<DateFestival*> (ptr.get())->date.month.value << " " 
            << static_cast<DateFestival*> (ptr.get())->date.day << " " 
            << static_cast<DateFestival*> (ptr.get())->date.year << endl;
        }
        else
        {
            fout2 << ptr->name << ": the " 
            << WeekTypeStr[static_cast<int> (static_cast<WeekDayFestival*> (ptr.get())->weektype)] 
            << " " << static_cast<WeekDayFestival*> (ptr.get())->weekday.weekday 
            << " of " << static_cast<WeekDayFestival*> (ptr.get())->month.month
            << " " << static_cast<WeekDayFestival*> (ptr.get())->startyear << endl;
        }
    }
    fout1.close();
    fout2.close();
}

// AddDateFestival函数
// 传入节日名称，月份，日期，年份
// 调用DateFestival的Add函数
// 返回值为RES枚举类型
RES Calendar::AddDateFestival(const string& name, const unsigned int month, const unsigned int day, unsigned int year)
{
    // 尝试能否添加，如果不能则返回错误类型
    try
    {
        DateFestival::Add(name, month, day, year);
    }
    catch (invalid_argument e)
    {
        return GetError(e);
    }
    return RES::SUCCESS;
}

// AddWeekDayFestival函数
// 传入节日名称，月份，星期类型，星期，年份
// 调用WeekDayFestival的Add函数
// 返回值为RES枚举类型
RES Calendar::AddWeekDayFestival(const string& name, const unsigned int month, const unsigned int weekType, const unsigned int weekDay, unsigned int year)
{
    // 尝试能否添加，如果不能则返回错误类型
    try
    {
        WeekDayFestival::Add(name, month, weekType, weekDay, year);
    }
    catch (invalid_argument e)
    {
        return GetError(e);
    }
    return RES::SUCCESS;
}

// DelFestival函数
// 根据名称调用相应类的Del函数
// 传入节日名称
// 返回值为RES枚举类型
RES Calendar::DelFestival(const string& name)
{
    FesPtr ptr;
    // 先尝试用Search函数获取名称对应的指针
    // 如果没有找到则返回错误类型
    try
    {
        ptr = Festival::Search(name);
    }
    catch(invalid_argument e)
    {
        if (e.what() == string("Festival does not exist!")) {
            return RES::FESTIVAL_NOT_EXIST;
        }
        else {
            return RES::ERROR;
        }
    }
    // 1为DateFestival，2为WeekDayFestival
    // 按照对应类的Del函数删除
    if (ptr->festivalKind == 1)
    {
        try
        {
            DateFestival::Del(name);
        }
        catch (invalid_argument e)
        {
            return GetError(e);
        }
    }
    else
    {
        try
        {
            WeekDayFestival::Del(name);
        }
        catch (invalid_argument e)
        {
            return GetError(e);
        }
    }
    return RES::SUCCESS;
}

// ResetDateFestivalName函数
// 传入节日名称，新名称
// 调用DateFestival的ResetName函数
// 返回值为RES枚举类型
RES Calendar::ResetDateFestivalName(const string& name, const string& newName)
{
    // 尝试改变名称，如果不能则返回错误类型
    try
    {
        DateFestival::ResetName(name, newName);
    }
    catch(invalid_argument e)
    {
        return GetError(e);
    }
    return RES::SUCCESS;
}

// ResetWeekDayFestivalMonth函数
// 传入节日名称，新月份
// 调用WeekDayFestival的ResetMonth函数
// 返回值为RES枚举类型
RES Calendar::ResetDateFestivalDate(const string& name, unsigned int newMonth, unsigned int newDay)
{
    // 尝试改变日期，如果不能则返回错误类型
    try
    {
        DateFestival::ResetDate(name, newMonth, newDay);
    }
    catch(invalid_argument e)
    {
        return GetError(e);
    }
    return RES::SUCCESS;
}

// ResetDateFestivalStartYear函数
// 传入节日名称，新年份
// 调用DateFestival的ResetYear函数
// 返回值为RES枚举类型
RES Calendar::ResetDateFestivalStartYear(const string& name, unsigned int newYear)
{
    // 尝试改变年份，如果不能则返回错误类型
    try
    {
        DateFestival::ResetYear(name, newYear);
    }
    catch(invalid_argument e)
    {
        return GetError(e);
    }
    return RES::SUCCESS;
}

// ResetWeekDayFestivalName函数
// 传入节日名称，新名称
// 调用WeekDayFestival的ResetName函数
// 返回值为RES枚举类型
RES Calendar::ResetWeekDayFestivalName(const string& name, const string& newName)
{
    // 尝试改变名称，如果不能则返回错误类型
    try
    {
        WeekDayFestival::ResetName(name, newName);
    }
    catch(invalid_argument e)
    {
        return GetError(e);
    }
    return RES::SUCCESS;
}

// ResetWeekDayFestivalMonth函数
// 传入节日名称，新月份
// 调用WeekDayFestival的ResetMonth函数
// 返回值为RES枚举类型
RES Calendar::ResetWeekDayFestivalDate(const string& name, unsigned int newMonth, unsigned int newWeekType, unsigned int newWeekDay)
{
    // 尝试改变日期，如果不能则返回错误类型
    try
    {
        WeekDayFestival::ResetDate(name, newMonth, newWeekType, newWeekDay);
    }
    catch(invalid_argument e)
    {
        return GetError(e);
    }
    return RES::SUCCESS;
}

// ResetWeekDayFestivalStartYear函数
// 传入节日名称，新年份
// 调用WeekDayFestival的ResetStartYear函数
// 返回值为RES枚举类型
RES Calendar::ResetWeekDayFestivalStartYear(const string& name, unsigned int newYear)
{
    // 尝试改变年份，如果不能则返回错误类型
    try
    {
        WeekDayFestival::ResetStartYear(name, newYear);
    }
    catch(invalid_argument e)
    {
        return GetError(e);
    }
    return RES::SUCCESS;
}

// SearchFestival函数
// 传入节日名称
// 返回值为RES枚举类型
RES Calendar::SearchFestival(const string& name)
{
    // 尝试用Search函数获取名称对应的指针
    // 如果没有找到则返回错误类型
    FesPtr ptr;
    try
    {
        ptr = Festival::Search(name);
    }
    catch(invalid_argument e)
    {
        if (e.what() == string("Festival does not exist!")) {
            return RES::FESTIVAL_NOT_EXIST;
        }
        else {
            return RES::ERROR;
        }
    }
    // 1为DateFestival，2为WeekDayFestival
    // 按照对应类的ToString函数获取信息
    if (ptr->festivalKind == 1)
    {
        m_Data.SetFestivalMessage(DateFestival::ToString(*static_cast<DateFestival*>(ptr.get())) + " " + to_string(static_cast<DateFestival*>(ptr.get())->date.year));
    }
    else
    {
        m_Data.SetFestivalMessage(WeekDayFestival::ToString(*static_cast<WeekDayFestival*>(ptr.get())) + " " + to_string(static_cast<WeekDayFestival*>(ptr.get())->startyear));
    }
    return RES::SUCCESS;
}

// SearchFestival函数
// 传入节日名称
// 返回值为RES枚举类型
RES Calendar::SearchFestival(const string& name, unsigned int year)
{
    // 尝试用Search函数获取名称对应的指针
    // 如果没有找到则返回错误类型
    FesPtr ptr;
    try
    {
        ptr = Festival::Search(name);
    }
    catch(invalid_argument e)
    {
        if (e.what() == string("Festival does not exist!")) {
            return RES::FESTIVAL_NOT_EXIST;
        }
        else {
            return RES::ERROR;
        }
    }
    // 1为DateFestival，2为WeekDayFestival
    // 按照对应类的ToString函数获取信息
    if (ptr->festivalKind == 1)
    {
        m_Data.SetFestivalMessage(DateFestival::ToString(*static_cast<DateFestival*>(ptr.get())) + " " + to_string(year));
    }
    else
    {
        Date temp = WeekDayFestival::WeekDayToDate(static_cast<WeekDayFestival*>(ptr.get())->month, 
            static_cast<WeekDayFestival*>(ptr.get())->weektype, static_cast<WeekDayFestival*>(ptr.get())->weekday, year);
        m_Data.SetFestivalMessage(name + " " + temp.ToString());
    }
    return RES::SUCCESS;
}

// SortFestival函数
// 传入两个日期，排序方式
// 返回值为RES枚举类型
RES Calendar::SortFestival(const unsigned int Year1, const unsigned int Month1, const unsigned int Day1, 
    const unsigned int Year2,const unsigned int Month2, const unsigned int Day2, unsigned int sortMethod)
{
    // 检查日期是否合法,如果不合法则返回错误类型
    Date Date1(1900, 1, 1);
    Date Date2(1900, 1, 1);
    try
    {
        Date1.SetDate(Year1, Month1, Day1);
    }
    catch(invalid_argument e)
    {
        return GetError(e);
    }
    try
    {
        Date2.SetDate(Year2, Month2, Day2);
    }
    catch(invalid_argument e)
    {
        return GetError(e);
    }
    // 检查两个日期是否超过一年,如果超过则返回错误类型
    if (Date::IsFullYear(Date1, Date2))
    {
        return RES::SHOULDNT_STRETCH_OVER_A_FULL_YEAR;
    }

    // 搜索
    // 清空搜索列表
    Festival::ClearSearchList();
    // 遍历搜索列表中的每一个名称
    auto namelist = Festival::ShowAllFestival();
    for (auto& name : namelist)
    {
        // 利用Search函数获取指针
        FesPtr ptr = Festival::Search(name);
        // 如果是DateFestival
        if (ptr->festivalKind == 1)
        {
            unsigned int ayear = static_cast<DateFestival*> (ptr.get())->date.year;
            Month amonth = static_cast<DateFestival*> (ptr.get())->date.month;
            unsigned int aday = static_cast<DateFestival*> (ptr.get())->date.day;
            // 单独讨论2月29日的情况
            if (amonth == 2 && aday == 29)
            {
                bool flag = false;
                Date Return_date(1900, 1, 1);
                // 如果两年中有一年是闰年，且该年的2月29日在两个日期之间
                if (Date1.IsLeapYear() && Date(Date1.year, 2, 29) >= Date1 
                    && Date(Date1.year, 2, 29) <= Date2 && ayear <= Date1.year)
                {
                    Return_date.SetDate(Date1.year, 2, 29);
                    flag = true;
                }
                if (Date2.IsLeapYear() && Date(Date2.year, 2, 29) <= Date2 
                    && Date(Date2.year, 2, 29) >= Date1 && ayear <= Date2.year)
                {
                    Return_date.SetDate(Date2.year, 2, 29);
                    flag = true;
                }
                if (flag)
                {
                    DateFestival::ListAdd(name, Return_date);
                }
            }
            // 如果不是2月29日
            else
            {
                if (Date(Date1.year, amonth, aday) >= Date1 
                    && Date(Date1.year, amonth, aday) <= Date2 && ayear <= Date1.year)
                {
                    DateFestival::ListAdd(name, Date(Date1.year, amonth, aday));
                }
                // 确保不会重复添加
                if (Date(Date2.year, amonth, aday) <= Date2 
                    && Date(Date2.year, amonth, aday) >= Date1 && ayear <= Date2.year && Date2.year != Date1.year)
                {
                    DateFestival::ListAdd(name, Date(Date2.year, amonth, aday));
                }
            }
        }
        // 如果是WeekDayFestival
        else
        {
            // 分别获得星期在这两年对应的日期
            Date temp = WeekDayFestival::WeekDayToDate(static_cast<WeekDayFestival*> (ptr.get())->month, 
                static_cast<WeekDayFestival*> (ptr.get())->weektype, 
                static_cast<WeekDayFestival*> (ptr.get())->weekday, Date1.year);
            unsigned int ayear = static_cast<WeekDayFestival*> (ptr.get())->startyear;
            if (temp >= Date1 && temp <= Date2 && ayear <= Date1.year)
            {
                DateFestival::ListAdd(name, temp);
            }
            // 确保不会重复添加
            temp = WeekDayFestival::WeekDayToDate(static_cast<WeekDayFestival*> (ptr.get())->month, 
                static_cast<WeekDayFestival*> (ptr.get())->weektype, 
                static_cast<WeekDayFestival*> (ptr.get())->weekday, Date2.year);
            if (temp <= Date2 && temp >= Date1 && ayear <= Date2.year && Date2.year != Date1.year)
            {
                DateFestival::ListAdd(name, temp);
            }
        }
    }
    // 如果搜索列表为空，则返回错误类型
    if (Festival::IsEmpty())
    {
        return RES::FESTIVAL_NOT_EXIST;
    }
    
    // 排序：1.按名称升序 2.按名称降序 3.按日期升序 4.按日期降序
    // 获取搜索列表
    // 利用lambda表达式进行排序
    namelist = Festival::ShowSearchList();
    switch (sortMethod)
    {
        case 1:
            sort(namelist.begin(), namelist.end(),
            [](const string& a, const string& b) -> bool
            {
                return a < b;
            });
            break;
        case 2:
            sort(namelist.begin(), namelist.end(),
            [](const string& a, const string& b) -> bool
            {
                return a > b;
            });
            break;
        case 3:
            sort(namelist.begin(), namelist.end(),
            [](const string& a, const string& b) -> bool
            {
                Date date1 = static_cast<DateFestival*> (Festival::SearchList(a).get())->date;
                Date date2 = static_cast<DateFestival*> (Festival::SearchList(b).get())->date;
                return date1 < date2;
            });
            break;
        case 4:
            sort(namelist.begin(), namelist.end(),
            [](const string& a, const string& b) -> bool
            {
                Date date1 = static_cast<DateFestival*> (Festival::SearchList(a).get())->date;
                Date date2 = static_cast<DateFestival*> (Festival::SearchList(b).get())->date;
                return date1 > date2;
            });
            break;
        default:
            return RES::ERROR;
    }
    // 添加节日
    // 分开添加，储存到m_FestivalList中
    vector<string> result;
    string fes = "";
    for (auto& name : namelist)
    {
        fes.clear();
        fes += name + ": " + static_cast<DateFestival*> (Festival::SearchList(name).get())->date.ToString();
        result.push_back(fes);
    }
    SetFestivalList(result); 
    return RES::SUCCESS;
}

// CountDown函数
// 计算两个日期之间的天数，储存到m_FestivalCount中
// 传入节日名称
// 返回值为RES类型
RES Calendar::CountDown(const string& name)
{
    // 利用名称获得节日指针
    // 如果节日不存在，则返回错误类型
    FesPtr ptr;
    try
    {
        ptr = Festival::Search(name);
    }
    catch(invalid_argument e)
    {
        if (e.what() == string("Festival does not exist!")) {
            return RES::FESTIVAL_NOT_EXIST;
        }
        else {
            return RES::ERROR;
        }
    }
    // 如果是DateFestival
    if (ptr->festivalKind == 1)
    {
        // 如果是2月29日的节日
        if (static_cast<DateFestival*>(ptr.get())->date.month == 2 && static_cast<DateFestival*>(ptr.get())->date.day == 29)
        {
            // 如果今年是闰年
            // 判断是否已经过了今年的节日
            if (Date::IsLeapYear(Date::Now().year))
            {
                Date date(Date::Now().year, static_cast<DateFestival*>(ptr.get())->date.month, static_cast<DateFestival*>(ptr.get())->date.day);
                // 如果已经过了今年的节日，则计算下一次节日的天数
                if (date < Date::Now())
                {
                    date.SetDate(Date::Now().year + 4, 2, 29);
                }
                m_Data.SetFestivalCount(date - Date::Now());
            }
            // 如果今年不是闰年
            // 找到最近的闰年，计算下一次节日的天数
            else
            {
                for (unsigned int i = Date::Now().year + 1; i < Date::Now().year + 4; i++)
                {
                    if (Date::IsLeapYear(i))
                    {
                        m_Data.SetFestivalCount(Date(i, 2, 29) - Date::Now());
                        break;
                    }
                }
            }
        }
        // 如果不是2月29日的节日
        else
        {
            Date date(Date::Now().year, static_cast<DateFestival*>(ptr.get())->date.month, static_cast<DateFestival*>(ptr.get())->date.day);
            // 如果已经过了今年的节日，则计算下一次节日的天数
            if (date < Date::Now())
            {
                date.SetYear(Date::Now().year + 1);
            }
            m_Data.SetFestivalCount(date - Date::Now());
        }
    }
    // 如果是WeekDayFestival
    else
    {
        // 比较时需要转化为日期
        Date date = WeekDayFestival::WeekDayToDate(static_cast<WeekDayFestival*>(ptr.get())->month, 
            static_cast<WeekDayFestival*>(ptr.get())->weektype, 
            static_cast<WeekDayFestival*>(ptr.get())->weekday, Date::Now().year);
        // 如果已经过了今年的节日，则计算下一次节日的天数
        if (date < Date::Now())
        {
            date = WeekDayFestival::WeekDayToDate(static_cast<WeekDayFestival*>(ptr.get())->month, 
            static_cast<WeekDayFestival*>(ptr.get())->weektype, 
            static_cast<WeekDayFestival*>(ptr.get())->weekday, Date::Now().year + 1);
        }
        m_Data.SetFestivalCount(date - Date::Now());
    }
    return RES::SUCCESS;
}

// ShowCalendar函数
// 输出某个月的日历
// 传入年份和月份
// 返回值为RES类型
RES Calendar::ShowCalendar(const unsigned int year, const unsigned int month)
{
    // 判断年份和月份是否合法，不合法则返回错误类型
    if (year < 1900 || year > 9999)
    {
        return RES::INVALID_YEAR;
    }
    if (month < 1 || month > 12)
    {
        return RES::INVALID_MONTH;
    }
    vector<string> result = {};
    string fes = "";
    // 储存日期信息
    Date date(year, month, 1);
    fes += to_string(date.ToWeekDay()) + " " + to_string(Month_Day[Date::IsLeapYear(year)][month]);
    result.push_back(fes);

    // 节日
    // 搜索符合条件的节日
    Festival::ClearSearchList();
    // 遍历搜索列表，找到符合条件的节日
    auto namelist = Festival::ShowAllFestival();
    for (auto& name : namelist)
    {
        // 根据名称得到指针
        FesPtr ptr = Festival::Search(name);
        // 如果是DateFestival
        if (ptr->festivalKind == 1)
        {
            unsigned int ayear = static_cast<DateFestival*> (ptr.get())->date.year;
            Month amonth = static_cast<DateFestival*> (ptr.get())->date.month;
            unsigned int aday = static_cast<DateFestival*> (ptr.get())->date.day;
            // 如果是2月29日的节日，需要判断是否是闰年
            if (amonth == 2 && aday == 29)
            {
                if (ayear <= year && Date::IsLeapYear(ayear) && month == amonth)
                {
                    DateFestival::ListAdd(name, Date(year, amonth, aday));
                }
            }
            // 如果不是2月29日的节日,直接判断日期是否符合
            else
            {
                if (ayear <= year && month == amonth)
                {
                    DateFestival::ListAdd(name, Date(year, amonth, aday));
                }
            }
        }
        // 如果是WeekDayFestival
        else
        {
            // 根据年份计算日期,再判断日期是否符合
            Date temp = WeekDayFestival::WeekDayToDate(static_cast<WeekDayFestival*> (ptr.get())->month, 
                static_cast<WeekDayFestival*> (ptr.get())->weektype, 
                static_cast<WeekDayFestival*> (ptr.get())->weekday, year);
            unsigned int ayear = static_cast<WeekDayFestival*> (ptr.get())->startyear;
            if (temp.month == month && ayear <= year)
            {
                DateFestival::ListAdd(name, temp);
            }
        }
    }
    // 如果搜索列表为空，返回错误类型
    if (Festival::IsEmpty())
    {
        return RES::FESTIVAL_NOT_EXIST;
    }
    // 添加节日
    namelist = Festival::ShowSearchList();
    fes.clear();
    fes = "Festivals:";
    result.push_back(fes);
    for (auto& name : namelist)
    {
        fes.clear();
        fes += name + ": " + static_cast<DateFestival*> (Festival::SearchList(name).get())->date.ToString();
        result.push_back(fes);
    }

    // 按照一定格式，储存到m_CalendarList中
    SetCalendarList(result);
    return RES::SUCCESS;
}

// GetError函数
// 根据异常类，建立错误类型和异常类的映射
// 传入异常类
// 返回值为RES类型
RES Calendar::GetError(invalid_argument& e) const
{
    if (e.what() == string("Invalid year!")) {
        return RES::INVALID_YEAR;
    }
    else if (e.what() == string("Invalid month!")) {
        return RES::INVALID_MONTH;
    }
    else if (e.what() == string("Invalid day!")) {
        return RES::INVALID_DAY;
    }
    else if (e.what() == string("Invalid format!")) {
        return RES::INVALID_FORMAT;
    }
    else if (e.what() == string("Invalid date!")) {
        return RES::INVALID_DATE;
    }
    else if (e.what() == string("Invalid WeekDay!")) {
        return RES::INVALID_WEEKDAY;
    }
    else if (e.what() == string("Invalid input!")) {
        return RES::INVALID_INPUT;
    }
    else if (e.what() == string("Invalid WeekType!")) {
        return RES::INVALID_WEEKTYPE;
    }
    else if (e.what() == string("File does not exist!")) {
        return RES::FILE_NOT_EXIST;
    }
    else if (e.what() == string("Festival already exists!")) {
        return RES::FESTIVAL_ALREADY_EXIST;
    }
    else if (e.what() == string("Festival does not exist!")) {
        return RES::FESTIVAL_NOT_EXIST;
    }
    else if (e.what() == string("Shouldn't stretch over a full year!")) {
        return RES::SHOULDNT_STRETCH_OVER_A_FULL_YEAR;
    }
    else {
        return RES::ERROR;
    }
}

// SetCalendarList函数
// 将日历字符串储存到m_CalendarList中
// 传入string类型的日历字符串
// 返回值为void
void Calendar::SetCalendarList(const vector<string>& calendarList)
{
    m_Data.SetCalendarList(calendarList);
}

// SetFestivalList函数
// 将节日列表储存到m_FestivalList中
// 传入string类型的节日列表
// 返回值为void
void Calendar::SetFestivalList(const vector<string>& festivalList)
{
    m_Data.SetFestivalList(festivalList);
}

// SetFestivalMessage函数
// 将节日信息储存到m_FestivalMessage中
// 传入string类型的节日信息
// 返回值为void
void Calendar::SetFestivalMessage(const string& festivalMessage)
{
    m_Data.SetFestivalMessage(festivalMessage);
}

// SetFestivalCount函数
// 将节日倒数日储存到m_FestivalCount中
// 传入unsigned int类型的节日倒数日
// 返回值为void
void Calendar::SetFestivalCount(const unsigned int festivalCount)
{
    m_Data.SetFestivalCount(festivalCount);
}