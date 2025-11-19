#ifndef CATEGORYMANAGER_H
#define CATEGORYMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QList>
#include <QVariantMap>
#include "category.h"
#include "../resources/styles/colors.h"

class CategoryManager : public QObject
{
    Q_OBJECT

public:
    explicit CategoryManager(const QString &dbPath, QObject *parent = nullptr);
    ~CategoryManager();

    bool openDatabase();    // DB 열기 + 테이블 생성.
    void closeDatabase();

    bool addCategory(const Category &category);
    bool updateCategory(const Category &category);
    bool deleteCategory(int id);

    QList<Category> getAllCategories();
    Category categoryFromQuery(const QVariantMap &record);
    Category getCategoryById(int id);

signals:
    void databaseError(const QString &msg);

private:
    QSqlDatabase m_database;
    QString m_dbPath;
};

#endif // CATEGORYMANAGER_H
