//
// mainwindow.cpp
// 控制主界面函数说明
// Created by 洪宸宇 on 2023/7/31.
// 添加注释 by 洪宸宇 on 2023/8/2.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "adddatefestival.h"
#include "addweekdayfestival.h"
#include "deletfestival.h"
#include "findfestival.h"
#include "sortfestival.h"
#include "resetdatefestival.h"
#include "resetweekdayfestival.h"
#include "instruction.h"
#include "dialogabout.h"
#include "setting.h"

#include <QDate>
#include <QString>
#include <QMessageBox>
#include <sstream>
#include <iomanip>
#include <QFrame>
#include <QDateTime>
#include <QDebug>

// 构造函数
// 参数：Calendar& Controller：Calendar类的引用
MainWindow::MainWindow(Calendar& Controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,  m_Controller(Controller) // 调用控制器
{
    ui->setupUi(this);

    // 设置等宽字体
    QFont font("Consolas", 14);
    ui->textBrowser->setFont(font);

    // 设置TextBrowser中的文字居中
    ui->textBrowser->setAlignment(Qt::AlignCenter);

    // 获取当前日期
    QDate currentDate = QDate::currentDate();
    QString output = updateCalendar(currentDate.year(), currentDate.month());

    // 按照换行符 '\n' 分隔字符串并创建字符串列表
    QStringList lines = output.split('\n');
    // 逐行添加文本到QTextBrowser
    for (const QString& line : lines)
    {
        ui->textBrowser->append(line);
    }
    ui->textBrowser->show();

    // 将背景图片的路径替换为实际的路径
    QString backgroundImagePath = "D:/VScode/cpp(code_runner)/final/photo/main_background.jpg";

    // 构造样式表字符串，设置背景图片
    QString styleSheet = QString("QTextBrowser { background-image: url(%1); background-size: cover; }").arg(backgroundImagePath);

    // 为QTextBrowser设置样式表
    ui->textBrowser->setStyleSheet(styleSheet);

    // 创建一个水平分割线
    QFrame* horizontalLine = new QFrame(this);
    horizontalLine->setFrameShape(QFrame::HLine);
    horizontalLine->setFrameShadow(QFrame::Sunken);

    // 设置分割线的大小和位置
    horizontalLine->setGeometry(5, 20, 390, 5);

    // 显示分割线
    horizontalLine->show();

    // 更改标题
    this->setWindowTitle("Calendar");

    // 各种功能
    connect(ui->AddDateFestival, &QAction::triggered, this, &MainWindow::AddDateFestivalSlot); // 添加日期节日
    connect(ui->AddWeekDayFestival, &QAction::triggered, this, &MainWindow::AddWeekDayFestivalSlot); // 添加星期节日
    connect(ui->actionDeletFestival, &QAction::triggered, this, &MainWindow::DelFestivalSlot); // 删除节日
    connect(ui->actionSearch, &QAction::triggered, this, &MainWindow::FindFestivalSlot); // 查找节日
    connect(ui->actionSearch_and_Sort, &QAction::triggered, this, &MainWindow::SortFestivalSlot); // 排序节日
    connect(ui->ResetDateFestival, &QAction::triggered, this, &MainWindow::ResetDateFestivalSlot); // 重置日期节日
    connect(ui->ResetWeekDayFestival, &QAction::triggered, this, &MainWindow::ResetWeekDayFestivalSlot); // 重置星期节日

    connect(ui->actionInstructions, &QAction::triggered, this, &MainWindow::InstructionSlot); // 使用说明
    connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::AboutSlot); // 关于

    // 设置计时器
    m_timer = new QTimer;
    m_timer->start(1000); // 每秒记一次

    connect(m_timer, &QTimer::timeout, this, &MainWindow::UpgradeTimeSlot);

    // 设置动态图片
    // 加载动态GIF图像
    m_movie = new QMovie("D:/VScode/cpp(code_runner)/final/photo/gear.gif");
    m_movie->start();
    m_movie->jumpToFrame(m_movie->frameCount() - 1);

    // 设置设置按钮为初始状态
    m_isMoviePlaying = false;
    updateSettingButton();

    // 设置定时器，每隔一段时间更新一次动画
    m_timer1 = new QTimer(this);
    connect(m_timer1, &QTimer::timeout, this, &MainWindow::updateSettingButton);
    m_timer1->start(100); // 设置定时器间隔，这里为100ms

}

