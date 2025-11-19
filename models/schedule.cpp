#include "Schedule.h"

Schedule::Schedule()
    : m_id(0)
{
}

Schedule::Schedule(int id,
                   const QString &title,
                   const QDateTime &start,
                   const QDateTime &end,
                   const QString &location,
                   const QString &memo,
                   int categoryId
                   )
    : m_id(id), m_title(title), m_start(start), m_end(end),
    m_location(location), m_memo(memo), m_categoryId(categoryId)
{
}

// 사용자로부터 데이터 받기
int Schedule::id() const { return m_id; }
QString Schedule::title() const { return m_title; }
QDateTime Schedule::startTime() const { return m_start; }
QDateTime Schedule::endTime() const { return m_end; }
QString Schedule::location() const { return m_location; }
QString Schedule::memo() const { return m_memo; }
int Schedule::categoryId() const { return m_categoryId; }


// 사용자 데이터 저장하기
void Schedule::setTitle(const QString &value) { m_title = value; }
void Schedule::setStartTime(const QDateTime &value) { m_start = value; }
void Schedule::setEndTime(const QDateTime &value) { m_end = value; }
void Schedule::setLocation(const QString &value) { m_location = value; }
void Schedule::setMemo(const QString &value) { m_memo = value; }
void Schedule::setCategoryId(const int &value) { m_categoryId = value; }
