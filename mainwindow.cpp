#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QVBoxLayout>

// test code
#include <QString>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setStyleSheet("background-color: " + COLOR_BACKGROUND);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    calendar = new CalendarView(this);
    layout->addWidget(calendar);

    QString dbPath = QCoreApplication::applicationDirPath() + "/database/schedule.db";
    categoryManager = new CategoryManager(dbPath, this);

    if (!categoryManager->openDatabase()) {
        qDebug() << "카테고리 데이터베이스 열기 실패";
        // 에러 처리
        return;
    }

    // test code
    // Category* b = new Category(1, QString("개인"), QString("#a3d6b1"));
    // Category* c = new Category(2, QString("회사"), QString("#a3bad6"));
    // categoryManager->addCategory(*b);
    // categoryManager->addCategory(*c);

    // categoryManager->deleteCategory(1);
    // categoryManager->deleteCategory(2);

    scheduleManager = new ScheduleManager(dbPath, this);

    if (!scheduleManager->openDatabase()) {
        qWarning() << "DB 열기 실패";
        // 에러 처리 추가
        return;
    }

    // Schedule* a = new Schedule(1, QString("일정이름"), QDateTime::currentDateTime(), QDateTime::currentDateTime(),
    //                            QString("서울"), QString("맛있는 거 먹기"), 1);
    // scheduleManager->addSchedule(*a);

    // 스케줄 매니저에서 목록 할당
    QList<Schedule> schedules = scheduleManager->getAllSchedules();
    calendar->setSchedules(schedules);

    // 날짜 선택 시 처리
    connect(calendar, &CalendarView::dateSelected,
            this, &MainWindow::handleDateSelected);

    // 일정 선택 시 처리
    // connect(calendar, &CalendarView::scheduleSelected,
    //         this, &MainWindow::handleScheduleSelected);
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

MainWindow::~MainWindow()
{
    delete ui;
}
