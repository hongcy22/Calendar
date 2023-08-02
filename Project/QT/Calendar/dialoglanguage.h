//
// dialoglanguage.h
// 语言界面头文件
// Created by 洪宸宇 on 2023/8/1.
// 添加注释 by 洪宸宇 on 2023/8/2.
//
#ifndef DIALOGLANGUAGE_H
#define DIALOGLANGUAGE_H

#include <QDialog>

namespace Ui {
class DialogLanguage;
}

// 语言界面类
// 继承自QDialog
// 用于显示语言界面
// 私有成员：
// Ui::DialogLanguage *ui：界面指针
// 公有成员：
// 构造函数、析构函数
class DialogLanguage : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLanguage(QWidget *parent = nullptr);
    ~DialogLanguage();

private:
    Ui::DialogLanguage *ui;
};

#endif // DIALOGLANGUAGE_H
