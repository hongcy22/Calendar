//
// Festival.cpp
// Implementation of the Festival class.
// Created by 洪宸宇 on 14/7/2023
// 添加注释 29/7/2023
//

#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <fstream>
#include <iostream> 
#include "Festival.hpp"

using std::string;
using std::vector;
using std::shared_ptr;
using std::invalid_argument;
using std::ostream;
using std::istream;
using std::sort;
using std::ofstream;
using std::ifstream;
using std::endl;

// 初始化两个列表
vector<shared_ptr<Festival>> Festival::m_AllFestival{};
vector<shared_ptr<Festival>> Festival::m_SearchList{};

// 私有构造函数
Festival::Festival(const string& Name)
{
    m_Name = Name;
}

// 私有构造函数
Festival::Festival(const char* Name)
{
    Festival(string(Name));
}

Festival::~Festival(){}

// Add函数，添加节日到m_AllFestival中
// 传入节日名称
// 返回指向该节日的指针
shared_ptr<Festival> Festival::Add(const string& Name)
{
    // 检查是否已经存在该节日, 如果存在则抛出异常
    for (auto& festival : m_AllFestival){
        if (festival->m_Name == Name){
            throw invalid_argument("Festival already exists!");
        }
    }
    m_AllFestival.push_back(shared_ptr<Festival>(new Festival(Name)));
    return m_AllFestival.back();
}

// Add函数，添加节日到m_AllFestival中
// 传入节日名称
// 返回指向该节日的指针
shared_ptr<Festival> Festival::Add(const char* Name)
{
    return Add(string(Name));
}

// Del函数，根据节日名称删除节日
// 传入节日名称
// 返回void
void Festival::Del(const string& Name)
{
    // 检查是否存在该节日, 如果不存在则抛出异常
    for (auto it = m_AllFestival.begin(); it != m_AllFestival.end(); ++it){
        if ((*it)->m_Name == Name){
            (*it).reset();
            m_AllFestival.erase(it);
            return;
        }
    }
    throw invalid_argument("Festival does not exist!");
}

// Del函数，根据节日名称删除节日
// 传入节日名称
// 返回void
void Festival::Del(const char* Name)
{
    Del(string(Name));
}

// Reset函数, 重命名节日
// 传入节日名称和新名称
// 返回void
void Festival::Reset(const string& Name, const string& NewName)
{
    // 根据新名称检查是否已经存在该节日, 如果存在则抛出异常
    for (auto& festival : m_AllFestival){
        if (festival->m_Name == NewName){
            throw invalid_argument("Festival already exists!");
        }
    }
    // 根据名称检查是否存在该节日, 如果不存在则抛出异常
    for (auto& festival : m_AllFestival){
        if (festival->m_Name == Name){
            festival->m_Name = NewName;
            return;
        }
    }
    throw invalid_argument("Festival does not exist!");
}

// Reset函数, 重命名节日
// 传入节日名称和新名称
// 返回void
void Festival::Reset(const char* Name, const char* NewName)
{
    Reset(string(Name), string(NewName));
}

// Reset函数, 重命名节日
// 传入节日新名称
// 返回void
void Festival::Reset(const string& NewName)
{
    Reset(m_Name, NewName);
    return;
}

// Reset函数, 重命名节日
// 传入新名称
// 返回void
void Festival::Reset(const char* NewName)
{
    Reset(string(NewName));
}

// Search函数, 根据节日名称搜索节日
// 传入节日名称
// 返回指向该节日的指针
shared_ptr<Festival> Festival::Search(const string& Name)
{
    // 检查是否存在该节日, 如果不存在则抛出异常
    for (auto& festival : m_AllFestival){
        if (festival->m_Name == Name){
            return festival;
        }
    }
    throw invalid_argument("Festival does not exist!");
}

// Search函数, 根据节日名称搜索节日
// 传入节日名称
// 返回指向该节日的指针
shared_ptr<Festival> Festival::Search(const char* Name)
{
    return Search(string(Name));
}

// SearchList函数, 根据节日名称搜索m_SeachList中的节日
// 传入节日名称
// 返回指向该节日的指针
shared_ptr<Festival> Festival::SearchList(const string& Name)
{
    // 检查m_SeachList是否存在该节日, 如果不存在则抛出异常
    for (auto& festival : m_SearchList){
        if (festival->m_Name == Name){
            return festival;
        }
    }
    throw invalid_argument("Festival does not exist!");
}

