#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    CalendarView* calendar = new CalendarView(this);
    layout->addWidget(calendar);

    QString dbPath = QCoreApplication::applicationDirPath() + "/database/schedule.db";
    ScheduleManager* scheduleManager = new ScheduleManager(dbPath, this);

    if (!scheduleManager->openDatabase()) {
        qWarning() << "DB 열기 실패";
        // 에러 처리 추가
        return;
    }

    // 스케줄 매니저에서 목록 할당
    QList<Schedule> schedules = scheduleManager->getAllSchedules();
    calendar->setSchedules(schedules);

    // // 날짜 선택 시 처리
    // connect(calendar, &CalendarView::dateSelected,
    //         this, &MainWindow::handleDateSelected);

    // // 일정 선택 시 처리
    // connect(calendar, &CalendarView::scheduleSelected,
    //         this, &MainWindow::handleScheduleSelected);
}

MainWindow::~MainWindow()
{
    delete ui;
}
