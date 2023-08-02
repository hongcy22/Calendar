//
// resetdatefestival.cpp
// 重置节日界面函数实现
// Created by 洪宸宇 on 2023/8/1.
// 添加注释 by 洪宸宇 on 2023/8/2.
//
#include "resetdatefestival.h"
#include "ui_resetdatefestival.h"
#include <QMessageBox>

// 构造函数
// 参数：
// Calendar& Controller：日历类的引用 
ResetDateFestival::ResetDateFestival(Calendar& Controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResetDateFestival)
    ,  m_Controller(Controller)
{
    ui->setupUi(this);

    // 更改标题
    this->setWindowTitle("Reset DeatFestival");
}

// 析构函数
ResetDateFestival::~ResetDateFestival()
{
    delete ui;
}

// 点击确认按钮,重置节日名称
// 获取输入的信息，调用控制器的ResetDateFestivalName函数
void ResetDateFestival::on_ResetButton_1_clicked()
{
    // 获取输入的信息
    QString newname = ui->lineEdit_newname->text();
    QString name = ui->lineEdit_Name->text();
    auto result = m_Controller.ResetDateFestivalName(name.toStdString(), newname.toStdString());
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
// 清空新名称输入框
void ResetDateFestival::on_ClearButton_1_clicked()
{
    ui->lineEdit_newname->clear();
}

// 点击确认按钮,重置节日日期
// 获取输入的信息，调用控制器的ResetDateFestivalDate函数
void ResetDateFestival::on_ResetButton_2_clicked()
{
    // 获取输入的信息
    QString month = ui->lineEdit_newmonth->text();
    QString day = ui->lineEdit_newday->text();
    QString name = ui->lineEdit_Name->text();
    auto result = m_Controller.ResetDateFestivalDate(name.toStdString(), month.toUInt(), day.toUInt());
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
// 清空新日期输入框
void ResetDateFestival::on_ClearButton_2_clicked()
{
    ui->lineEdit_newmonth->clear();
    ui->lineEdit_newday->clear();
}

// 点击确认按钮,重置节日起始年份
// 获取输入的信息，调用控制器的ResetDateFestivalStartYear函数
void ResetDateFestival::on_ResetButton_3_clicked()
{
    // 获取输入的信息
    QString startyear = ui->lineEdit_Newyear->text();
    QString name = ui->lineEdit_Name->text();
    auto result = m_Controller.ResetDateFestivalStartYear(name.toStdString(), startyear.toUInt());
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
// 清空新起始年份输入框
void ResetDateFestival::on_ClearButton_3_clicked()
{
    ui->lineEdit_Newyear->clear();
}

// 点击取消按钮
// 关闭界面
void ResetDateFestival::on_CancelButton_clicked()
{
    close();
}

