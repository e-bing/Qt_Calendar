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
    qDebug() << m_schedules.length();
    for (const Schedule& schedule : m_schedules) {
        QWidget* itemWidget = new QWidget(m_listWidget);
        QHBoxLayout* row1 = new QHBoxLayout;
        QLabel* colorBox = new QLabel;
        colorBox->setFixedSize(12, 12); // 카테고리 색
        colorBox->setStyleSheet("background: " + QString(COLOR_PRIMARY)); // 카테고리별 색상 (getColor 함수 임의구현)
        QLabel* timeLabel = new QLabel(schedule.startTime().toString("HH:mm"));
        QLabel* titleLabel = new QLabel(schedule.title());

        row1->addWidget(colorBox);
        row1->addWidget(timeLabel);
        row1->addWidget(titleLabel);

        QHBoxLayout* row2 = new QHBoxLayout;
        QLabel* locationLabel = new QLabel(schedule.location());
        QLabel* memoLabel = new QLabel(schedule.memo());
        row2->addWidget(locationLabel);
        row2->addWidget(memoLabel);

        QVBoxLayout* itemLayout = new QVBoxLayout(itemWidget);
        itemLayout->addLayout(row1);
        itemLayout->addLayout(row2);
        itemWidget->setLayout(itemLayout);

        QListWidgetItem* item = new QListWidgetItem(m_listWidget);
        item->setSizeHint(itemWidget->sizeHint());
        m_listWidget->addItem(item);
        m_listWidget->setItemWidget(item, itemWidget);
    }

    if (m_schedules.isEmpty()) {
        m_listWidget->addItem("해당 날짜에 일정이 없습니다.");
    }
}

