#include "./mainwindow.h"
#include "./ui_mainwindow.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: " + COLOR_BACKGROUND);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    searchButton = new QPushButton("일정 검색", this);
    searchButton->setStyleSheet(QString(R"(
    QPushButton {
        background-color: %1;
        color: %2;
        border-radius: 8px;
        padding: 6px 14px;
        font-weight: bold;
        font-size: 14px;
    }
    QPushButton:hover {
        background-color: %3;
    }
    QPushButton:pressed {
        background-color: %4;
    }
)").arg(COLOR_PRIMARY).arg(COLOR_SECONDARY).arg(COLOR_PRIMARY_HOVER).arg(COLOR_PRIMARY_HOVER));
    layout->addWidget(searchButton);
    connect(searchButton, &QPushButton::clicked, this, &MainWindow::onSearchButtonClicked);

    calendar = new CalendarView(this);
    layout->addWidget(calendar);

    QString dbPath = QCoreApplication::applicationDirPath() + "/database/schedule.db";
    categoryManager = new CategoryManager(dbPath, this);

    if (!categoryManager->openDatabase()) {
        qDebug() << "카테고리 데이터베이스 열기 실패";
        // 에러 처리
        return;
    }

    scheduleManager = new ScheduleManager(dbPath, this);

    if (!scheduleManager->openDatabase()) {
        qWarning() << "DB 열기 실패";
        // 에러 처리 추가
        return;
    }

    // 스케줄 매니저에서 목록 할당
    QList<Schedule> schedules = scheduleManager->getAllSchedules();
    calendar->setCategories(categoryManager->getAllCategories());
    calendar->setSchedules(schedules);

    // 날짜 선택 시 처리
    connect(calendar, &CalendarView::dateSelected,
            this, &MainWindow::handleDateSelected);

    connect(categoryManager, &CategoryManager::categoryUpdated,
            this, &MainWindow::onCategoryChanged);
}

void MainWindow::handleDateSelected(const QDate& date)
{
    QList<Schedule> schedules = calendar->showSchedulesForDate(date); // 일정 리스트 가져오기
    ScheduleListView* listView = new ScheduleListView(schedules, date, scheduleManager, categoryManager, this);

    connect(listView, &ScheduleListView::scheduleUpdated, this, [this](int scheduleId) {
        QList<Schedule> allSchedules = scheduleManager->getAllSchedules();
        calendar->setSchedules(allSchedules);
    });

    listView->exec();
}

void MainWindow::onSearchButtonClicked()
{
    SearchDialog dlg(scheduleManager, categoryManager, this);
    dlg.exec();
}

void MainWindow::onCategoryChanged()
{
    QList<Category> latestCategories = categoryManager->getAllCategories();
    calendar->setCategories(latestCategories);
}

MainWindow::~MainWindow()
{
    delete ui;
}
