#include "mainwindow.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int fontId = QFontDatabase::addApplicationFont(":/styles/Pretendard-Medium.ttf");

    if (fontId == -1)
    {
        qWarning("폰트 설정에 실패했습니다.");
    } else
    {
        QString family = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont font(family);
        a.setFont(font);
    }

    MainWindow w;
    w.show();
    return a.exec();
}
