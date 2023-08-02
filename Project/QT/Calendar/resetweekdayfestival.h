//
// resetweekdayfestival.h
// 重置周节日界面头文件
// Created by 洪宸宇 on 2023/8/1.
// 添加注释 by 洪宸宇 on 2023/8/2.
//
#ifndef RESETWEEKDAYFESTIVAL_H
#define RESETWEEKDAYFESTIVAL_H

#include <QWidget>
#include "../../test/CalendarController.hpp"

namespace Ui {
class ResetWeekDayFestival;
}

// 重置周节日界面类
// 继承自QWidget
// 用于重置周节日
// 私有成员：
// Ui::ResetWeekDayFestival *ui：界面指针
// Calendar& m_Controller：Calendar类的引用
// 公有成员：
// 构造函数、析构函数
// 槽函数：
// on_ResetButton_1_clicked：点击名称重置按钮
// on_ClearButton_1_clicked：点击名称清空按钮
// on_ResetButton_2_clicked：点击星期重置按钮
// on_ClearButton_2_clicked：点击星期清空按钮
// on_ResetButton_3_clicked：点击起始年份重置按钮
// on_ClearButton_3_clicked：点击起始年份清空按钮
// on_CancelButton_clicked：点击取消按钮
class ResetWeekDayFestival : public QWidget
{
    Q_OBJECT

public:
    explicit ResetWeekDayFestival(Calendar& Controller, QWidget *parent = nullptr);
    ~ResetWeekDayFestival();

private slots:

    void on_ResetButton_1_clicked();

    void on_ClearButton_1_clicked();

    void on_ResetButton_2_clicked();

    void on_ClearButton_2_clicked();

    void on_ResetButton_3_clicked();

    void on_ClearButton_3_clicked();

    void on_CancelButton_clicked();

private:
    Ui::ResetWeekDayFestival *ui;
    Calendar& m_Controller;
};

#endif // RESETWEEKDAYFESTIVAL_H
