//
// setting.h
// 设置界面头文件
// Created by 洪宸宇 on 2023/8/1.
// 添加注释 by 洪宸宇 on 2023/8/2.
//
#ifndef SETTING_H
#define SETTING_H

#include <QWidget>

class MainWindow; // 前向声明主界面类

namespace Ui {
class Setting;
}

// 设置界面类
// 继承自QWidget
// 用于设置
// 私有成员：
// Ui::Setting *ui：界面指针
// MainWindow* m_mainWindow：指向主界面的指针
// 公有成员：
// 构造函数、析构函数
// 槽函数：
// on_LanguageButton_clicked：点击语言按钮
// on_BackGroundButton_clicked：点击背景按钮
// on_CancelButton_clicked：点击取消按钮
class Setting : public QWidget
{
    Q_OBJECT

public:
    explicit Setting(MainWindow* ptr, QWidget* parent = nullptr);
    ~Setting();
    void showEvent(QShowEvent* event);

private slots:

    void on_LanguageButton_clicked();

    void on_BackGroundButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::Setting *ui;
    MainWindow* m_mainWindow; // 指向主界面的指针
};

#endif // SETTING_H
