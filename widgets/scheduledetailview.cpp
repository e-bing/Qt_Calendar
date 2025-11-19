#include "scheduledetailview.h"

ScheduleDetailView::ScheduleDetailView(const Schedule& schedule, ScheduleManager* manager, CategoryManager* categoryManager, QWidget* parent)
    : QDialog(parent), m_schedule(schedule), m_scheduleManager(manager), m_categoryManager(categoryManager)
{
    setupUI();
    updateUI();
    setWindowTitle("일정 상세");
    resize(360, 200);
}

void ScheduleDetailView::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(24, 16, 24, 16); // 여백
    mainLayout->setSpacing(15);

    // 제목 + 카테고리 색상 박스
    QHBoxLayout* topRow = new QHBoxLayout;
    m_categoryColorBox = new QLabel(this);
    m_categoryColorBox->setFixedSize(20, 20);
    m_categoryColorBox->setStyleSheet(QString("background: %1; border-radius: 4px;")
                                      .arg(COLOR_PRIMARY));

    m_titleLabel = new QLabel(this);
    m_titleLabel->setStyleSheet("font-weight: bold; font-size: 16px; margin-left:4px;");

    topRow->addWidget(m_categoryColorBox, 0, Qt::AlignVCenter);
    topRow->addWidget(m_titleLabel, 1, Qt::AlignVCenter);
    topRow->addStretch();

    mainLayout->addLayout(topRow);

    // 시간 라벨
    m_timeLabel = new QLabel(this);
    m_timeLabel->setStyleSheet(QString("color:%1; font-size:15px;")
                                   .arg(COLOR_BLACK)); // 시간 폰트 색상
    mainLayout->addWidget(m_timeLabel);

    // 카테고리 이름 라벨
    m_categoryNameLabel = new QLabel(this);
    m_categoryNameLabel->setStyleSheet(QString("color:%1; font-size:14px;")
                                    .arg(COLOR_BLACK)); // 카테고리 이름 폰트 색상
    mainLayout->addWidget(m_categoryNameLabel);

    // 장소 라벨
    m_locationLabel = new QLabel(this);
    m_locationLabel->setStyleSheet(QString("color:%1; font-size:14px;")
                                    .arg(COLOR_BLACK));
    mainLayout->addWidget(m_locationLabel);

    // 메모 라벨
    m_memoLabel = new QLabel(this);
    m_memoLabel->setStyleSheet(QString("color:%1; font-size:14px;")
                                   .arg(COLOR_BLACK)); // 메모 폰트 색상
    mainLayout->addWidget(m_memoLabel);

    // 버튼들
    QHBoxLayout* buttonRow = new QHBoxLayout;
    buttonRow->addStretch();
    m_editButton = new QPushButton("수정", this);
    m_deleteButton = new QPushButton("삭제", this);
    m_editButton->setStyleSheet(QString("padding:6px 15px;border-radius:5px;"
                                 "background-color:%1;border:none;color:%2;")
                                    .arg(COLOR_PRIMARY) // 버튼 색상
                                    .arg(COLOR_SECONDARY)); // 폰트 색상
    m_deleteButton->setStyleSheet(QString("padding:6px 15px;border-radius:5px;"
                                   "background-color:%1;border:none;color:%2;")
                                    .arg(COLOR_PRIMARY) // 버튼 색상
                                    .arg(COLOR_SECONDARY)); // 폰트 색상

    connect(m_editButton, &QPushButton::clicked, this, &ScheduleDetailView::onEditClicked);
    connect(m_deleteButton, &QPushButton::clicked, this, &ScheduleDetailView::onDeleteClicked);

    buttonRow->addWidget(m_editButton);
    buttonRow->addWidget(m_deleteButton);
    mainLayout->addLayout(buttonRow);

    setLayout(mainLayout);
}

void ScheduleDetailView::updateUI()
{
    m_titleLabel->setText(m_schedule.title());

    QString catColor = COLOR_PRIMARY;
    QString catName = "";
    if (m_categoryManager) {
        Category cat = m_categoryManager->getCategoryById(m_schedule.categoryId());
        if (cat.id() != -1) {
            catColor = cat.color();
            catName = cat.title();
        }
    }
    m_categoryColorBox->setStyleSheet(QString("background: %1; border-radius: 4px;").arg(catColor));
    m_categoryNameLabel->setText("카테고리: " + catName);

    QString startStr = m_schedule.startTime().toString("yyyy-MM-dd HH:mm");
    QString endStr   = m_schedule.endTime().toString("yyyy-MM-dd HH:mm");

    if (startStr == endStr)
        m_timeLabel->setText("시간: " + startStr);
    else
        m_timeLabel->setText("기간: " + startStr + " ~ " + endStr);

    m_locationLabel->setText(m_schedule.location().isEmpty() ? "" : ("장소: " + m_schedule.location()));
    m_memoLabel->setText(m_schedule.memo().isEmpty() ? "" : ("메모: " + m_schedule.memo()));
}

void ScheduleDetailView::onDeleteClicked()
{
    auto reply = QMessageBox::question(
        this,
        "일정 삭제",
        "정말 삭제하시겠습니까?",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        if (m_scheduleManager && m_scheduleManager->deleteSchedule(m_schedule.id())) {
            emit scheduleDeleted(m_schedule.id());
            accept(); // QDialog 닫기 (성공 반환)
        } else {
            // 실패 메시지
            QMessageBox::warning(this, "삭제 실패", "일정 삭제에 실패했습니다.");
        }
    }
}

void ScheduleDetailView::onEditClicked()
{
    ScheduleForm editForm(m_schedule, m_categoryManager, this);
    if (editForm.exec() == QDialog::Accepted) {
        Schedule updatedSchedule = editForm.getSchedule();

        if (m_scheduleManager && m_scheduleManager->updateSchedule(updatedSchedule)) {
            m_schedule = updatedSchedule;
            updateUI();
            QMessageBox::information(this, "성공", "일정이 수정되었습니다.");
            emit scheduleUpdated(m_schedule.id(), m_schedule);
        } else {
            QMessageBox::warning(this, "실패", "일정 수정에 실패했습니다.");
        }
    }
}
