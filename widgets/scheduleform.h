#ifndef SCHEDULEFORM_H
#define SCHEDULEFORM_H

#include <QDialog>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include "../models/schedule.h"

class ScheduleForm : public QDialog
{
    Q_OBJECT
public:
    explicit ScheduleForm(QWidget *parent = nullptr);
    Schedule getSchedule() const;

private:
    QLineEdit* m_titleEdit;
    QDateTimeEdit* m_startEdit;
    QDateTimeEdit* m_endEdit;
    QLineEdit* m_locationEdit;
    QTextEdit* m_memoEdit;

    QPushButton* m_okButton;
    QPushButton* m_cancelButton;

    void setupUI();
    void connectSignals();

private slots:
    void onOkClicked();
};

#endif // SCHEDULEFORM_H
