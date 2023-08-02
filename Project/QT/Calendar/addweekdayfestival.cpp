// 
// addweekdayfestival.cpp
// 添加星期节日界面函数实现
// Created by 洪宸宇 on 2023/7/31.
// 添加注释 by 洪宸宇 on 2023/8/2.
//
#include "addweekdayfestival.h"
#include "ui_addweekdayfestival.h"
#include <QMessageBox>

// 构造函数
// 参数：
// Calendar& Controller：Calendar类的引用
// QWidget *parent：父窗口指针
AddWeekDayFestival::AddWeekDayFestival(Calendar& Controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddWeekDayFestival)
    ,  m_Controller(Controller) // 调用控制器
{
    ui->setupUi(this);

    // 更改标题
    this->setWindowTitle("Add WeekDayFestival");
}

// 析构函数
AddWeekDayFestival::~AddWeekDayFestival()
{
    delete ui;

}

// 点击确认按钮
// 获取输入的信息，调用控制器的AddWeekDayFestival函数
void AddWeekDayFestival::on_EnterButton_clicked()
{
    QString name = ui->lineEdit_Name->text();
    QString month = ui->lineEdit_Month->text();
    QString weektype = ui->lineEdit_WeekType->text();
    QString weekday = ui->lineEdit_WeekDay->text();
    QString startyear = ui->lineEdit_Startyear->text();
    auto result = m_Controller.AddWeekDayFestival(name.toStdString(), month.toUInt(), weektype.toInt(), weekday.toUInt(), startyear.toUInt());
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
void AddWeekDayFestival::on_ClearButton_clicked()
{
    ui->lineEdit_Name->clear();
    ui->lineEdit_Month->clear();
    ui->lineEdit_WeekType->clear();
    ui->lineEdit_WeekDay->clear();
    ui->lineEdit_Startyear->clear();
}

// 点击取消按钮
// 关闭窗口
void AddWeekDayFestival::on_CancelButton_clicked()
{
    close();
}

