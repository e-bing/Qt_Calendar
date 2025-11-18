#ifndef SCHEDULELISTVIEW_H
#define SCHEDULELISTVIEW_H

#include <QDialog>
#include <QList>
#include "../models/schedule.h"

class QListWidget;

class ScheduleListView : public QDialog
{
    Q_OBJECT
public:
    explicit ScheduleListView(const QList<Schedule>& schedules, QWidget *parent = nullptr);

private:
    QListWidget* m_listWidget;
    QList<Schedule> m_schedules;

    void setupUI();
    void populateSchedules();
};

#endif // SCHEDULELISTVIEW_H
