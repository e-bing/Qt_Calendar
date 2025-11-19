#ifndef CATEGORYVIEW_H
#define CATEGORYVIEW_H

#include <QDialog>
#include "ui_categoryview.h"
#include <QStyledItemDelegate>
#include <QPainter>

#include "./models/category.h"
#include "./models/categorymanager.h"
#include "./categoryform.h"

namespace Ui {
class CategoryView;
}

// ----------------------------------------------------
// CategoryColorDelegate 클래스: 색상 코드 대신 색상을 표시하는 델리게이트
// ----------------------------------------------------
class CategoryColorDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit CategoryColorDelegate(QObject *parent = nullptr) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        // 0번 컬럼 (색상 컬럼)에만 적용
        if (index.column() == 0) {
            painter->save();

            // 색상 코드를 가져옵니다. (Qt::DisplayRole에 저장된 HEX 코드)
            QString hexColor = index.data(Qt::DisplayRole).toString();
            QColor color(hexColor);

            // 셀 영역의 여백을 고려한 사각형 영역 계산
            QRect colorRect = option.rect;
            int margin = 5;
            colorRect.setLeft(colorRect.left() + margin);
            colorRect.setRight(colorRect.right() - margin);
            colorRect.setTop(colorRect.top() + margin);
            colorRect.setBottom(colorRect.bottom() - margin);

            // 색상 채우기
            if (color.isValid()) {
                painter->fillRect(colorRect, color);
            } else {
                painter->fillRect(colorRect, Qt::white);
            }

            // 테두리 그리기
            painter->drawRect(colorRect);

            painter->restore();

        } else {
            // 다른 컬럼 (제목 컬럼)은 기본 그리기 동작을 따릅니다.
            QStyledItemDelegate::paint(painter, option, index);
        }
    }
};
// ----------------------------------------------------

class CategoryView : public QDialog
{
    Q_OBJECT

public:
    explicit CategoryView(CategoryManager *manager = nullptr, QWidget *parent = nullptr);
    ~CategoryView();

private:
    Ui::CategoryView *ui;
    CategoryManager *m_manager;
    QVector<Category> m_list;
    CategoryColorDelegate *m_colorDelegate; // 델리게이트 멤버 변수 선언

    void loadCategories();

private slots:
    void on_btnAdd_clicked();
    void on_btnEdit_clicked();
    void on_btnDelete_clicked();
};

#endif // CATEGORYVIEW_H
