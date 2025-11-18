#include "schedulelistcell.h"

ScheduleListCell::ScheduleListCell(const Schedule& schedule, QWidget* parent)
    : QWidget(parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    mainLayout->setContentsMargins(0,3,0,0);
    mainLayout->setSpacing(8);

    // 카테고리 색상 세로 막대
    QWidget* colorBar = new QWidget(this);
    colorBar->setFixedWidth(6);
    colorBar->setStyleSheet(QString("background: %1; border-radius: 3px;")
                                .arg(COLOR_PRIMARY)); // 막대 색상, 나중에 카테고리에서 불러오는 코드로 변경
    mainLayout->addWidget(colorBar);

    // 내용 영역
    QVBoxLayout* vbox = new QVBoxLayout;
    vbox->setSpacing(1);

    // 시각, 일정명
    QHBoxLayout* toprow = new QHBoxLayout;
    QLabel* timeLabel = new QLabel(schedule.startTime().toString("HH:mm"), this);
    timeLabel->setStyleSheet(QString("color: %1; font-size:14px; background-color:transparent; border:none;")
                                 .arg(COLOR_SECONDARY));
    QLabel* titleLabel = new QLabel("<b>" + schedule.title() + "</b>", this);
    titleLabel->setStyleSheet("font-size:17px; margin-left:7px; background-color:transparent; border:none;");
    toprow->addWidget(timeLabel);
    toprow->addWidget(titleLabel);
    toprow->addStretch();
    vbox->addLayout(toprow);

    // 장소, 설명
    QHBoxLayout* descRow = new QHBoxLayout;
    QLabel* timeSpacer = new QLabel(this);
    timeSpacer->setFixedWidth(timeLabel->sizeHint().width() + 7); // 7=margin-left
    timeSpacer->setStyleSheet("background-color:transparent; border:none;");
    descRow->addWidget(timeSpacer);

    QString desc;
    if (!schedule.location().isEmpty()) desc += schedule.location();
    if (!schedule.memo().isEmpty()) {
        if (!desc.isEmpty()) desc += ", ";
        desc += schedule.memo();
    }
    QLabel* descLabel = new QLabel(desc, this);
    descLabel->setStyleSheet(QString("color:%1; font-size:13px; margin-left:2px; background-color:transparent; border:none;")
                                 .arg(COLOR_GRAY)); // 장소, 설명 폰트 색상
    descRow->addWidget(descLabel);
    descRow->addStretch();

    vbox->addLayout(descRow);

    mainLayout->addLayout(vbox);
    mainLayout->addStretch();
    setLayout(mainLayout);
    setStyleSheet(QString("background: %1; border: 1px solid %2; border-radius:8px;")
                      .arg(COLOR_BACKGROUND) // 배경 색상
                      .arg(COLOR_BACKGROUND)); // 선 색상
}