// 析构函数

MainWindow::~MainWindow()
{
    delete ui;

}

// updateCalendar函数，更新日历
// 参数：unsigned int newyear：年份
// 参数：unsigned int newmonth：月份
// 返回值：QString：日历
QString MainWindow::updateCalendar(unsigned int newyear, unsigned int newmonth)
{
    // 获取年份和月份并显示日历
    auto result = m_Controller.ShowCalendar(newyear, newmonth);
    if (result == RES::SUCCESS)
    {
        // 清除textBrowser
        ui->textBrowser->clear();
        auto res = m_Controller.data.calendarlist;
        unsigned int FirstDay; // 获取第一天是星期几
        unsigned int LastDay; // 获取这个月有几天
        // 利用输入流分别赋值
        istringstream iss(res[0]);
        iss >> FirstDay >> LastDay;

        // 使用QString来储存输出结果
        QString* output = new QString;

        // 格式化输出日期，将结果拼接到output中
        output->append(QString("          %1/%2          \n").arg(newyear).arg(newmonth));
        output->append("*******************************\n");
        int maxWidth = 4;
        // 表头
        output->append("  ");
        output->append(QString("Sun").leftJustified(maxWidth, ' '));
        output->append(QString("Mon").leftJustified(maxWidth, ' '));
        output->append(QString("Tue").leftJustified(maxWidth, ' '));
        output->append(QString("Wed").leftJustified(maxWidth, ' '));
        output->append(QString("Thu").leftJustified(maxWidth, ' '));
        output->append(QString("Fri").leftJustified(maxWidth, ' '));
        output->append(QString("Sat").leftJustified(maxWidth, ' '));
        output->append("\n  ");

        // 输出第一行的空格
        for (unsigned int i = 0; i < FirstDay; ++i) {
            output->append("    ");
        }

        if (i == 7) {
            output->append("  ");
        }

        // 输出日期
        for (unsigned int day = 1; day <= LastDay; ++day) {
            // 格式化输出日期，保持两位数
            if (day < 10)
            {
                output->append(QString("  %1 ").arg(day));
            }
            else
            {
                output->append(QString(" %1 ").arg(day));
            }

            // 换行处理
            if ((day + FirstDay) % 7 == 0) {
                output->append("\n  ");
            }
        }

        // 输出最后一行的换行
        output->append("\n");
        output->append("*******************************\n");

        // 输出节日
        for (unsigned int i = 1; i < res.size(); ++i) {
            output->append(QString::fromStdString(res[i]));
            output->append("\n");
        }
        return *output;
    }
    else
    {
        // 弹出错误提示
        QMessageBox::warning(this, "Error", QString::fromStdString(ResString[static_cast<int> (result)]));
        return "Error!";
    }
}

// on_EnterButton_clicked函数,点击按钮后更新日历
// 参数：无
void MainWindow::on_EnterButton_clicked()
{
    // 获取年份和月份
    unsigned int newyear = ui->spinBox_year->value();
    unsigned int newmonth = ui->spinBox_month->value();

    QString res = updateCalendar(newyear, newmonth);

    // 按照换行符 '\n' 分隔字符串并创建字符串列表
    QStringList lines = res.split('\n');
    // 逐行添加文本到QTextBrowser
    for (const QString& line : lines)
    {
        ui->textBrowser->append(line);
    }
    ui->textBrowser->show();
}

// AddDateFestivalSlot函数，更新时间
// 参数：无
void MainWindow::AddDateFestivalSlot()
{
    // 开启新界面AddDateFestival
    AddDateFestival* ad = new AddDateFestival(m_Controller);
    ad->show();
}

// AddWeekDayFestivalSlot函数，更新时间
// 参数：无
void MainWindow::AddWeekDayFestivalSlot()
{
    // 开启新界面AddWeekDayFestival
    AddWeekDayFestival* aw = new AddWeekDayFestival(m_Controller);
    aw->show();
}

// DelFestivalSlot函数，删除节日
// 参数：无
void MainWindow::DelFestivalSlot()
{
    // 开启新界面DeletFestival
    DeletFestival* df = new DeletFestival(m_Controller);
    df->show();
}