// 重载==运算符
// 传入节日
// 返回bool
bool Festival::operator==(const Festival& Source) const
{
    return m_Name == Source.m_Name;
}

// 重载==运算符
// 传入节日名称
// 返回bool
bool Festival::operator==(const string& Name) const
{
    return m_Name == Name;
}

// 重载==运算符
// 传入节日名称
// 返回bool
bool Festival::operator==(const char* Name) const
{
    return m_Name == string(Name);
}

// 重载!=运算符
// 传入节日
// 返回bool
bool Festival::operator!=(const Festival& Source) const
{
    return m_Name != Source.m_Name;
}

// 重载!=运算符
// 传入节日名称
// 返回bool
bool Festival::operator!=(const string& Name) const
{
    return m_Name != Name;
}

// 重载!=运算符
// 传入节日名称
// 返回bool
bool Festival::operator!=(const char* Name) const
{
    return m_Name != string(Name);
}

// 重载<运算符
// 传入节日
// 返回bool
bool Festival::operator<(const Festival& Source) const
{
    return m_Name < Source.m_Name;
}

// 重载>运算符
// 传入节日名称
// 返回bool
bool Festival::operator>(const Festival& Source) const
{
    return m_Name > Source.m_Name;
}

// 重载<=运算符
// 传入节日名称
// 返回bool
bool Festival::operator<=(const Festival& Source) const
{
    return m_Name <= Source.m_Name;
}

// 重载>=运算符
// 传入节日名称
// 返回bool
bool Festival::operator>=(const Festival& Source) const
{
    return m_Name >= Source.m_Name;
}

// 重载<<运算符
// 传入输出流和节日
// 返回输出流
ostream& operator<<(ostream& os, const Festival& Source)
{
    os << Source.m_Name;
    return os;
}

// SortUp函数, 按照字典序升序排序
void Festival::SortUp()
{
    // 使用lambda表达式作为比较函数
    sort(m_AllFestival.begin(), m_AllFestival.end(), 
    [](shared_ptr<Festival> a, shared_ptr<Festival> b) { return *a < *b; });
}

// SortDown函数, 按照字典序降序排序
void Festival::SortDown()
{
    // 使用lambda表达式作为比较函数
    sort(m_AllFestival.begin(), m_AllFestival.end(), 
    [](shared_ptr<Festival> a, shared_ptr<Festival> b) { return *a > *b; });
}

// ReadFromFile函数
// 从指定文件中读取节日信息，存入m_AllFestival中
// 传入文件名
// 返回void
void Festival::ReadFromFile(const string& FileName){
    ifstream fin(FileName);
    if (!fin.is_open())
    {
        throw invalid_argument("File does not exist!");
    }
    string Name;
    while (getline(fin, Name)){
        Add(Name);
    }
    fin.close();
}

// WriteToFile函数
// 将m_AllFestival中的节日信息写入指定文件
// 传入文件名
// 返回void
void Festival::WriteToFile(const string& FileName){
    ofstream fout(FileName);
    if (!fout.is_open())
    {
        throw invalid_argument("File does not exist!");
    }
    for (auto& festival : m_AllFestival){
        fout << festival->m_Name << endl;
    }
    fout.close();
}

// ClearSearchList函数
// 清空m_SearchList
// 传入m_SearchList类型的列表
void Festival::ClearSearchList(vector<shared_ptr<Festival>>& SearchList)
{
    SearchList.clear();
    return;
}

// ClearSearchList函数
// 清空m_SearchList
void Festival::ClearSearchList()
{
    m_SearchList.clear();
    return;
}

// IsEmpty函数
// 判断m_SearchList是否为空
// 返回bool
bool Festival::IsEmpty()
{
    return m_SearchList.empty();
}

// ShowAllFestival函数
// 返回m_AllFestival中的所有节日名称
vector<string> Festival::ShowAllFestival()
{
    vector<string> result;
    for (auto& festival : m_AllFestival)
    {
        result.push_back(festival->name);
    }
    return result;
}

// ShowSearchList函数
// 返回m_SearchList中的所有节日名称
vector<string> Festival::ShowSearchList()
{
    vector<string> result;
    for (auto& festival : m_SearchList)
    {
        result.push_back(festival->name);
    }
    return result;
}
