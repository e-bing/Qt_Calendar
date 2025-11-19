#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QListWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPushButton>

#include "../models/schedulemanager.h"
#include "../models/categorymanager.h"
#include "../widgets/schedulelistcell.h"
#include "../widgets/scheduledetailview.h"

class SearchDialog : public QDialog
{
    Q_OBJECT
public:
    SearchDialog(ScheduleManager* scheduleManager, CategoryManager* categoryManager, QWidget* parent = nullptr);

private slots:
    void onSearchClicked();
    void onResultItemClicked(QListWidgetItem* item);
    void onScheduleUpdated(int id);

private:
    QLineEdit* m_searchEdit;
    QPushButton* m_searchButton;
    QListWidget* m_resultList;
    QList<Schedule> m_currentResults;

    ScheduleManager* m_scheduleManager;
    CategoryManager* m_categoryManager;

    void setupUI();
};

#endif // SEARCHDIALOG_H
