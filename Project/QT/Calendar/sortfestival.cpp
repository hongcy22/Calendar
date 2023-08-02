//
// sortfestival.cpp
// 按节日排序界面函数实现
// Created by 洪宸宇 on 2023/8/1.
// 添加注释 by 洪宸宇 on 2023/8/2.
//
#include "sortfestival.h"
#include "ui_sortfestival.h"
#include <QMessageBox>

// 按节日排序界面类构造函数
// 参数：
// Calendar& Controller：Calendar类的引用
SortFestival::SortFestival(Calendar& Controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SortFestival)
    ,  m_Controller(Controller)
{
    ui->setupUi(this);
}

// 按节日排序界面类析构函数
SortFestival::~SortFestival()
{
    delete ui;
}

// 点击确认按钮,按节日排序
// 获取输入的信息，调用控制器的SortFestival函数
void SortFestival::on_EnterButton_clicked()
{
    // 获取输入的信息
    QString year1 = ui->lineEdit_year1->text();
    QString year2 = ui->lineEdit_year2->text();
    QString month1 = ui->lineEdit_month1->text();
    QString month2 = ui->lineEdit_month2->text();
    QString day1 = ui->lineEdit_day1->text();
    QString day2 = ui->lineEdit_day2->text();
    unsigned int method = ui->spinBox->value(); // 排序方法
    QString output;
    auto result = m_Controller.SortFestival(year1.toUInt(), month1.toUInt(), day1.toUInt(), year2.toUInt(), month2.toUInt(), day2.toUInt(), method);
    if (result == RES::SUCCESS)
    {
        ui->textBrowser_sort->clear();
        for (auto res : m_Controller.data.festivallist)
        {
            output.append(QString::fromStdString(res));
            output.append("\n");
        }
    }
    else
    {
        QMessageBox::warning(this, "Error", QString::fromStdString(ResString[static_cast<int> (result)]));
    }

    // 按照换行符 '\n' 分隔字符串并创建字符串列表
    QStringList lines = output.split('\n');
    // 逐行添加文本到QTextBrowser
    for (const QString& line : lines)
    {
        ui->textBrowser_sort->append(line);
    }
    ui->textBrowser_sort->show();
}

// 点击清空按钮
// 清空输入框
void SortFestival::on_ClearButton_clicked()
{
    ui->lineEdit_year1->clear();
    ui->lineEdit_year2->clear();
    ui->lineEdit_month1->clear();
    ui->lineEdit_month2->clear();
    ui->lineEdit_day1->clear();
    ui->lineEdit_day2->clear();
}

// 点击取消按钮
// 关闭界面
void SortFestival::on_CancelButton_clicked()
{
    close();
}

