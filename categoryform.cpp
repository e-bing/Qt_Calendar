#include "categoryform.h"
#include "ui_categoryform.h"
#include <QMessageBox>

CategoryForm::CategoryForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CategoryForm)
{
    ui->setupUi(this);

    // 아이디는 UI에 표시만 하고 수정은 못 하도록 설정할 수도 있음 (선택)
    if (ui->txtId) {
        ui->txtId->setEnabled(false);
    }
}

CategoryForm::~CategoryForm()
{
    delete ui;
}

void CategoryForm::setCategory(const Category &category)
{
    m_category = category;

    if (ui->txtId)
        ui->txtId->setText(QString::number(category.id()));

    ui->txtTitle->setText(category.title());
    ui->txtColor->setText(category.color());
}

Category CategoryForm::category() const
{
    return m_category;
}

void CategoryForm::on_btnOk_clicked()
{
    if (ui->txtTitle->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "오류", "카테고리명을 입력하세요.");
        return;
    }

    m_category.setTitle(ui->txtTitle->text());
    m_category.setColor(ui->txtColor->text());
    accept();   // QDialog::Accepted 반환
}

void CategoryForm::on_btnCancel_clicked()
{
    reject();   // QDialog::Rejected 반환
}
