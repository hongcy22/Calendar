//
// instruction.cpp
// 指令界面函数实现
// Created by 洪宸宇 on 2023/8/1.
// 添加注释 by 洪宸宇 on 2023/8/2.
//
#include "instruction.h"
#include "ui_instruction.h"
#include <QMessageBox>

// 构造函数
// 参数：
// QWidget *parent：指向父界面的指针
Instruction::Instruction(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Instruction)
{
    ui->setupUi(this);

    // 将背景图片的路径替换为实际的路径
    QString backgroundImagePath = "D:/VScode/cpp(code_runner)/final/photo/main_background.jpg";

    // 构造样式表字符串，设置背景图片
    QString styleSheet = QString("QTextBrowser { background-image: url(%1); background-size: cover; }").arg(backgroundImagePath);

    // 为QTextBrowser设置样式表
    ui->textBrowser->setStyleSheet(styleSheet);

    // 更改标题
    this->setWindowTitle("Instructions");

    // 设置等宽字体
    QFont font("Times New Roman", 12);
    ui->textBrowser->setFont(font);

    //初始化显示内容
    ui->textBrowser->setText("Welcome to the instruction function!");
}

// 析构函数 
Instruction::~Instruction()
{
    delete ui;
}

// 点击下拉框
// 给出各个功能的说明
// 参数：
// int index：下拉框的索引
// 返回值：无
void Instruction::on_comboBox_activated(int index)
{
    QString help;
    switch (index)
    {
    case 0:
        // 说明添加节日的功能
        help = "You can add special festivals using this \"Add\" function, including two types: date-based festivals and weekday-based festivals. "
               "For date-based festivals, input the festival name (without colons), the specific month and day, and the starting year for the festival. "
               "Then click the \"Enter\" key to add it. "
               "Similarly, for weekday-based festivals, input the festival name, the specific month, the week type, the day of the week, and the starting year for the holiday. "
               "You can also click the \"Clear\" key to remove the entered information and re-enter new details, or click the \"Cancel\" key to exit this function.";
        break;
    case 1:
    // 说明删除节日的功能
        help = "In the festival deletion function, you only need to input the name of the festival you want to delete, "
               "then wait for the program to search, and click the \"Enter\" key to delete the holiday. "
               "Similarly, you can click the \"Clear\" key to remove the entered information and re-enter new details, or click the \"Cancel\" key to exit this function";
        break;
    case 2:
    // 说明查询节日的功能
        help = "This is a function to search for festival information. You need to input the name of the festival you want to find and a year for the search. "
               "After clicking the \"Enter\" key, the basic information of the festival will be displayed below, "
               "including the date of the festival in that year and the time remaining until the next occurrence of the festival from today. "
               "You can click the \"Clear\" key to remove the entered information and re-enter new details, or click the \"Cancel\" key to exit this function.";
        break;
    case 3:
    // 说明查询节日的功能
        help = "This function allows you to search for all festivals between two dates. Please note that the time span between the two dates cannot exceed one year. "
               "You need to input two valid dates and then choose the sorting method, either by name or by date. "
               "After that, click the \"Enter\" key to proceed. "
               "You can click the \"Clear\" key to remove the entered information and re-enter new dates, or click the \"Cancel\" key to exit this function.";
        break;
    case 4:
    // 说明修改节日的功能
        help = "The Modify function allows you to edit the recorded festivals, including modifying the festival name, date, and starting year. "
               "You can select which type of festival to modify from the menu. "
               "In the modification interface for date-based festivals, you need to first input the festival name and then choose which part to modify. "
               "To modify the corresponding part, simply enter the new information and press the corresponding Enter key. "
               "The \"Clear\" key can help you clear the information in that section, allowing you to re-enter new data. "
               "Finally, the \"Cancel\" key allows you to exit this function. "
               "In the case of week-based festivals, the process is similar, and it is important to ensure the accuracy of the information provided.";
        break;
    default:
        QMessageBox::warning(this, "Error", "Invalid choose!");
    }
    // 按照换行符 '\n' 分隔字符串并创建字符串列表
    QStringList lines = help.split('\n');
    ui->textBrowser->clear();
    // 逐行添加文本到QTextBrowser
    for (const QString& line : lines)
    {
        ui->textBrowser->append(line);
    }
    ui->textBrowser->show();
}

// 点击返回按钮
// 返回主界面
void Instruction::on_pushButton_clicked()
{
    close();
}

