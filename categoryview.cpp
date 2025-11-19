#include "categoryview.h"
#include "ui_categoryview.h"

#include "./models/category.h"
#include "./models/categorymanager.h"
#include "./categoryform.h"

#include <QHeaderView>
#include <QMessageBox>

CategoryView::CategoryView(CategoryManager *manager, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::CategoryView)
    , m_manager(manager)
{
    ui->setupUi(this);
    setWindowTitle("카테고리 관리");

    // 1. UI 깔끔하게 하기: 테이블 설정
    ui->tableCategories->verticalHeader()->setVisible(false); // 행 번호 숨김
    ui->tableCategories->setColumnCount(2);

    // 컬럼 순서: 색상(0번) -> 제목(1번)
    ui->tableCategories->setColumnWidth(0, 80);  // 색상 컬럼 너비
    ui->tableCategories->setColumnWidth(1, 200); // 제목 컬럼 너비

    ui->tableCategories->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableCategories->horizontalHeader()->setStretchLastSection(false);

    ui->tableCategories->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableCategories->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableCategories->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableCategories->setAlternatingRowColors(true);

    if (!m_manager) {
        m_manager = new CategoryManager("category.db", this);
        m_manager->openDatabase();
    }

    ui->tableCategories->setHorizontalHeaderLabels({"색상", "제목"});

    // 2. 색상 코드 대신 실제 색상 표시: 델리게이트 적용 (0번 컬럼)
    m_colorDelegate = new CategoryColorDelegate(this);
    ui->tableCategories->setItemDelegateForColumn(0, m_colorDelegate);

    loadCategories();
}

CategoryView::~CategoryView()
{
    delete ui;
}

void CategoryView::loadCategories()
{
    m_list = m_manager->getAllCategories();
    ui->tableCategories->setRowCount(m_list.size());

    for (int i = 0; i < m_list.size(); i++) {
        // 0번 컬럼: 색상 코드 (델리게이트가 실제 색상으로 그림)
        QTableWidgetItem *colorItem = new QTableWidgetItem(m_list[i].color());
        colorItem->setTextAlignment(Qt::AlignCenter);
        ui->tableCategories->setItem(i, 0, colorItem);

        // 1번 컬럼: 제목
        ui->tableCategories->setItem(i, 1, new QTableWidgetItem(m_list[i].title()));
    }
}

// 3. 링커 오류 방지: 슬롯 함수의 구현체 (정의)
void CategoryView::on_btnAdd_clicked()
{
    CategoryForm dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        m_manager->addCategory(dialog.category());
        loadCategories(); // 목록 갱신
    }
}

void CategoryView::on_btnEdit_clicked()
{
    int row = ui->tableCategories->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "선택 오류", "수정할 카테고리를 선택하세요.");
        return;
    }

    CategoryForm dialog(this);
    dialog.setCategory(m_list[row]);

    if (dialog.exec() == QDialog::Accepted) {
        m_manager->updateCategory(dialog.category());
        loadCategories(); // 목록 갱신
    }
}

void CategoryView::on_btnDelete_clicked()
{
    int row = ui->tableCategories->currentRow();
    if (row < 0) {
        QMessageBox::warning(this, "선택 오류", "삭제할 카테고리를 선택하세요.");
        return;
    }

    if (QMessageBox::question(this, "삭제 확인", "선택된 카테고리를 정말 삭제하시겠습니까?",
                              QMessageBox::Yes | QMessageBox::No) == QMessageBox::No) {
        return;
    }

    m_manager->deleteCategory(m_list[row].id());
    loadCategories(); // 목록 갱신
}
