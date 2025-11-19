#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "./widgets/calendarview.h"
#include "./models/schedulemanager.h"
#include "./models/categorymanager.h"
#include "./widgets/schedulelistview.h"
#include "./widgets/searchdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ScheduleManager* scheduleManager;
    CalendarView* calendar;
    CategoryManager* categoryManager;
    QPushButton* searchButton;

    void handleDateSelected(const QDate& date);
    void onSearchButtonClicked();
    void onCategoryChanged();
};
#endif // MAINWINDOW_H
