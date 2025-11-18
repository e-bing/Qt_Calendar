#ifndef SCHEDULELISTVIEW_H
#define SCHEDULELISTVIEW_H

#include <QDialog>
#include <QList>
#include <QLabel>
#include <QListWidget>
#include <QVBoxLayout>
#include "../models/schedule.h"
#include "scheduledetailview.h"
#include "schedulelistcell.h"
#include "../resources/styles/colors.h"

class QListWidget;

class ScheduleListView : public QDialog
{
    Q_OBJECT
public:
    explicit ScheduleListView(const QList<Schedule>& schedules, const QDate& date, QWidget *parent = nullptr);

private:
    QLabel* m_dateLabel;
    QListWidget* m_listWidget;
    QList<Schedule> m_schedules;

    void setupUI();
    void populateSchedules();
};

#endif // SCHEDULELISTVIEW_H
