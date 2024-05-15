   #include "headers/mainwindow.h"
#include "qapplication.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Установка шрифта по умолчанию
    int fontId = QFontDatabase::addApplicationFont(":/fonts/nightmare.ttf");
    if (fontId != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QApplication::setFont(QFont("Bauhaus 93")); // Not using nightmare, bauhaus is more retrowave
    } else {
        qDebug() << "Warning, failed to load font.";
    }

    MainWindow w;
    w.show();

    return a.exec();
}
