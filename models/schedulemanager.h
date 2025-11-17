#ifndef SCHEDULEMANAGER_H
#define SCHEDULEMANAGER_H

#include <QObject>
#include <QList>
#include <QVariantMap>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include "schedule.h"

class ScheduleManager : public QObject
{
    Q_OBJECT
public:
    explicit ScheduleManager(const QString& dbPath, QObject* parent = nullptr);
    ~ScheduleManager();

    bool openDatabase();
    void closeDatabase();

    // 일정 추가
    bool addSchedule(const Schedule& schedule);

    // 일정 수정
    bool updateSchedule(const Schedule& schedule);

    // 일정 삭제
    bool deleteSchedule(int id);

    // 전체 일정 조회
    QList<Schedule> getAllSchedules();

    // 일정 검색
    QList<Schedule> searchSchedules(const QString& keyword);

signals:
    void databaseError(const QString& error);

private:
    QSqlDatabase m_database;
    QString m_dbPath;

    Schedule scheduleFromQuery(const QVariantMap& record);
};

#endif // SCHEDULEMANAGER_H
