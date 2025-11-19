#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <Qstring>
#include <QDateTime>

class Schedule
{
public:
    Schedule();
    Schedule(int m_id,
             const QString &m_title,
             const QDateTime &m_start,
             const QDateTime &m_end,
             const QString &m_location = "",
             const QString &m_memo = "",
             int m_categoryId = 0);
    Schedule(const Schedule& other);
    Schedule& operator=(const Schedule& other);

    // Getter Function
    int id() const;
    QString title() const;
    QDateTime startTime() const;
    QDateTime endTime() const;
    QString location() const;
    QString memo() const;
    int categoryId() const;

    // Setter Function
    void setTitle(const QString &value);
    void setStartTime(const QDateTime &value);
    void setEndTime(const QDateTime &value);
    void setLocation(const QString &value);
    void setMemo(const QString &value);
    void setCategoryId(const int &value);

private:
    int m_id;
    QString m_title;
    QDateTime m_start;
    QDateTime m_end;
    QString m_location;
    QString m_memo;
    int m_categoryId;
};

#endif // SCHEDULE_H
