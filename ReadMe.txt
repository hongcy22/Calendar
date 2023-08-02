-Model中包含了所有的底层类：
```
    Month类：建立月份单词与月份数字的对应关系
    WeekDay类：建立星期单词与星期数字的对应关系
    Date类：建立日期的类，包含了年、月、日等信息
    Festival类：建立节日的类，包含了节日的名称
    DateFestival类：建立日期与节日的对应关系
    WeekDayFestival类：建立星期与节日的对应关系
```
-Data中包含的是用于测试的节日信息：
```
    DateFestival.txt：储存日期节日的信息
    WeekDayFestival.txt：储存星期节日的信息
```
-Controller中包含了控制器类：Calendar类
-Project中是命令行类和实现的可执行文件：
```
    CommandLine：命令行类，用于测试 main.cpp
    QT: 可视化界面（需要修改文件路径）
        Calendar: 可视化界面的所有类、主函数、项目文件
        photo: 可视化界面的所有图片
        Calendar.exe: 可执行文件
```
-开发环境版本说明：(vscode配置参见vscode.code-profile)
```
    开发环境：Windows 11
    开发工具：Visual Studio Code 1.80.2(user setup)
             Qt Creator 11.0.0 (Community)
    编译器：g++ (MinGW.org GCC-6.3.0-1) 6.3.0
           QT 6.2.4 (MinGW, 64 bit)
    开发语言：C++
```