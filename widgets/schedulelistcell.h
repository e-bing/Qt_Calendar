#ifndef SCHEDULELISTCELL_H
#define SCHEDULELISTCELL_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "../models/schedule.h"

class ScheduleListCell : public QWidget
{
    Q_OBJECT
public:
    ScheduleListCell(const Schedule& schedule, QWidget* parent = nullptr);

signals:
};

#endif // SCHEDULELISTCELL_H
