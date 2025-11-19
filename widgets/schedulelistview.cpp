#include "schedulelistview.h"

ScheduleListView::ScheduleListView(const QList<Schedule>& schedules, const QDate& date, ScheduleManager* manager, CategoryManager* categoryManager, QWidget *parent)
    : QDialog(parent), m_schedules(schedules), m_scheduleManager(manager), m_categoryManager(categoryManager), m_date(date)
{
    setupUI();
    m_dateLabel->setText(date.toString("yyyy-MM-dd"));
    populateSchedules();

    connect(m_listWidget, &QListWidget::itemClicked, this, [this](QListWidgetItem* item){
        int idx = m_listWidget->row(item);
        if (idx >= 0 && idx < m_schedules.size()) {
            ScheduleDetailView* detail = new ScheduleDetailView(m_schedules[idx], m_scheduleManager, m_categoryManager, this);
            connect(detail, &ScheduleDetailView::scheduleDeleted, this, &ScheduleListView::scheduleUpdated);
            connect(detail, &ScheduleDetailView::scheduleDeleted, this, &ScheduleListView::onScheduleDeleted);
            connect(detail, &ScheduleDetailView::scheduleUpdated, this, &ScheduleListView::scheduleUpdated);
            connect(detail, &ScheduleDetailView::scheduleUpdated, this, &ScheduleListView::onScheduleUpdated);

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

    m_addButton = new QPushButton("+", this);
    layout->addWidget(m_addButton);

    setLayout(layout);
    setWindowTitle("일정 목록");
    resize(400, 300);

    connect(m_addButton, &QPushButton::clicked, this, &ScheduleListView::onAddButtonClicked);
}

void ScheduleListView::populateSchedules()
{
    m_listWidget->clear();

    for (const Schedule& schedule : m_schedules) {
        QListWidgetItem* item = new QListWidgetItem(m_listWidget);
        ScheduleListCell* cell = new ScheduleListCell(schedule, m_categoryManager, m_listWidget);
        item->setSizeHint(QSize(280, 56)); // 필요시 조정
        m_listWidget->addItem(item);
        m_listWidget->setItemWidget(item, cell);
    }

    if (m_schedules.isEmpty()) {
        QListWidgetItem* item = new QListWidgetItem(QStringLiteral("해당 날짜에 일정이 없습니다."), m_listWidget);
        m_listWidget->addItem(item);
    }
}

void ScheduleListView::onScheduleDeleted(int scheduleId)
{
    for (int i = 0; i < m_schedules.size(); ++i) {
        if (m_schedules[i].id() == scheduleId) {
            m_schedules.removeAt(i);
            break;
        }
    }
    populateSchedules();
}

void ScheduleListView::onScheduleUpdated(int scheduleId, const Schedule& updatedSchedule)
{
    for (int i = 0; i < m_schedules.size(); ++i) {
        if (m_schedules[i].id() == scheduleId) {
            m_schedules[i] = updatedSchedule;
            break;
        }
    }
    populateSchedules();
}

void ScheduleListView::onAddButtonClicked()
{
    ScheduleForm* form = new ScheduleForm(m_categoryManager, m_date, this);

    if (form->exec() == QDialog::Accepted) {
        Schedule newSchedule = form->getSchedule();
        // DB에 새 일정 추가
        if (m_scheduleManager->addSchedule(newSchedule)) {
            // 성공 시 m_schedules에 추가 후 UI 갱신
            m_schedules.append(newSchedule);
            populateSchedules();
            emit scheduleUpdated(newSchedule.id()); // 상위 알림용 신호 emit
        } else {
            QMessageBox::warning(this, "추가 실패", "일정 추가에 실패했습니다.");
        }
    }

    delete form;
}
