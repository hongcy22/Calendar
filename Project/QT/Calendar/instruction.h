//
// instruction.h
// 说明界面头文件
// Created by 洪宸宇 on 2023/8/1.
// 添加注释 by 洪宸宇 on 2023/8/2.
//
#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QWidget>

namespace Ui {
class Instruction;
}

//
// 说明界面类
// 继承自QWidget
// 用于显示说明界面
// 私有成员：
// Ui::Instruction *ui：界面指针
// 公有成员：
// 构造函数、析构函数   
// 槽函数：
// on_comboBox_activated：选择下拉框
// on_pushButton_clicked：点击确认按钮
class Instruction : public QWidget
{
    Q_OBJECT

public:
    explicit Instruction(QWidget *parent = nullptr);
    ~Instruction();

private slots:
    void on_comboBox_activated(int index);

    void on_pushButton_clicked();

private:
    Ui::Instruction *ui;
};

#endif // INSTRUCTION_H
