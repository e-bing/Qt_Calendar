#include "schedulelistview.h"

// 헤더 파일로 옮기기
#include <QListWidget>
#include <QVBoxLayout>

ScheduleListView::ScheduleListView(const QList<Schedule>& schedules, QWidget *parent)
    : QDialog(parent), m_schedules(schedules)
{
    setupUI();
    populateSchedules();
}

void ScheduleListView::setupUI()
{
    QVBoxLayout* layout = new QVBoxLayout(this);

    m_listWidget = new QListWidget(this);
    layout->addWidget(m_listWidget);

    setLayout(layout);
    setWindowTitle("일정 목록");
    resize(400, 300);
}

void ScheduleListView::populateSchedules()
{
    for (const Schedule& schedule : m_schedules) {
        m_listWidget->addItem(schedule.title());  // Schedule의 title() 함수 호출
    }

    if (m_schedules.isEmpty()) {
        m_listWidget->addItem("해당 날짜에 일정이 없습니다.");
    }
}

