#ifndef CATEGORYFORM_H
#define CATEGORYFORM_H

#include <QDialog>
#include <QPushButton> // 색상 선택 버튼을 위한 인클루드
#include <QLabel>      // 선택된 색상을 표시할 라벨 (또는 다른 위젯)
#include "./models/category.h"

namespace Ui {
class CategoryForm;
}

class CategoryForm : public QDialog
{
    Q_OBJECT

public:
    explicit CategoryForm(QWidget *parent = nullptr);
    ~CategoryForm();

    void setCategory(const Category &category);
    Category category() const;

private slots:
    void on_btnOk_clicked();
    void on_btnCancel_clicked();
    void on_btnSelectColor_clicked(); // 색상 선택 버튼 슬롯 추가

private:
    Ui::CategoryForm *ui;
    Category m_category;

    // UI 파일이 수정된다는 가정 하에, ui->txtColor 대신 사용할 멤버 변수 추가
    // QColorDialog를 열 버튼 (UI 파일에 추가해야 함)
    QPushButton *m_btnColorSelect;
    // 선택된 색상을 시각적으로 표시할 위젯 (UI 파일에 추가해야 함)
    QLabel *m_lblColorPreview;

    // UI 파일 수정 가이드:
    // 1. 기존의 txtColor (QLineEdit)을 제거합니다.
    // 2. QLineEdit 대신, 색상 미리보기용 QLabel (예: lblColorPreview)과 색상 선택용 QPushButton (예: btnSelectColor)을 배치합니다.
    // 3. (선택 사항) txtId (QLineEdit)을 제거하여 ID 노출 문제를 해결합니다.

    // 선택된 색상 코드를 저장할 private 변수 (Category 객체에 저장되기 전 임시 저장용)
    QString m_selectedColor;

    // 색상 미리보기 라벨의 배경색을 설정하는 도우미 함수
    void setColorPreview(const QString &hexColor);
};

#endif // CATEGORYFORM_H
