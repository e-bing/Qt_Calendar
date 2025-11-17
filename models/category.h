#ifndef CATEGORY_H
#define CATEGORY_H

#include <QObject>

class Category : public QObject
{
    Q_OBJECT
public:
    explicit Category(QObject *parent = nullptr);

signals:
};

#endif // CATEGORY_H
