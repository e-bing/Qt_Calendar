#ifndef CALENDAR_H
#define CALENDAR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Calendar;
}
QT_END_NAMESPACE

class Calendar : public QWidget
{
    Q_OBJECT

public:
    Calendar(QWidget *parent = nullptr);
    ~Calendar();

private:
    Ui::Calendar *ui;
};
#endif // CALENDAR_H
