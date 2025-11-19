#include "scheduleform.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>

ScheduleForm::ScheduleForm(const QList<Category>& categories, QWidget* parent)
    : QDialog(parent), m_categories(categories)
{
    setupUI();

    connectSignals();
    setWindowTitle("일정 추가");
    setFixedSize(400, 500);
}

void ScheduleForm::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    // 제목
    QLabel* titleLabel = new QLabel("제목:", this);
    m_titleEdit = new QLineEdit(this);

    // 시작 시간
    QLabel* startLabel = new QLabel("시작 시간:", this);
    m_startEdit = new QDateTimeEdit(QDateTime::currentDateTime(), this);
    m_startEdit->setCalendarPopup(true);

    // 종료 시간
    QLabel* endLabel = new QLabel("종료 시간:", this);
    m_endEdit = new QDateTimeEdit(QDateTime::currentDateTime(), this);
    m_endEdit->setCalendarPopup(true);

    QLabel* categoryLabel = new QLabel("카테고리:", this);
    m_categoryCombo = new QComboBox(this);
    for (const Category& cat : m_categories) {
        m_categoryCombo->addItem(cat.title());
    }

    // 장소
    QLabel* locationLabel = new QLabel("장소:", this);
    m_locationEdit = new QLineEdit(this);

    // 메모
    QLabel* memoLabel = new QLabel("메모:", this);
    m_memoEdit = new QTextEdit(this);
    m_memoEdit->setFixedHeight(80);

    // 버튼
    m_okButton = new QPushButton("확인", this);
    m_cancelButton = new QPushButton("취소", this);

    // 레이아웃 구성
    mainLayout->addWidget(titleLabel);
    mainLayout->addWidget(m_titleEdit);

    mainLayout->addWidget(startLabel);
    mainLayout->addWidget(m_startEdit);

    mainLayout->addWidget(endLabel);
    mainLayout->addWidget(m_endEdit);

    mainLayout->addWidget(categoryLabel);
    mainLayout->addWidget(m_categoryCombo);

    mainLayout->addWidget(locationLabel);
    mainLayout->addWidget(m_locationEdit);

    mainLayout->addWidget(memoLabel);
    mainLayout->addWidget(m_memoEdit);

    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(m_okButton);
    buttonsLayout->addWidget(m_cancelButton);
    mainLayout->addLayout(buttonsLayout);

    setLayout(mainLayout);
}

void ScheduleForm::connectSignals()
{
    connect(m_okButton, &QPushButton::clicked, this, &ScheduleForm::onOkClicked);
    connect(m_cancelButton, &QPushButton::clicked, this, &ScheduleForm::reject);
}

void ScheduleForm::onOkClicked()
{
    if (m_titleEdit->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "입력 오류", "제목은 필수 입력 항목입니다.");
        return;
    }
    if (m_endEdit->dateTime() < m_startEdit->dateTime()) {
        QMessageBox::warning(this, "입력 오류", "종료 시간은 시작 시간 이후여야 합니다.");
        return;
    }
    accept();
}

Schedule ScheduleForm::getSchedule() const
{
    int index = m_categoryCombo->currentIndex();
    int selectedCategoryId = -1;
    if (index >= 0 && index < m_categories.size())
    {
        selectedCategoryId = m_categories[index].id();  // Category에서 id를 받아야 함
    }

    // 임시 ID -1로 설정, 실제 DB 추가 시 고유 ID가 부여됨
    return Schedule(
        -1,
        m_titleEdit->text().trimmed(),
        m_startEdit->dateTime(),
        m_endEdit->dateTime(),
        m_locationEdit->text().trimmed(),
        m_memoEdit->toPlainText(),
        selectedCategoryId
        );
}
