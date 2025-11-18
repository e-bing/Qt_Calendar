#include "schedulelistview.h"

ScheduleListView::ScheduleListView(const QList<Schedule>& schedules, const QDate& date, QWidget *parent)
    : QDialog(parent), m_schedules(schedules)
{
    setupUI();
    m_dateLabel->setText(date.toString("yyyy-MM-dd"));
    populateSchedules();

    connect(m_listWidget, &QListWidget::itemClicked, this, [this](QListWidgetItem* item){
        int idx = m_listWidget->row(item);
        if (idx >= 0 && idx < m_schedules.size()) {
            ScheduleDetailView* detail = new ScheduleDetailView(m_schedules[idx], this);
            detail->exec();
        }
    });
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
    m_listWidget->clear();

    for (const Schedule& schedule : m_schedules) {
        QListWidgetItem* item = new QListWidgetItem(m_listWidget);
        ScheduleListCell* cell = new ScheduleListCell(schedule, m_listWidget);
        item->setSizeHint(QSize(280, 56)); // 필요시 조정
        m_listWidget->addItem(item);
        m_listWidget->setItemWidget(item, cell);
    }

    if (m_schedules.isEmpty()) {
        QListWidgetItem* item = new QListWidgetItem(QStringLiteral("해당 날짜에 일정이 없습니다."), m_listWidget);
        m_listWidget->addItem(item);
    }
}

