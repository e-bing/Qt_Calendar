#ifndef CATEGORYVIEW_H
#define CATEGORYVIEW_H

#include <QWidget>
#include "ui_categoryview.h"

#include "./models/category.h"
#include "./models/categorymanager.h"
#include "./widgets/categoryform.h"



namespace Ui {
class CategoryView;
}

class CategoryView : public QWidget
{
    Q_OBJECT

public:
    explicit CategoryView(QWidget *parent = nullptr);
    ~CategoryView();

private:
    Ui::CategoryView *ui;
    CategoryManager *m_manager;
    QVector<Category> m_list;

    void loadCategories();

private slots:
    void on_btnAdd_clicked();
    void on_btnEdit_clicked();
    void on_btnDelete_clicked();
};

#endif // CATEGORYVIEW_H
