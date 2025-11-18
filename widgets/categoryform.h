#ifndef CATEGORYFORM_H
#define CATEGORYFORM_H

#include <QDialog>
#include "../models/category.h"

namespace Ui {
class CategoryForm;
}

class CategoryForm : public QDialog
{
    Q_OBJECT

public:
    explicit CategoryForm(QWidget *parent = nullptr);
    ~CategoryForm();

    void setCategory(const Category &category);  // 수정 시 데이터 로드
    Category category() const;                  // 폼 입력값을 Category로 반환

private slots:
    void on_btnOk_clicked();
    void on_btnCancel_clicked();

private:
    Ui::CategoryForm *ui;
    Category m_category;
};

#endif // CATEGORYFORM_H
