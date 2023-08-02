//
// background.h
// 背景界面函数说明
// Created by 洪宸宇 on 2023/8/1.
// 添加注释 by 洪宸宇 on 2023/8/2.
//
#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QWidget>

class MainWindow; // 前向声明主界面类

namespace Ui {
class BackGround;
}

// 背景界面类
// 用于控制背景界面的显示
// 私有成员：
// MainWindow* m_mainWindow：指向主界面的指针
// 公有成员：
// 构造函数、析构函数
// 槽函数：
// on_comboBox_activated：点击下拉框
class BackGround : public QWidget
{
    Q_OBJECT

public:
    explicit BackGround(MainWindow* ptr, QWidget *parent = nullptr);
    ~BackGround();

    void SetBackGround(MainWindow* ptr);

private slots:


    void on_comboBox_activated(int index);

private:
    Ui::BackGround *ui;
    MainWindow* m_mainWindow; // 指向主界面的指针
};

#endif // BACKGROUND_H
