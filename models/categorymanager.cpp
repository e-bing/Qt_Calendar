#include "CategoryManager.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDir>
#include <QFileInfo>

CategoryManager::CategoryManager(const QString &dbPath, QObject *parent)
    : QObject(parent), m_dbPath(dbPath)
{
    if (!QSqlDatabase::contains("shared_connection"))
    {
        m_database = QSqlDatabase::addDatabase("QSQLITE", "shared_connection");
        m_database.setDatabaseName(m_dbPath);
    }
}

CategoryManager::~CategoryManager()
{
    QSqlDatabase::database("shared_connection").close();
    QSqlDatabase::removeDatabase("shared_connection");
}

bool CategoryManager::openDatabase()
{
    QString dbDir = QFileInfo(m_dbPath).absolutePath();
    if (!QDir(dbDir).exists()) QDir().mkpath(dbDir);

    if (!m_database.open()) {
        qDebug() << "DB 열기 실패:" << m_database.lastError().text();
        return false;
    }

    // 테이블 생성
    QSqlQuery query(m_database);
    QString sql = R"(
        CREATE TABLE IF NOT EXISTS categories (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            title TEXT NOT NULL,
            color TEXT
        )
    )";

    if (!query.exec(sql)) {
        qDebug() << "테이블 생성 실패:" << query.lastError().text();
        return false;
    }

    QSqlQuery checkQuery(m_database);
    if (checkQuery.exec("SELECT COUNT(*) FROM categories") && checkQuery.next()) {
        int count = checkQuery.value(0).toInt();
        if (count == 0) {
            // 카테고리가 없으면 생성
            addCategory(Category(-1, "일반", COLOR_PRIMARY));
        }
    } else {
        qDebug() << "카테고리 개수 조회 실패:" << checkQuery.lastError().text();
    }

    return true;
}

void CategoryManager::closeDatabase()
{
    if (m_database.isOpen()) m_database.close();
}

bool CategoryManager::addCategory(const Category &category)
{
    QSqlQuery query(m_database);
    query.prepare("INSERT INTO categories (title, color) VALUES (?, ?)");
    query.addBindValue(category.title());
    query.addBindValue(category.color());

    if (!query.exec()) {
        qDebug() << "카테고리 추가 실패:" << query.lastError().text();
        return false;
    }

    return true;
}

bool CategoryManager::deleteCategory(int id)
{
    QSqlQuery query(m_database);
    query.prepare("DELETE FROM categories WHERE id = ?");
    query.addBindValue(id);

    if (!query.exec()) {
        emit databaseError("Failed to delete category: " + query.lastError().text());
        return false;
    }

    return true;
}

QList<Category> CategoryManager::getAllCategories()
{
    QList<Category> list;
    QSqlQuery query(m_database);

    if (!query.exec("SELECT id, title, color FROM categories ORDER BY id")) {
        qDebug() << "카테고리 조회 실패:" << query.lastError().text();
        return list;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        QString title = query.value("title").toString();
        QString color = query.value("color").toString();
        list.append(Category(id, title, color));
    }

    return list;
}
