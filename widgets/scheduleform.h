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
#include "../models/categorymanager.h"
#include "../categoryview.h"

class ScheduleForm : public QDialog
{
    Q_OBJECT
public:
    explicit ScheduleForm(CategoryManager* categoryManager, QWidget *parent = nullptr);
    ScheduleForm(const Schedule& schedule, CategoryManager* categoryManager, QWidget* parent = nullptr);
    Schedule getSchedule() const;

private:
    QLineEdit* m_titleEdit;
    QDateTimeEdit* m_startEdit;
    QDateTimeEdit* m_endEdit;
    QLineEdit* m_locationEdit;
    QTextEdit* m_memoEdit;
    QComboBox* m_categoryCombo;
    CategoryManager* m_categoryManager;
    QList<Category> m_categories;
    QPushButton* m_okButton;
    QPushButton* m_cancelButton;
    QPushButton* m_addCategoryButton;

    void setupUI();
    void connectSignals();

private slots:
    void onOkClicked();
    void onAddCategoryClicked();
};

#endif // SCHEDULEFORM_H
