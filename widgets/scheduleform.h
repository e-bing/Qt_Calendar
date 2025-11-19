#ifndef SCHEDULEFORM_H
#define SCHEDULEFORM_H

#include <QDialog>
#include <QLineEdit>
#include <QDateTimeEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>
#include "../models/category.h"
#include "../models/schedule.h"

class ScheduleForm : public QDialog
{
    Q_OBJECT
public:
    explicit ScheduleForm(const QList<Category>& categories, QWidget *parent = nullptr);
    Schedule getSchedule() const;

private:
    QLineEdit* m_titleEdit;
    QDateTimeEdit* m_startEdit;
    QDateTimeEdit* m_endEdit;
    QLineEdit* m_locationEdit;
    QTextEdit* m_memoEdit;
    QComboBox* m_categoryCombo;
    QList<Category> m_categories;

    QPushButton* m_okButton;
    QPushButton* m_cancelButton;

    void setupUI();
    void connectSignals();

private slots:
    void onOkClicked();
};

#endif // SCHEDULEFORM_H
