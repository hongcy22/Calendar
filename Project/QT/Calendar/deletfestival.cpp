// 
// deletfestival.cpp
// 删除节日界面函数实现
// Created by 洪宸宇 on 2023/7/31.
// 添加注释 by 洪宸宇 on 2023/8/2.
//
#include "deletfestival.h"
#include "ui_deletfestival.h"
#include <QMessageBox>

// 构造函数
// 参数：
// Calendar& Controller：Calendar类的引用
DeletFestival::DeletFestival(Calendar& Controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeletFestival)
    ,  m_Controller(Controller)
{
    ui->setupUi(this);
    
    // 更改标题
    this->setWindowTitle("Delet Festival");
}

// 析构函数
DeletFestival::~DeletFestival()
{
    delete ui;

}

// 点击确认按钮
// 获取输入的信息，调用控制器的DelFestival函数
void DeletFestival::on_EnterButton_clicked()
{
    QString name = ui->lineEdit->text();
    auto result = m_Controller.DelFestival(name.toStdString());
    if (result == RES::SUCCESS)
    {
        this->close();
    }
    else
    {
        QMessageBox::warning(this, "Error", QString::fromStdString(ResString[static_cast<int> (result)]));
    }
}

// 点击清空按钮
// 清空输入框
void DeletFestival::on_ClearButton_clicked()
{
    ui->lineEdit->clear();
}

// 点击取消按钮
// 关闭窗口
void DeletFestival::on_CancelButton_clicked()
{
    close();
}

