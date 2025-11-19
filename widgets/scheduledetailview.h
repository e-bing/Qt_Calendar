#ifndef SCHEDULEDETAILVIEW_H
#define SCHEDULEDETAILVIEW_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>
#include <QMessageBox>

#include "../models/schedule.h"
#include "../models/schedulemanager.h"
#include "../models/categorymanager.h"
#include "./scheduleform.h"
#include "../resources/styles/colors.h"

class ScheduleDetailView : public QDialog
{
    Q_OBJECT
public:
    explicit ScheduleDetailView(const Schedule& schedule, ScheduleManager* manager, CategoryManager* categoryManager, QWidget* parent);

private:
    Schedule m_schedule;
    ScheduleManager* m_scheduleManager;
    CategoryManager* m_categoryManager;

    QLabel* m_titleLabel;
    QLabel* m_timeLabel;
    QLabel* m_locationLabel;
    QLabel* m_memoLabel;
    QLabel* m_categoryColorBox;
    QPushButton* m_editButton;
    QPushButton* m_deleteButton;

    void setupUI();
    void updateUI();
    void onDeleteClicked();
    void onEditClicked();

signals:
    void scheduleDeleted(int scheduleId);
    void scheduleUpdated(int scheduleId);

};

#endif // SCHEDULEDETAILVIEW_H
