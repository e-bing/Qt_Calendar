#ifndef SCHEDULELISTVIEW_H
#define SCHEDULELISTVIEW_H

#include <QDialog>
#include <QList>
#include <QLabel>
#include <QListWidget>
#include <QVBoxLayout>
#include "../models/schedule.h"
#include "../models/categorymanager.h"
#include "scheduledetailview.h"
#include "schedulelistcell.h"
#include "scheduleform.h"
#include "../resources/styles/colors.h"

class QListWidget;

class ScheduleListView : public QDialog
{
    Q_OBJECT
public:
    explicit ScheduleListView(const QList<Schedule>& schedules, const QDate& date, ScheduleManager* manager, CategoryManager* categoryManager, QWidget *parent = nullptr);

private:
    QDate m_date;
    QLabel* m_dateLabel;
    QListWidget* m_listWidget;
    QList<Schedule> m_schedules;
    ScheduleManager* m_scheduleManager;
    CategoryManager* m_categoryManager;
    QPushButton* m_addButton;

    void setupUI();
    void populateSchedules();
    void onScheduleDeleted(int scheduleId);
    void onScheduleUpdated(int scheduleId, const Schedule& updatedSchedule);

private slots:
    void onAddButtonClicked();

signals:
    void scheduleUpdated(int scheduleId);
};

#endif // SCHEDULELISTVIEW_H
