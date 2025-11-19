#include "categoryform.h"
#include "ui_categoryform.h"
#include <QMessageBox>
#include <QColorDialog>
#include <QPalette>
#include <QDebug> // 디버깅용

CategoryForm::CategoryForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CategoryForm)
{
    ui->setupUi(this);

    // 💡 UI 위젯 바인딩 (UI 파일이 수정되었다고 가정)
    // 1. ID 입력 필드 제거: UI에서 txtId를 삭제했으므로, 해당 코드 블록은 완전히 제거됩니다.
    // 2. Color 입력 필드 교체: txtColor 대신 새로운 위젯을 사용합니다.

    // UI에서 위젯을 가져와 멤버 변수에 연결 (UI 파일의 객체 이름에 따라 수정 필요)
    m_btnColorSelect = ui->btnSelectColor; // UI에 추가된 QPushButton
    m_lblColorPreview = ui->lblColorPreview; // UI에 추가된 QLabel

    // 초기 색상 설정 (기본값)
    m_selectedColor = "#FFFFFF"; // 흰색을 기본값으로 설정
    setColorPreview(m_selectedColor);
}

CategoryForm::~CategoryForm()
{
    delete ui;
}

// 색상 미리보기 라벨 업데이트
void CategoryForm::setColorPreview(const QString &hexColor)
{
    // 스타일시트만 사용하여 배경색 설정
    m_lblColorPreview->setStyleSheet(
        QString("border: 1px solid gray; background-color: %1;").arg(hexColor)
        );

    m_lblColorPreview->setText(" ");
    m_selectedColor = hexColor;
}

void CategoryForm::setCategory(const Category &category)
{
    m_category = category;

    // 💡 ID 노출 문제 해결: ID 관련 UI 접근 코드는 제거
    // 이전: ui->txtId->setText(QString::number(category.id())); -> 제거

    ui->txtTitle->setText(category.title());

    // Color: 저장된 색상 코드로 미리보기와 내부 변수 업데이트
    QString color = category.color();
    if (!color.isEmpty()) {
        setColorPreview(color);
    } else {
        setColorPreview("#FFFFFF"); // 저장된 색상이 없으면 기본값
    }
}

Category CategoryForm::category() const
{
    return m_category;
}

// 색상 선택 버튼 클릭 슬롯
void CategoryForm::on_btnSelectColor_clicked()
{
    // QColorDialog를 사용하여 색상 선택
    QColor initialColor(m_selectedColor); // 현재 선택된 색상을 초기값으로 사용
    QColor color = QColorDialog::getColor(initialColor, this, "카테고리 색상 선택");

    if (color.isValid()) {
        // 선택된 색상을 HEX 코드로 변환하여 저장
        QString hexColor = color.name(QColor::HexRgb);
        setColorPreview(hexColor);
    }
}


void CategoryForm::on_btnOk_clicked()
{
    if (ui->txtTitle->text().trimmed().isEmpty()) {
        QMessageBox::warning(this, "오류", "카테고리명을 입력하세요.");
        return;
    }

    // 1. Title 설정
    m_category.setTitle(ui->txtTitle->text());

    // 2. Color 설정 (선택된 색상 코드 사용)
    m_category.setColor(m_selectedColor);

    // 3. ID 설정: 새로운 카테고리(m_category.id() == -1 또는 0)일 경우 ID는 DB에서 부여되므로
    //    여기서는 기존 로직대로 유지합니다. (CategoryManager에서 처리됨)
    // 이전: if (ui->txtId && ui->txtId->text().isEmpty()) { m_category.setId(0); } -> 제거 (txtId 삭제)

    accept();
}

void CategoryForm::on_btnCancel_clicked()
{
    reject();
}
