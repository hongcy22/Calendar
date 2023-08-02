//
// sortfestival.h
// 按节日排序界面头文件
// Created by 洪宸宇 on 2023/8/1.
// 添加注释 by 洪宸宇 on 2023/8/2.
//
#ifndef SORTFESTIVAL_H
#define SORTFESTIVAL_H

#include <QWidget>
#include "../../test/CalendarController.hpp"

namespace Ui {
class SortFestival;
}

// 按节日排序界面类
// 继承自QWidget
// 用于按节日排序
// 私有成员：
// Ui::SortFestival *ui：界面指针
// Calendar& m_Controller：日历控制器的引用
// 公有成员：
// 构造函数、析构函数
// 槽函数：
// on_EnterButton_clicked：点击确认按钮
// on_ClearButton_clicked：点击清空按钮
// on_CancelButton_clicked：点击取消按钮
class SortFestival : public QWidget
{
    Q_OBJECT

public:
    explicit SortFestival(Calendar& Controller, QWidget *parent = nullptr);
    ~SortFestival();

private slots:
    void on_EnterButton_clicked();

    void on_ClearButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::SortFestival *ui;
    Calendar& m_Controller;
};

#endif // SORTFESTIVAL_H
