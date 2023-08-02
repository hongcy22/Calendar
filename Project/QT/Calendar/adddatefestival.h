#ifndef ADDDATEFESTIVAL_H
#define ADDDATEFESTIVAL_H

#include <QWidget>
#include "../../test/CalendarController.hpp"

namespace Ui {
class AddDateFestival;
}

class AddDateFestival : public QWidget
{
    Q_OBJECT

public:
    explicit AddDateFestival(Calendar& Controller, QWidget *parent = nullptr);
    ~AddDateFestival();

private slots:
    void on_ClearButton_clicked();

    void on_CancleButton_clicked();

    void on_EnterButton_clicked();

private:
    Ui::AddDateFestival *ui;
    Calendar& m_Controller;
};

#endif // ADDDATEFESTIVAL_H
