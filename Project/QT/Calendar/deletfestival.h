//
// deletfestival.h
// 删除节日界面头文件
// Created by 洪宸宇 on 2023/7/31.
// 添加注释 by 洪宸宇 on 2023/8/2.
//
#ifndef DELETFESTIVAL_H
#define DELETFESTIVAL_H

#include <QWidget>
#include "../../test/CalendarController.hpp"

namespace Ui {
class DeletFestival;
}

// 删除节日界面类
// 继承自QWidget
// 用于删除节日
// 私有成员：
// Ui::DeletFestival *ui：界面指针
// Calendar& m_Controller：Calendar类的引用
// 公有成员：
// 构造函数、析构函数
// 槽函数：
// on_EnterButton_clicked：点击确认按钮
// on_ClearButton_clicked：点击清空按钮
// on_CancelButton_clicked：点击取消按钮
class DeletFestival : public QWidget
{
    Q_OBJECT

public:
    explicit DeletFestival(Calendar& Controller, QWidget *parent = nullptr);
    ~DeletFestival();

private slots:
    void on_EnterButton_clicked();

    void on_ClearButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::DeletFestival *ui;
    Calendar& m_Controller;
};

#endif // DELETFESTIVAL_H
