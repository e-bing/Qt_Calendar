#include "calendarview.h"

CalendarView::CalendarView(QWidget *parent)
    : QWidget{parent}, m_calendar(new QCalendarWidget(this))
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(m_calendar);

    // 날짜 선택 시 시그널 연결
    connect(m_calendar, &QCalendarWidget::selectionChanged, this, [this]() {
        QDate selectedDate = m_calendar->selectedDate();
        emit dateSelected(selectedDate);
        showSchedulesForDate(selectedDate);
    });
}

void CalendarView::setSchedules(const QList<Schedule>& schedules)
{
    m_schedules = schedules;
    highlightScheduleDates();
}

void CalendarView::highlightScheduleDates()
{
    // 달력의 모든 날짜 형식 초기화
    QTextCharFormat defaultFormat;
    m_calendar->setDateTextFormat(QDate(), defaultFormat);

    // 일정이 있는 날짜들을 하이라이트
    QColor color(COLOR_PRIMARY);
    QBrush brush(color);
    QTextCharFormat highlightFormat;
    highlightFormat.setBackground(brush);

    QSet<QDate> datesWithSchedules;
    for (const auto& schedule : m_schedules) {
        // 일정 시작일부터 종료일까지 모두 하이라이트 처리
        QDate startDate = schedule.startTime().date();
        datesWithSchedules.insert(startDate);
    }

    for (const QDate& date : datesWithSchedules) {
        m_calendar->setDateTextFormat(date, highlightFormat);
    }
}

void CalendarView::showSchedulesForDate(const QDate& date)
{
    for (const auto& schedule : m_schedules) {
        if (schedule.startTime().date() == date) {
            emit scheduleSelected(schedule);
            break;
        }
    }
}

void CalendarView::onDateChanged(const QDate& date) {
    emit dateSelected(date);
    showSchedulesForDate(date);
}
