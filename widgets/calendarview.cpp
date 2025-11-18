#include "calendarview.h"

CalendarView::CalendarView(QWidget *parent)
    : QCalendarWidget{parent}
{
    setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);

    // 날짜 선택 시 시그널 연결
    // connect(this, &QCalendarWidget::selectionChanged, this, [this]() {
    //     QDate selectedDate = this->selectedDate();
    //     emit dateSelected(selectedDate);
    //     showSchedulesForDate(selectedDate);
    // });
}

void CalendarView::setSchedules(const QList<Schedule>& schedules)
{
    m_schedules = schedules;
    updateCells();
    update();
}

void CalendarView::paintCell(QPainter *painter, const QRect &rect, QDate date) const
{
    bool isCurrentMonth = (date.month() == this->monthShown()) && (date.year() == this->yearShown());

    painter->save();
    QFont dateFont = painter->font();
    dateFont.setBold(true);
    painter->setFont(dateFont);
    QRect dateRect(rect.left(), rect.top()+4, rect.width(), 24);
    // 회색 색상 추가 필요
    QColor textColor = isCurrentMonth ? QColor(COLOR_BLACK) : QColor(COLOR_GRAY);
    painter->setPen(textColor);

    painter->drawText(dateRect, Qt::AlignHCenter | Qt::AlignTop, QString::number(date.day()));
    painter->restore();

    auto schedules = findSchedulesForDate(date);
    int marginX = 2;
    int marginY = 24;
    int boxWidth = rect.width() - 2*marginX;
    int boxHeight = 18;
    int spacing = 2;

    for (int i = 0; i < schedules.size(); ++i) {
        QRect boxRect(
            rect.left() + (rect.width() - boxWidth)/2,
            rect.top() + marginY + i*(boxHeight+spacing),
            boxWidth,
            boxHeight
            );

        painter->save();
        // 박스 색상 카테고리별로 설정 필요
        QColor boxColor = QColor(COLOR_PRIMARY);
        painter->setBrush(boxColor);
        painter->setPen(Qt::NoPen);
        painter->drawRoundedRect(boxRect, 4, 4);

        QFont textFont = painter->font();
        textFont.setPointSize(9);
        painter->setFont(textFont);
        painter->setPen(Qt::black);
        painter->drawText(boxRect.adjusted(4, 0, -4, 0), Qt::AlignVCenter | Qt::AlignLeft, schedules[i].title());
        painter->restore();
    }

    painter->save();
    // 회색 색상 추가 필요
    QColor penColor = QColor(COLOR_GRAY_LIGHT);
    QPen thinPen(penColor);
    thinPen.setWidth(1);
    painter->setPen(thinPen);
    painter->setBrush(Qt::NoBrush);

    painter->drawRect(rect.adjusted(0, 0, 0, 0));
    painter->restore();
}

QList<Schedule> CalendarView::findSchedulesForDate(const QDate& date) const
{
    QList<Schedule> result;
    for (const auto& s : m_schedules) {
        if (date >= s.startTime().date() && date <= s.endTime().date())
            result.append(s);
    }
    return result;
}


QList<Schedule> CalendarView::showSchedulesForDate(const QDate& date) const
{
    QList<Schedule> result;
    for (const auto& schedule : m_schedules) {
        if (schedule.startTime().date() == date) {
            result.append(schedule);
        }
    }
    return result;
}

void CalendarView::onDateChanged(const QDate& date) {
    emit dateSelected(date);
    showSchedulesForDate(date);
}