// FindFestivalSlot函数，查找节日
// 参数：无
void MainWindow::FindFestivalSlot()
{
    // 开启新界面FindFestival
    FindFestival* ff = new FindFestival(m_Controller);
    ff->show();
}

// SortFestivalSlot函数，排序节日
// 参数：无
void MainWindow::SortFestivalSlot()
{
    // 开启新界面SortFestival
    SortFestival* sf = new SortFestival(m_Controller);
    sf->show();
}

// ResetDateFestivalSlot函数，重置日期节日
// 参数：无
void MainWindow::ResetDateFestivalSlot()
{
    // 开启新界面ResetDateFestival
    ResetDateFestival* rf = new ResetDateFestival(m_Controller);
    rf->show();
}

// ResetWeekDayFestivalSlot函数，重置星期节日
// 参数：无
void MainWindow::ResetWeekDayFestivalSlot()
{
    // 开启新界面ResetWeekDayFestival
    ResetWeekDayFestival* rw = new ResetWeekDayFestival(m_Controller);
    rw->show();
}

// InstructionSlot函数，打开说明书
// 参数：无
void MainWindow::InstructionSlot()
{
    // 开启新界面Instruction
    Instruction* i = new Instruction();
    i->show();
}

// AboutSlot函数，打开关于界面
// 参数：无
void MainWindow::AboutSlot()
{
    // 开启新界面DialogAbout
    DialogAbout* da = new DialogAbout;
    da->show();
}

// UpgradeTimeSlot函数，更新时间
// 参数：无
void MainWindow::UpgradeTimeSlot()
{
    // 获取当前日期和时间
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // 获取时间和日期的字符串
    QString timeString = currentDateTime.toString("HH:mm:ss");
    QString dateString = currentDateTime.toString("yyyy/MM/dd");

    // 将日期和时间字符串拼接起来并显示在 QLabel 中
    ui->label_time->setText(timeString + "   " + dateString);
}

// updateSettingButton函数，更新设置按钮
// 参数：无
void MainWindow::updateSettingButton()
{
    // 获取鼠标在窗口内的位置
    bool mouseOverButton = ui->SettingButton->underMouse();
    if (mouseOverButton == true && m_isMoviePlaying == false) {
        // 鼠标移动到按钮上时，开始播放动画并跳转到第一帧
        m_movie->jumpToFrame(0);
        m_movie->start();
        m_isMoviePlaying = true;
    } else if (mouseOverButton == true && m_isMoviePlaying == true) {
        // 太长时间停下
        if (m_movie->currentFrameNumber() == m_movie->frameCount() - 1) {
            m_movie->stop();
        }
    } else if (mouseOverButton == false && m_isMoviePlaying == true) {
        // 鼠标移出按钮时，停止播放动画并跳转到最后一帧
        m_movie->start();
        m_movie->jumpToFrame(m_movie->frameCount() - 1);
        m_isMoviePlaying = false;
    } else {
        m_movie->start();
        m_movie->jumpToFrame(m_movie->frameCount() - 1);
    }
    // 显示图像
    ui->SettingButton->setIcon(QIcon(m_movie->currentPixmap()));
    ui->SettingButton->setIconSize(ui->SettingButton->size());
}

// on_SettingButton_clicked函数，点击设置按钮
// 参数：无
void MainWindow::on_SettingButton_clicked()
{
    Setting* s = new Setting(this);
    s->show();
}

// GetSettingButtonGeomtry函数,获取设置按钮的位置
// 参数：无
QRect MainWindow::GetSettingButtonGeomtry()
{
    return ui->SettingButton->geometry();
}

// SetBackGroundColor函数，设置背景颜色
// 参数：QString color
// 返回值：无
void MainWindow::SetBackGroundColor(QString color)
{
    QString styleSheet = color;
    this->setStyleSheet(styleSheet);
}

// SetBackGroundPhoto函数，设置背景图片
// 参数：QString photo
// 返回值：无
void MainWindow::SetBackGroundPhoto(QString photo)
{
    QString imagePath = photo;
    QString styleSheet = QString("background-image: url(%1); background-repeat: no-repeat; background-position: center;").arg(imagePath);
    this->setStyleSheet(styleSheet);
}
