//
// dialogabout.cpp
// 关于界面函数实现
// Created by 洪宸宇 on 2023/8/1.
// 添加注释 by 洪宸宇 on 2023/8/2.
//
#include "dialogabout.h"
#include "ui_dialogabout.h"

// 构造函数
// 参数：
// QWidget *parent：指向父界面的指针
DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
    ui->setupUi(this);

    // 更改标题
    this->setWindowTitle("About");
}

// 析构函数
DialogAbout::~DialogAbout()
{
    delete ui;
}
