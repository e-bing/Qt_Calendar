#include "schedulelistview.h"

// 헤더 파일로 옮기기
#include <QListWidget>
#include <QVBoxLayout>

ScheduleListView::ScheduleListView(const QList<Schedule>& schedules, const QDate& date, QWidget *parent)
    : QDialog(parent), m_schedules(schedules)
{
    setupUI();
    m_dateLabel->setText(date.toString("yyyy-MM-dd") + " 일정 목록");
    populateSchedules();
}

void ScheduleListView::setupUI()
{
    this->setStyleSheet("background-color: " + COLOR_BACKGROUND);

    QVBoxLayout* layout = new QVBoxLayout(this);
    m_listWidget = new QListWidget(this);

    m_dateLabel = new QLabel(this);
    QFont font = m_dateLabel->font();
    font.setPointSize(12);
    font.setBold(true);
    m_dateLabel->setFont(font);
    m_dateLabel->setAlignment(Qt::AlignCenter);

    layout->addWidget(m_dateLabel);
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

