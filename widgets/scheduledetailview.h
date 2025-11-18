#ifndef SCHEDULEDETAILVIEW_H
#define SCHEDULEDETAILVIEW_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDateTime>

#include "../models/schedule.h"

class ScheduleDetailView : public QDialog
{
    Q_OBJECT
public:
    explicit ScheduleDetailView(const Schedule& schedule, QWidget* parent = nullptr);

private:
    const Schedule m_schedule;

    QLabel* m_titleLabel;
    QLabel* m_timeLabel;
    QLabel* m_locationLabel;
    QLabel* m_memoLabel;
    QLabel* m_categoryColorBox;
    // QPushButton* m_editButton, m_deleteButton 등 추가

    void setupUI();
    void updateUI();

signals:
};

#endif // SCHEDULEDETAILVIEW_H
