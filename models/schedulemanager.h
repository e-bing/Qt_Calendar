#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H

#include <QObject>
#include <QList>
#include <QVariantMap>
#include <QSqlDatabase>
#include "schedule.h"

class ScheduleManager : public QObject
{
    Q_OBJECT
public:
    ScheduleManager();
};

#endif // SCHEDULEMANAGER_H
