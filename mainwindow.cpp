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

    CalendarView* calendar = new CalendarView(this);
    layout->addWidget(calendar);

    QString dbPath = QCoreApplication::applicationDirPath() + "/database/schedule.db";
    ScheduleManager* scheduleManager = new ScheduleManager(dbPath, this);

    // test code
    // Schedule* a = new Schedule(1, QString("일정이름"), QDateTime::currentDateTime(), QDateTime::currentDateTime(),
    //                            QString("서울"), QString("놀러감"));


    if (!scheduleManager->openDatabase()) {
        qWarning() << "DB 열기 실패";
        // 에러 처리 추가
        return;
    }

    // test code
    // scheduleManager->addSchedule(*a);

    // 스케줄 매니저에서 목록 할당
    QList<Schedule> schedules = scheduleManager->getAllSchedules();
    calendar->setSchedules(schedules);

    // // 날짜 선택 시 처리
    connect(calendar, &CalendarView::dateSelected,
            this, &MainWindow::handleDateSelected);

    // // 일정 선택 시 처리
    // connect(calendar, &CalendarView::scheduleSelected,
    //         this, &MainWindow::handleScheduleSelected);
}

void MainWindow::handleDateSelected(const QDate& date)
{
    QList<Schedule> schedules = calendar->showSchedulesForDate(date); // 일정 리스트 가져오기
    ScheduleListView* listView = new ScheduleListView(schedules, date, this);
    listView->exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}
