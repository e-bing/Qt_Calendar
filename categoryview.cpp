#include "./categoryview.h"
#include "./ui_categoryview.h"
#include "./ui_categoryform.h"

#include "./models/category.h"
#include "./models/categorymanager.h"
#include "./categoryform.h"

CategoryView::CategoryView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::CategoryView)
{
    ui->setupUi(this);
    ui->tableCategories->horizontalHeader()->setStretchLastSection(true);
    ui->tableCategories->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableCategories->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableCategories->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableCategories->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableCategories->setAlternatingRowColors(true);
    ui->tableCategories->setStyleSheet("alternate-background-color: #ffffff;");
    m_manager = new CategoryManager("category.db", this);
    m_manager->openDatabase();

    ui->tableCategories->setColumnCount(2);
    ui->tableCategories->setHorizontalHeaderLabels({"제목", "색상"});

    loadCategories();
}

void CategoryView::on_btnAdd_clicked()
{
    CategoryForm form(this);
    if (form.exec() == QDialog::Accepted) {
        m_manager->addCategory(form.category());
        loadCategories();
    }
}

void CategoryView::on_btnEdit_clicked()
{
    int row = ui->tableCategories->currentRow();
    if (row < 0) return;

    CategoryForm form(this);
    form.setCategory(m_list[row]);

    if (form.exec() == QDialog::Accepted) {
        m_manager->updateCategory(form.category());
        loadCategories();
    }
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
        ui->tableCategories->setItem(i, 0, new QTableWidgetItem(m_list[i].title()));
        ui->tableCategories->setItem(i, 1, new QTableWidgetItem(m_list[i].color()));
    }
}


void CategoryView::on_btnDelete_clicked()
{
    int row = ui->tableCategories->currentRow();
    if (row < 0) return;

    m_manager->deleteCategory(m_list[row].id());
    loadCategories();
}
