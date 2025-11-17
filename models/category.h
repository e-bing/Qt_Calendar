#ifndef CATEGORY_H
#define CATEGORY_H

#include <QString>

class Category
{
public:
    Category();
    Category(int id, const QString& title, const QString& color);

    // getter functions
    int id();
    QString title();
    QString color();

    // setter functions
    void setId(int num);
    void setTitle(const QString& title);
    void setColor(const QString& color);

private:
    int m_id;
    QString m_title;
    QString m_color;
};

#endif // CATEGORY_H
