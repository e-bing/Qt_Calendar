#ifndef CATEGORYFORM_H
#define CATEGORYFORM_H

#include <QDialog>
#include "./models/category.h"   // Category 모델 포함

namespace Ui {
class CategoryForm;
}

class CategoryForm : public QDialog
{
    Q_OBJECT

public:
    explicit CategoryForm(QWidget *parent = nullptr);
    ~CategoryForm();

    void setCategory(const Category &category);   // 기존 데이터 로드 (수정용)
    Category category() const;                   // 입력된 데이터 반환

private slots:
    void on_btnOk_clicked();
    void on_btnCancel_clicked();

private:
    Ui::CategoryForm *ui;
    Category m_category;  // 현재 작업 중인 카테고리 데이터
};

#endif // CATEGORYFORM_H
