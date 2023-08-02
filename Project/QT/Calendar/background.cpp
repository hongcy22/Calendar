// 
// background.cpp
// 背景界面函数实现
// Created by 洪宸宇 on 2023/8/1.
// 添加注释 by 洪宸宇 on 2023/8/2.
//
#include "background.h"
#include "ui_background.h"
#include "mainwindow.h" // 包含主界面的头文件
#include <QMessageBox>

// 构造函数
// 参数：
// MainWindow* ptr：指向主界面的指针
// 返回值：无
BackGround::BackGround(MainWindow* ptr, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BackGround),
    m_mainWindow(ptr)
{
    ui->setupUi(this);

    this->setWindowTitle("BackGround");
}

// 析构函数
BackGround::~BackGround()
{
    delete ui;
}

// 设置背景图片
// 参数：
// MainWindow* ptr：指向主界面的指针
void BackGround::SetBackGround(MainWindow* ptr)
{
    ptr->SetBackGroundPhoto(ui->lineEdit->text());
}

// 点击下拉框
// 参数：
// int index：下拉框的索引
// 返回值：无
void BackGround::on_comboBox_activated(int index)
{
    QString ss;
    // 根据下拉框的索引设置背景颜色
    switch (index)
    {
    case 0:
    // 设置背景颜色为经典色
        ss = QString("background-color: rgb(%1, %2, %3);").arg(241).arg(238).arg(218);
        m_mainWindow->SetBackGroundColor(ss);
        break;
    case 1:
    // 设置背景颜色为灰色
        ss = QString("background-color: rgb(%1, %2, %3);").arg(192).arg(192).arg(192);
        m_mainWindow->SetBackGroundColor(ss);
        break;
    case 2:
    // 设置背景颜色为白色
        ss = QString("background-color: rgb(%1, %2, %3);").arg(255).arg(255).arg(255);
        m_mainWindow->SetBackGroundColor(ss);
        break;
    case 3:
    // 设置背景颜色为黑色
        ss = QString("background-color: rgb(%1, %2, %3);").arg(0).arg(0).arg(0);
        m_mainWindow->SetBackGroundColor(ss);
        break;
    case 4:
    // 设置背景颜色为绿色
        ss = QString("background-color: rgb(%1, %2, %3);").arg(123).arg(185).arg(155);
        m_mainWindow->SetBackGroundColor(ss);
        break;
    default:
        QMessageBox::warning(this, "Error", "Invalid choose!");
    }
}





