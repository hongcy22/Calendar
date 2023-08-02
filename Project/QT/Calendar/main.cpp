//
// main.cpp
// 控制主界面
// Created by 洪宸宇 on 2023/7/31.
// 添加注释 by 洪宸宇 on 2023/8/2.
//

#include "mainwindow.h"
#include <QApplication>
#include <QString>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 建立一个Calendar对象
    Calendar controller("D:\\VScode\\cpp(code_runner)\\test\\DateFestival.txt", "D:\\VScode\\cpp(code_runner)\\test\\WeekDayFestival.txt");

    // 开启主界面
    MainWindow w(controller);
    w.show();
    return a.exec();
}
