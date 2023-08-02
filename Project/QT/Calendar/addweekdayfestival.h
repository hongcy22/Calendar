//
// addweekdayfestival.h
// 添加星期节日界面函数说明
// Created by 洪宸宇 on 2023/7/31.
// 添加注释 by 洪宸宇 on 2023/8/2.
//
#ifndef ADDWEEKDAYFESTIVAL_H
#define ADDWEEKDAYFESTIVAL_H

#include <QWidget>
#include "../../test/CalendarController.hpp"

namespace Ui {
class AddWeekDayFestival;
}

// 添加星期节日界面类
// 用于控制添加星期节日界面的显示
// 通过调用Calendar类的函数来实现功能
// 私有成员：
// Calendar& m_Controller：Calendar类的引用
// 公有成员：
// 构造函数、析构函数
// 槽函数：
// on_EnterButton_clicked：点击确认按钮
// on_ClearButton_clicked：点击清空按钮
// on_CancelButton_clicked：点击取消按钮
class AddWeekDayFestival : public QWidget
{
    Q_OBJECT

public:
    explicit AddWeekDayFestival(Calendar& Controller, QWidget *parent = nullptr);
    ~AddWeekDayFestival();

private slots:
    void on_EnterButton_clicked();

    void on_ClearButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::AddWeekDayFestival *ui;
    Calendar& m_Controller;
};

#endif // ADDWEEKDAYFESTIVAL_H
