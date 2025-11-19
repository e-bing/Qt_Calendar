#include "scheduleform.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QDebug> // 디버깅용으로 필요시 사용

ScheduleForm::ScheduleForm(CategoryManager* categoryManager, QWidget* parent)
    : QDialog(parent), m_categoryManager(categoryManager)
{
    if (m_categoryManager) {
        m_categories = m_categoryManager->getAllCategories();
    }

    setupUI();

    connectSignals();
    setWindowTitle("일정 추가");
    setFixedSize(400, 500);
}

ScheduleForm::ScheduleForm(const Schedule& schedule, CategoryManager* categoryManager, QWidget* parent)
    : QDialog(parent), m_categoryManager(categoryManager)
{
    if (m_categoryManager) {
        m_categories = m_categoryManager->getAllCategories();
    }

    setupUI();

    m_titleEdit->setText(schedule.title());
    m_startEdit->setDateTime(schedule.startTime());
    m_endEdit->setDateTime(schedule.endTime());
    m_locationEdit->setText(schedule.location());
    m_memoEdit->setPlainText(schedule.memo());

    for (const Category& cat : m_categories) {
        m_categoryCombo->addItem(cat.title());
    }

    // 기존 카테고리 선택 index 설정
    int index = 0;
    for (int i = 0; i < m_categories.size(); ++i) {
        if (m_categories[i].id() == schedule.categoryId()) {
            index = i;
            break;
        }
    }
    m_categoryCombo->setCurrentIndex(index);

    connectSignals();
    setWindowTitle("일정 수정");
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

    QHBoxLayout* categoryRowLayout = new QHBoxLayout;
    QLabel* categoryLabel = new QLabel("카테고리:", this);
    m_addCategoryButton = new QPushButton("+", this);
    m_addCategoryButton->setFixedSize(60, 24);

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

    categoryRowLayout->addWidget(categoryLabel);
    categoryRowLayout->addStretch();
    categoryRowLayout->addWidget(m_addCategoryButton);

    mainLayout->addLayout(categoryRowLayout);
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
    connect(m_addCategoryButton, &QPushButton::clicked, this, &ScheduleForm::onAddCategoryClicked);

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

void ScheduleForm::onAddCategoryClicked()
{
    // CategoryView를 QDialog로 실행
    CategoryView categoryViewDialog(m_categoryManager, this);
    categoryViewDialog.exec(); // 모달 다이얼로그로 실행

    // 다이얼로그 종료 후: ScheduleForm의 카테고리 목록과 콤보박스 갱신

    // 1. 카테고리 매니저에서 최신 목록을 다시 불러옵니다.
    if (m_categoryManager) {
        m_categories = m_categoryManager->getAllCategories();
    }

    // 2. QComboBox의 기존 항목을 지웁니다.
    m_categoryCombo->clear();

    // 3. QComboBox에 최신 카테고리 목록을 다시 추가합니다.
    for (const Category& cat : m_categories) {
        m_categoryCombo->addItem(cat.title());
    }

    // (선택 사항: 만약 수정 중이었다면, 기존에 선택된 카테고리를 다시 선택하도록 로직을 추가할 수 있습니다.)
}
