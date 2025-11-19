#include "./searchdialog.h"

SearchDialog::SearchDialog(ScheduleManager* scheduleManager, CategoryManager* categoryManager, QWidget* parent)
    : QDialog(parent), m_scheduleManager(scheduleManager), m_categoryManager(categoryManager)
{
    setupUI();

    connect(m_searchButton, &QPushButton::clicked, this, &SearchDialog::onSearchClicked);
}

void SearchDialog::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QHBoxLayout* searchLayout = new QHBoxLayout;

    m_searchEdit = new QLineEdit(this);
    m_searchEdit->setPlaceholderText("검색어를 입력하세요");

    m_searchButton = new QPushButton("검색", this);
    m_searchButton->setStyleSheet(QString(R"(
    QPushButton {
        background-color: %1;
        color: white;
        border-radius: 6px;
        padding: 5px 12px;
        font-size: 13px;
    }
    QPushButton:hover {
        background-color: %2;
    }
)")
                                    .arg(COLOR_PRIMARY)
                                    .arg(COLOR_PRIMARY_HOVER));

    searchLayout->addWidget(m_searchEdit);
    searchLayout->addWidget(m_searchButton);


    m_resultList = new QListWidget(this);

    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(m_resultList);
}

void SearchDialog::onSearchClicked()
{
    QString keyword = m_searchEdit->text().trimmed();
    if (keyword.isEmpty()) {
        QMessageBox::information(this, "입력 오류", "검색어를 입력하세요.");
        return;
    }

    QList<Schedule> result = m_scheduleManager->searchSchedules(keyword);
    m_currentResults = result;

    QMap<QDate, QList<Schedule>> groupedSchedules;

    for (const auto& sched : result) {
        QDate date = sched.startTime().date();
        groupedSchedules[date].append(sched);
    }

    m_resultList->clear();

    if (result.isEmpty())
    {
        m_resultList->addItem("검색 결과가 없습니다.");
    }
    else
    {
        for (auto it = groupedSchedules.begin(); it != groupedSchedules.end(); ++it)
        {
            QListWidgetItem* dateItem = new QListWidgetItem(m_resultList);
            QLabel* dateLabel = new QLabel(it.key().toString("yyyy-MM-dd"));
            dateLabel->setStyleSheet(QString("font-size: 12px; padding: 6px; color: %1;")
                                         .arg(COLOR_SECONDARY));
            m_resultList->addItem(dateItem);
            m_resultList->setItemWidget(dateItem, dateLabel);
            dateItem->setFlags(dateItem->flags() & ~Qt::ItemIsSelectable); // 날짜 구분자 선택 불가

            for (const Schedule& sched : it.value()) {
                QListWidgetItem* item = new QListWidgetItem(m_resultList);
                ScheduleListCell* cellWidget = new ScheduleListCell(sched, m_categoryManager, m_resultList);
                item->setSizeHint(cellWidget->sizeHint());
                m_resultList->addItem(item);
                m_resultList->setItemWidget(item, cellWidget);
            }
        }
    }
}

void SearchDialog::onResultItemClicked(QListWidgetItem* item)
{
    int idx = m_resultList->row(item);
    if (idx < 0 || idx >= m_currentResults.size()) return;

    Schedule schedule = m_currentResults[idx];
    ScheduleDetailView* detail = new ScheduleDetailView(schedule, m_scheduleManager, m_categoryManager, this);

    connect(detail, &ScheduleDetailView::scheduleDeleted, this, &SearchDialog::onScheduleUpdated);
    connect(detail, &ScheduleDetailView::scheduleUpdated, this, &SearchDialog::onScheduleUpdated);

    detail->exec();
}

void SearchDialog::onScheduleUpdated(int id)
{
    for (const Schedule& sched : m_currentResults)
    {
        if (sched.id() == id) {
            onSearchClicked();
            return;
        }
    }
    onSearchClicked();
}
