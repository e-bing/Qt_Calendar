#include "scheduledetailview.h"

ScheduleDetailView::ScheduleDetailView(const Schedule& schedule, QWidget* parent)
    : QDialog(parent), m_schedule(schedule)
{
    setupUI();
    updateUI();
    setWindowTitle("일정 상세");
    resize(360, 200);
}

void ScheduleDetailView::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // 카테고리 색상 박스 (임시로 파랑)
    m_categoryColorBox = new QLabel(this);
    m_categoryColorBox->setFixedSize(16, 16);
    m_categoryColorBox->setStyleSheet("background: #3b82f6; border-radius: 4px;"); // 임의 색상 및 둥글게

    QHBoxLayout* firstLine = new QHBoxLayout;
    firstLine->addWidget(m_categoryColorBox);

    m_titleLabel = new QLabel(this);
    m_titleLabel->setStyleSheet("font-weight: bold; font-size: 16px;");
    firstLine->addWidget(m_titleLabel);

    mainLayout->addLayout(firstLine);

    m_timeLabel = new QLabel(this);
    m_locationLabel = new QLabel(this);
    m_memoLabel = new QLabel(this);

    mainLayout->addWidget(m_timeLabel);
    mainLayout->addWidget(m_locationLabel);
    mainLayout->addWidget(m_memoLabel);

    setLayout(mainLayout);
}

void ScheduleDetailView::updateUI()
{
    m_titleLabel->setText(m_schedule.title());

    QString startStr = m_schedule.startTime().toString("yyyy-MM-dd HH:mm");
    QString endStr   = m_schedule.endTime().toString("yyyy-MM-dd HH:mm");
    if (startStr == endStr)
        m_timeLabel->setText("시간: " + startStr);
    else
        m_timeLabel->setText("기간: " + startStr + " ~ " + endStr);

    m_locationLabel->setText("장소: " + m_schedule.location());
    m_memoLabel->setText("메모: " + m_schedule.memo());

    // 카테고리별 색상으로 바꾸려면 추후 setStyleSheet 부분만 교체
}
