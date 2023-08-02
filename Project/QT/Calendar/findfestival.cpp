// 
// findfestival.cpp
// 查找节日界面函数实现
// Created by 洪宸宇 on 2023/7/31.
// 添加注释 by 洪宸宇 on 2023/8/2.
//
#include "findfestival.h"
#include "ui_findfestival.h"
#include <QMessageBox>

// 构造函数
// 参数：
// Calendar& Controller：Calendar类的引用
FindFestival::FindFestival(Calendar& Controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FindFestival)
    ,  m_Controller(Controller)
{
    ui->setupUi(this);

    // 更改标题
    this->setWindowTitle("Find Festival");
}

// 析构函数
FindFestival::~FindFestival()
{
    delete ui;
}

// 点击确定按钮
// 获取输入的信息，调用控制器的SearchFestival函数
void FindFestival::on_EnterButton_clicked()
{
    // 获取输入的信息
    QString name = ui->lineEdit_name->text();
    QString year = ui->lineEdit_year->text();
    QString res;

    // 调用控制器的SearchFestival函数,获取完整信息
    auto result = m_Controller.SearchFestival(name.toStdString());
    bool flag = true;
    if (result == RES::SUCCESS && flag == true)
    {
        res.append("The message of the festival:\n");
        res.append(QString::fromStdString(m_Controller.data.festivalmessage));
        res.append("\n\n");
    }
    else
    {
        flag = false;
    }

    // 调用控制器的SearchFestival函数,获取指定年份信息
    result = m_Controller.SearchFestival(name.toStdString(), year.toInt());
    if (result == RES::SUCCESS)
    {
        res.append("The date of the festival in ");
        res.append(year);
        res.append(":\n");
        res.append(QString::fromStdString(m_Controller.data.festivalmessage));
        res.append("\n\n");
    }
    else
    {
        flag = false;
    }

    // 调用控制器的CountDown函数,获取距离下一次该节日的天数
    result = m_Controller.CountDown(name.toStdString());
    if (result == RES::SUCCESS)
    {
        res.append("The nearest one will be in ");
        res.append(QString::number(m_Controller.data.festivalcount));
        res.append(" days.\n");
    }
    else
    {
        flag = false;
    }

    // 有错误则弹出错误信息
    if (flag == false)
    {
        QMessageBox::warning(this, "Error", QString::fromStdString(ResString[static_cast<int> (result)]));
    }

    // 按照换行符 '\n' 分隔字符串并创建字符串列表
    QStringList lines = res.split('\n');
    // 逐行添加文本到QTextBrowser
    ui->textBrowser->clear();
    for (const QString& line : lines)
    {
        ui->textBrowser->append(line);
    }
    ui->textBrowser->show();
}

// 点击清除按钮
// 清除输入的信息
void FindFestival::on_ClearButton_clicked()
{
    ui->lineEdit_name->clear();
    ui->lineEdit_year->clear();
}

// 点击取消按钮
// 关闭窗口
void FindFestival::on_CancelButton_clicked()
{
    close();
}

