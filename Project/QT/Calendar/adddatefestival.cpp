#include "adddatefestival.h"
#include "ui_adddatefestival.h"
#include <QMessageBox>

AddDateFestival::AddDateFestival(Calendar& Controller, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddDateFestival)
    ,  m_Controller(Controller)
{
    ui->setupUi(this);

    // 更改标题
    this->setWindowTitle("Add DateFestival");
}

AddDateFestival::~AddDateFestival()
{
    delete ui;
}


void AddDateFestival::on_ClearButton_clicked()
{
    ui->lineEdit_Name->clear();
    ui->lineEdit_Month->clear();
    ui->lineEdit_Day->clear();
    ui->lineEdit_Startyear->clear();
}


void AddDateFestival::on_CancleButton_clicked()
{
    this->close();
}


void AddDateFestival::on_EnterButton_clicked()
{
    QString name = ui->lineEdit_Name->text();
    QString month = ui->lineEdit_Month->text();
    QString day = ui->lineEdit_Day->text();
    QString startyear = ui->lineEdit_Startyear->text();
    auto result = m_Controller.AddDateFestival(name.toStdString(), month.toUInt(), day.toUInt(), startyear.toUInt());
    if (result == RES::SUCCESS)
    {
        this->close();
    }
    else
    {
        QMessageBox::warning(this, "Error", QString::fromStdString(ResString[static_cast<int> (result)]));
    }
}

