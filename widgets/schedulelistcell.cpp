#include "schedulelistcell.h"

ScheduleListCell::ScheduleListCell(const Schedule& schedule, QWidget* parent)
    : QWidget(parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(8);

    // 카테고리 색상 세로 막대
    QWidget* colorBar = new QWidget(this);
    colorBar->setFixedWidth(6);
    colorBar->setStyleSheet("background: #f9c9a0; border-radius: 3px;");
    mainLayout->addWidget(colorBar);

    // 내용 영역
    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->setSpacing(2);

    // 1행: 시각 + 일정명
    QHBoxLayout* toprow = new QHBoxLayout;
    QLabel* timeLabel = new QLabel(schedule.startTime().toString("HH:mm"), this);
    timeLabel->setStyleSheet("color: #888; font-size:14px;");
    QLabel* titleLabel = new QLabel("<b>" + schedule.title() + "</b>", this);
    titleLabel->setStyleSheet("font-size:17px; margin-left:7px;");
    toprow->addWidget(timeLabel);
    toprow->addWidget(titleLabel);
    toprow->addStretch();
    vbox->addLayout(toprow);

    // 2행: 회색 장소/메모
    QString desc;
    if (!schedule.location().isEmpty()) desc += schedule.location();
    if (!schedule.memo().isEmpty()) {
        if (!desc.isEmpty()) desc += ", ";
        desc += schedule.memo();
    }
    QLabel* descLabel = new QLabel(desc, this);
    descLabel->setStyleSheet("color:#666; font-size:13px; margin-left:2px;");
    vbox->addWidget(descLabel);

    mainLayout->addLayout(vbox);
    mainLayout->addStretch();
    setLayout(mainLayout);
    setStyleSheet("background: #fff; border: 1px solid #f2f2f2; border-radius:8px;");
}
