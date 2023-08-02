//
// Festival.hpp
// Declaration of the Festival class.
// Created by 洪宸宇 on 14/7/2023
// 添加注释 29/7/2023
//

#ifndef Festival_hpp
#define Festival_hpp

#include <string>
#include <vector>
#include <memory>

using std::string;
using std::vector;
using std::shared_ptr;
using std::ostream;
using std::istream;

// Festival类，用于表示节日名称
// 该类的对象不可拷贝和赋值
// 不能直接创建对象，只能Add到列表中
// 不能添加两个相同名字的日期
// 根据不同条件搜索得到的节日会被保存在m_SearchList中
// 有两种类型的节日，一种是DateFestival，一种是WeekDayFestival
// DateFestival是指在某个日期的节日，WeekDayFestival是指在某个星期几的节日
// 私有成员：
// m_Name: 节日名称
// m_FestivalKind: 节日类型,"1"为DateFestival,"2"为WeekDayFestival
// m_AllFestival: 保存所有节日的指针
// m_SearchList: 保存所有符合搜索条件的节日
// 公有成员：
// Add\Del: 增加或根据条件删除节日
// Reset: 修改节日名称、寻找指定节日
// Search: 寻找指定节日
// 重载比较运算符:==,!=,<,>,<=,>=
// 重载输出运算符:<<
// SortUp\SortDown: 把储存的节日按名称升序或降序排序
// ReadFromFile\WriteToFile: 从指定文件读取节日信息或把节日信息写入文件
// ClearSearchList: 清空搜索列表
// IsEmpty: 判断搜索列表是否为空
// ShowAllFestival: 显示所有节日
// ShowSearchList: 显示搜索列表
// 常引用参数：
// name: 节日名称
// festivalkind: 节日类型
class Festival 
{
public:
    // 禁止拷贝构造和赋值
    Festival(const Festival& Source) = delete;
    Festival& operator=(const Festival& Source) = delete;
    // 虚析构函数
    virtual ~Festival();

    // 增加或根据条件删除节日
    static shared_ptr<Festival> Add(const string& Name);
    static shared_ptr<Festival> Add(const char* Name);
    static void Del(const string& Name);
    static void Del(const char* Name);

    // 修改节日名称、寻找指定节日
    void Reset(const string& NewName);
    void Reset(const char* NewName);
    static void Reset(const string& Name, const string& NewName);
    static void Reset(const char* Name, const char* NewName);
    static shared_ptr<Festival> Search(const string& Name);
    static shared_ptr<Festival> Search(const char* Name);
    static shared_ptr<Festival> SearchList(const string& Name); // 在搜索列表中寻找

    // 重载比较运算符，按名称比较
    bool operator==(const Festival& Source) const;
    bool operator==(const string& Name) const;
    bool operator==(const char* Name) const;
    bool operator!=(const Festival& Source) const;
    bool operator!=(const string& Name) const;
    bool operator!=(const char* Name) const;
    bool operator<(const Festival& Source) const;
    bool operator>(const Festival& Source) const;
    bool operator<=(const Festival& Source) const;
    bool operator>=(const Festival& Source) const;

    // 重载输出运算符
    friend ostream& operator<<(ostream& os, const Festival& Source);

    // 把储存的节日按名称升序排序
    static void SortUp();

    // 把储存的节日按名称降序排序
    static void SortDown();

    // 从指定文件读取节日信息
    static void ReadFromFile(const string& FileName);

    // 把节日信息写入文件
    static void WriteToFile(const string& FileName);

    // 清空搜索列表
    static void ClearSearchList(vector<shared_ptr<Festival>>& SearchList);
    static void ClearSearchList();

    // 显示列表中有无节日
    static bool IsEmpty();

    // 显示列表中的所有节日
    static vector<string> ShowAllFestival();
    static vector<string> ShowSearchList();

    // 直接获取节日信息
    const string& name = m_Name;
    const int& festivalKind = m_FestivalKind;

protected:
    // 保存所有节日的指针,智能指针
    static vector<shared_ptr<Festival>> m_AllFestival;
    // 构造函数
    Festival(const string& Name);
    Festival(const char* Name);
    // 存储所有符合搜索条件的节日,智能指针
    static vector<shared_ptr<Festival>> m_SearchList;    
    // 节日类型,"1"为DateFestival,"2"为WeekDayFestival
    int m_FestivalKind;

private:
    string m_Name;

};

#endif /* Festival_hpp */