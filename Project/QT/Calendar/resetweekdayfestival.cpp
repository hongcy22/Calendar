//
// resetweekdayfestival.cpp
// 重置周节日界面函数实现
// Created by 洪宸宇 on 2023/8/1.
// 添加注释 by 洪宸宇 on 2023/8/2.
//
#include "resetweekdayfestival.h"
#include "ui_resetweekdayfestival.h"
#include <QMessageBox>

// 构造函数
// 参数：
// Calendar& Controller：日历类的引用
ResetWeekDayFestival::ResetWeekDayFestival(Calendar& Controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ResetWeekDayFestival)
    ,  m_Controller(Controller)
{
    ui->setupUi(this);

    // 更改标题
    this->setWindowTitle("Reset WeekDayFestival");
}

ResetWeekDayFestival::~ResetWeekDayFestival()
{
    delete ui;
}

// 点击确认按钮,重置周节日名称
// 获取输入的信息，调用控制器的ResetWeekDayFestivalName函数
void ResetWeekDayFestival::on_ResetButton_1_clicked()
{
    // 获取输入的信息
    QString newname = ui->lineEdit_NewName->text();
    QString name = ui->lineEdit_name->text();
    auto result = m_Controller.ResetWeekDayFestivalName(name.toStdString(), newname.toStdString());
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
void ResetWeekDayFestival::on_ClearButton_1_clicked()
{
    ui->lineEdit_NewName->clear();
}

// 点击确认按钮,重置周节日日期
// 获取输入的信息，调用控制器的ResetWeekDayFestivalDate函数
void ResetWeekDayFestival::on_ResetButton_2_clicked()
{
    // 获取输入的信息
    QString month = ui->lineEdit_NewMonth->text();
    QString weektype = ui->lineEdit_NewWeektype->text();
    QString weekday = ui->lineEdit_NewWeekDay->text();
    QString name = ui->lineEdit_name->text();
    auto result = m_Controller.ResetWeekDayFestivalDate(name.toStdString(), month.toUInt(), weektype.toUInt(), weekday.toUInt());
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
void ResetWeekDayFestival::on_ClearButton_2_clicked()
{
    ui->lineEdit_NewMonth->clear();
    ui->lineEdit_NewWeekDay->clear();
    ui->lineEdit_NewWeektype->clear();
}

// 点击确认按钮,重置周节日起始年份
// 获取输入的信息，调用控制器的ResetWeekDayFestivalStartYear函数
void ResetWeekDayFestival::on_ResetButton_3_clicked()
{
    // 获取输入的信息
    QString startyear = ui->lineEdit_NewStartYear->text();
    QString name = ui->lineEdit_name->text();
    auto result = m_Controller.ResetWeekDayFestivalStartYear(name.toStdString(), startyear.toUInt());
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
void ResetWeekDayFestival::on_ClearButton_3_clicked()
{
    ui->lineEdit_NewStartYear->clear();
}

// 点击取消按钮
// 关闭界面
void ResetWeekDayFestival::on_CancelButton_clicked()
{
    close();
}

