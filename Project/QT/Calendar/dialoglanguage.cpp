//
// dialoglanguage.cpp
// 语言界面函数实现
// Created by 洪宸宇 on 2023/8/1.
// 添加注释 by 洪宸宇 on 2023/8/2.
//
#include "dialoglanguage.h"
#include "ui_dialoglanguage.h"

// 构造函数
// 参数：
// QWidget *parent：指向父界面的指针
DialogLanguage::DialogLanguage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogLanguage)
{
    ui->setupUi(this);
    // 更改标题
    this->setWindowTitle("Language");
}

// 析构函数
DialogLanguage::~DialogLanguage()
{
    delete ui;
}
