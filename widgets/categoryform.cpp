#include "CategoryForm.h"
//#include "ui_CategoryForm.h"
#include <QMessageBox>

CategoryForm::CategoryForm(QWidget *parent)
    : QDialog(parent)
    //, ui(new Ui::CategoryForm)
{
   // ui->setupUi(this);
}

CategoryForm::~CategoryForm()
{
   // delete ui;
}

// ///////////////////////////////////////////////////////////////////// //
// UI에서 카테고리 추가 버튼을 눌렀을 때
// CategoryForm dlg;
// if (dlg.exec() == QDialog::Accepted)
// {
//     categoryManager.addCategory(dlg.category());
// }

// UI에서 카테고리 수정 버튼을 눌렀을 때
// Category c = categoryManager.find(selectedId);
// CategoryForm dlg;
// dlg.setCategory(c);
// if (dlg.exec() == QDialog::Accepted)
// {
//     categoryManager.updateCategory(selectedId, dlg.category());
// }

// UI에서 카테고리 삭제 버튼을 눌렀을 때
// categoryManager.removeCategory(selectedId);
// ///////////////////////////////////////////////////////////////////// //



void CategoryForm::setCategory(const Category &category)
{
    m_category = category;
    // ui->txtId->setText(QString::number(category.id()));
    // ui->txtTitle->setText(category.title());
    // ui->txtColor->setText(category.color());
}

Category CategoryForm::category() const
{
    return m_category;
}

void CategoryForm::on_btnOk_clicked()
{
    // if (ui->txtTitle->text().isEmpty()) {
    //     QMessageBox::warning(this, "오류", "카테고리명을 입력하세요.");
    //     return;
    // }

    // m_category.setTitle(ui->txtTitle->text());
    // m_category.setColor(ui->txtColor->text());

    accept();
}

void CategoryForm::on_btnCancel_clicked()
{
    reject();
}
