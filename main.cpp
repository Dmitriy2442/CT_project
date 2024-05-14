#include "headers/mainwindow.h"
#include "qapplication.h"

#include <QApplication>
#include <QFontDatabase>
#include <QMediaPlayer>
#include <QAudioOutput>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Установка шрифта по умолчанию
    int fontId = QFontDatabase::addApplicationFont(":/fonts/nightmare.ttf");
    if (fontId != -1) {
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QApplication::setFont(QFont(fontFamily));
    } else {
        qDebug() << "Warning, failed to load font.";
    }

    QMediaPlayer * player = new QMediaPlayer;
    QAudioOutput * output = new QAudioOutput;

    player->setAudioOutput(output);
    player->setSource(QUrl("qrc:/sounds/music.wav"));

    output->setVolume(100);

    player->play();

    MainWindow w;
    w.show();

    return a.exec();
}
