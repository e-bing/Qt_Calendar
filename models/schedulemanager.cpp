#include "schedulemanager.h"

ScheduleManager::ScheduleManager(const QString& dbPath, QObject* parent)
    : QObject(parent), m_dbPath(dbPath)
{
    if (!QSqlDatabase::contains("shared_connection"))
    {
        m_database = QSqlDatabase::addDatabase("QSQLITE", "shared_connection");
        m_database.setDatabaseName(m_dbPath);
    }
    else
    {
        m_database = QSqlDatabase::database("shared_connection");
    }
}

ScheduleManager::~ScheduleManager()
{
    if (m_database.isOpen()) {
        m_database.close();
    }
}

bool ScheduleManager::openDatabase()
{
    QString dbDir = QFileInfo(m_dbPath).absolutePath();

    if(!QDir(dbDir).exists()) {
        qDebug() << "DB 폴더를 생성합니다:" << dbDir;
        QDir().mkpath(dbDir);
    }

    if (!m_database.open()) {
        emit databaseError("Failed to open database: " + m_database.lastError().text());
        return false;
    }

    QSqlQuery pragmaQuery(m_database);
    if(!pragmaQuery.exec("PRAGMA foreign_keys = ON")) {
        qWarning() << "Failed to enable foreign keys:" << pragmaQuery.lastError().text();
    }

    QSqlQuery query(m_database);
    QString createTableSql = R"(
        CREATE TABLE IF NOT EXISTS schedules (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            start_time TEXT NOT NULL,
            end_time TEXT NOT NULL,
            location TEXT,
            memo TEXT,
            category_id INTEGER DEFAULT 0,
            FOREIGN KEY (category_id) REFERENCES categories(id)
        )
    )";

    if (!query.exec(createTableSql)) {
        emit databaseError("Failed to create schedules table: " + query.lastError().text());
        return false;
    }

    return true;
}

void ScheduleManager::closeDatabase()
{
    if (m_database.isOpen()) {
        m_database.close();
    }
}

bool ScheduleManager::addSchedule(const Schedule& schedule)
{

    QSqlQuery query(m_database);

    QString sql =
        "INSERT INTO schedules (title, start_time, end_time, location, memo, category_id) "
        "VALUES (?, ?, ?, ?, ?, ?)";
    query.prepare(sql);

    query.addBindValue(schedule.title());
    query.addBindValue(schedule.startTime().toString(Qt::ISODate));
    query.addBindValue(schedule.endTime().toString(Qt::ISODate));
    query.addBindValue(schedule.location());
    query.addBindValue(schedule.memo());
    query.addBindValue(schedule.categoryId());

    if(!query.exec()) {
        qDebug() << "schedule add 실패:" << query.lastError().text();
        emit databaseError("Failed to insert schedule: " + query.lastError().text());
        return false;
    }
    return true;
}

bool ScheduleManager::updateSchedule(const Schedule& schedule)
{
    QSqlQuery query(m_database);
    query.prepare("UPDATE schedules SET title = ?, start_time = ?, end_time = ?, location = ?, memo = ?, category_id = ? WHERE id = ?");
    query.addBindValue(schedule.title());
    query.addBindValue(schedule.startTime().toString(Qt::ISODate));
    query.addBindValue(schedule.endTime().toString(Qt::ISODate));
    query.addBindValue(schedule.location());
    query.addBindValue(schedule.memo());
    query.addBindValue(schedule.categoryId());
    query.addBindValue(schedule.id());

    if (!query.exec()) {
        emit databaseError("Failed to update schedule: " + query.lastError().text());
        return false;
    }

    return true;
}

bool ScheduleManager::deleteSchedule(int id)
{
    QSqlQuery query(m_database);
    query.prepare("DELETE FROM schedules WHERE id = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        emit databaseError("Failed to delete schedule: " + query.lastError().text());
        return false;
    }

    return true;
}

QList<Schedule> ScheduleManager::getAllSchedules()
{
    QList<Schedule> schedules;
    QSqlQuery query(m_database);
    if(!query.exec("SELECT id, title, start_time, end_time, location, memo, category_id FROM schedules ORDER BY start_time")) {
        emit databaseError("Failed to fetch schedules: " + query.lastError().text());
        return schedules;
    }

    while (query.next()) {
        QVariantMap record;
        record["id"] = query.value("id");
        record["title"] = query.value("title");
        record["start_time"] = query.value("start_time");
        record["end_time"] = query.value("end_time");
        record["location"] = query.value("location");
        record["memo"] = query.value("memo");
        record["category_id"] = query.value("category_id");

        schedules.append(scheduleFromQuery(record));
    }
    return schedules;
}

QList<Schedule> ScheduleManager::searchSchedules(const QString& keyword)
{
    QList<Schedule> schedules;
    QSqlQuery query(m_database);
    query.prepare("SELECT id, title, start_time, end_time, location, memo, category_id FROM schedules WHERE title LIKE ? ORDER BY start_time");
    query.addBindValue("%" + keyword + "%");

    if (!query.exec()) {
        emit databaseError("Failed to search schedules: " + query.lastError().text());
        return schedules;
    }

    while (query.next()) {
        QVariantMap record;
        record["id"] = query.value("id");
        record["title"] = query.value("title");
        record["start_time"] = query.value("start_time");
        record["end_time"] = query.value("end_time");
        record["location"] = query.value("location");
        record["memo"] = query.value("memo");
        record["category_id"] = query.value("category_id");

        schedules.append(scheduleFromQuery(record));
    }
    return schedules;
}

Schedule ScheduleManager::scheduleFromQuery(const QVariantMap& record)
{
    int id = record.value("id").toInt();
    QString title = record.value("title").toString();
    QDateTime start = QDateTime::fromString(record.value("start_time").toString(), Qt::ISODate);
    QDateTime end = QDateTime::fromString(record.value("end_time").toString(), Qt::ISODate);
    QString location = record.value("location").toString();
    QString memo = record.value("memo").toString();
    int category_id = record.value("category_id").toInt();

    return Schedule(id, title, start, end, location, memo, category_id);
}
