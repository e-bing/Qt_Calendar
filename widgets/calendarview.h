#ifndef CALENDARVIEW_H
#define CALENDARVIEW_H

#include <QWidget>
#include <QCalendarWidget>
#include <QList>
#include <QVBoxLayout>
#include <QTextCharFormat>
#include <QBrush>
#include <QColor>
#include "../models/schedule.h"
#include "../resources/styles/colors.h"

class CalendarView : public QWidget
{
    Q_OBJECT

public:
    explicit CalendarView(QWidget *parent = nullptr);

    void setSchedules(const QList<Schedule>& schedules);

signals:
    void dateSelected(const QDate& date);
    void scheduleSelected(const Schedule& schedule);

private slots:
    void onDateChanged(const QDate& date);

private:
    QCalendarWidget* m_calendar;
    QList<Schedule> m_schedules;

    void highlightScheduleDates();
    void showSchedulesForDate(const QDate& date);
};

#endif // CALENDARVIEW_H
