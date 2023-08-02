//
// setting.cpp
// 设置界面函数实现
// Created by 洪宸宇 on 2023/8/1.
// 添加注释 by 洪宸宇 on 2023/8/2.
//
#include "setting.h"
#include "ui_setting.h"
#include "mainwindow.h" // 包含主界面的头文件
#include "dialoglanguage.h"
#include "background.h"

// 构造函数
// 参数：
// MainWindow* ptr：主界面指针
Setting::Setting(MainWindow* ptr, QWidget* parent) :
    QWidget(parent),
    ui(new Ui::Setting),
    m_mainWindow(ptr)
{
    ui->setupUi(this);

    this->setWindowTitle("Setting");
}

// 析构函数
Setting::~Setting()
{
    delete ui;
}

// showEvent函数，重写自QWidget
// 参数：
// QShowEvent* event：事件指针
// 重写showEvent函数，使得子窗口显示在主窗口的右上角
void Setting::showEvent(QShowEvent* event)
{
    // 获取SettingButton的位置和尺寸
    QRect settingButtonRect = m_mainWindow->GetSettingButtonGeomtry();

    // 计算子窗口的位置
    QPoint subWindowPos = m_mainWindow->mapToGlobal(settingButtonRect.topRight());

    // 设置子窗口的位置
    this->move(subWindowPos);
}

// 点击背景按钮
// 跳转到背景设置界面
void Setting::on_BackGroundButton_clicked()
{
    BackGround* bg = new BackGround(m_mainWindow);
    bg->show();
    this->close();
}

// 点击语言按钮
// 跳转到语言设置界面
void Setting::on_LanguageButton_clicked()
{
    DialogLanguage* dl = new DialogLanguage;
    dl->show();
}

// 点击取消按钮
// 关闭设置界面
void Setting::on_CancelButton_clicked()
{
    this->close();
}

