#include "category.h"

Category::Category() : m_id(-1)     // 생성자 초기화 리스트
{}

Category::Category(int id, const QString& title, const QString& color) : m_id(id), m_title(title), m_color(color)
{
}

// getter functions
int Category::id() const
{
    return m_id;
}

QString Category::title() const
{
    return m_title;
}

QString Category::color() const
{
    return m_color;
}

// setter functions
void Category::setId(int num)
{
    m_id = num;
}

void Category::setTitle(const QString& title)
{
    m_title = title;
}

void Category::setColor(const QString& color)
{
    m_color = color;
}
