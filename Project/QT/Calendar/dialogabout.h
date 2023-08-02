// 
// dialogabout.h
// 关于界面头文件
// Created by 洪宸宇 on 2023/8/1.
// 添加注释 by 洪宸宇 on 2023/8/2.
//
#ifndef DIALOGABOUT_H
#define DIALOGABOUT_H

#include <QDialog>

namespace Ui {
class DialogAbout;
}

// 关于界面类
// 继承自QDialog
// 用于显示关于界面
// 私有成员：
// Ui::DialogAbout *ui：界面指针
// 公有成员：
// 构造函数、析构函数
class DialogAbout : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAbout(QWidget *parent = nullptr);
    ~DialogAbout();

private:
    Ui::DialogAbout *ui;
};

#endif // DIALOGABOUT_H
