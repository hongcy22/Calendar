//
// mainwindow.h
// 控制主界面函数说明
// Created by 洪宸宇 on 2023/7/31.
// 添加注释 by 洪宸宇 on 2023/8/2.
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../test/CalendarController.hpp"
#include <QMovie>
#include <QTimer>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
// 主界面类
// 用于控制主界面的显示
// 通过调用Calendar类的函数来实现功能
// 私有成员：
// Calendar& m_Controller：Calendar类的引用
// QTimer* m_timer：用于更新时间的定时器
// QTimer* m_timer1：用于更新背景动图的定时器
// QMovie* m_movie：用于播放背景动图的QMovie对象
// bool m_isMoviePlaying：用于判断背景动图是否正在播放
// 公有成员：
// 构造函数、析构函数
// updateCalendar：更新日历
// updateSettingButton：更新设置按钮
// GetSettingButtonGeomtry：获取设置按钮的位置
// SetBackGroundColor：设置背景颜色
// SetBackGroundPhoto：设置背景图片
// 槽函数：
// on_EnterButton_clicked：点击进入按钮
// AddDateFestivalSlot：添加日期节日槽函数
// AddWeekDayFestivalSlot：添加星期节日槽函数
// DelFestivalSlot：删除节日槽函数
// FindFestivalSlot：查找节日槽函数
// SortFestivalSlot：排序节日槽函数
// ResetDateFestivalSlot：重置日期节日槽函数
// ResetWeekDayFestivalSlot：重置星期节日槽函数
// InstructionSlot：使用说明槽函数
// AboutSlot：关于槽函数
// UpgradeTimeSlot：更新时间槽函数
// on_SettingButton_clicked：点击设置按钮
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Calendar& Controller, QWidget *parent = nullptr);
    ~MainWindow();
    // 更新日历
    QString updateCalendar(unsigned int newyear, unsigned int newmonth);
    // 更新设置按钮
    void updateSettingButton();

    // 获取设置按钮的位置
    QRect GetSettingButtonGeomtry();

    // 设置背景颜色,图片
    void SetBackGroundColor(QString color);
    void SetBackGroundPhoto(QString photo);

private slots:
    // 点击进入按钮
    void on_EnterButton_clicked();

    // 添加日期节日槽函数
    void AddDateFestivalSlot();
    void AddWeekDayFestivalSlot();
    // 删除节日槽函数
    void DelFestivalSlot();
    // 查找节日槽函数
    void FindFestivalSlot();
    // 排序节日槽函数
    void SortFestivalSlot();
    // 重置日期节日槽函数
    void ResetDateFestivalSlot();
    void ResetWeekDayFestivalSlot();

    // 使用说明槽函数
    void InstructionSlot();
    void AboutSlot();

    // 更新时间槽函数
    void UpgradeTimeSlot();

    // 点击设置按钮
    void on_SettingButton_clicked();

private:
    Ui::MainWindow *ui;
    //添加一个Calendar类
    Calendar& m_Controller;

    // 定时器
    QTimer* m_timer;
    QTimer* m_timer1;

    // 背景动图
    QMovie* m_movie;
    bool m_isMoviePlaying;

};
#endif // MAINWINDOW_H
