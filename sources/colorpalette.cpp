#include "../headers/colorpalette.h"

ColorPalette::ColorPalette()
{
    qDebug() << "ColorPalette Error: Palette path not specified!";
}

ColorPalette::ColorPalette(const QString &filePath)
{
    QFile file(filePath);
    if (file.open(QIODevice::ReadOnly)) {
        QTextStream out(&file);
        while (!out.atEnd()) {
            QString line = out.readLine();
            QStringList parts = line.split(" ");
            if (parts.size() == 2) {
                colors.append(QString(parts[1]));
            }
        }
        file.close();
    }
}

QString ColorPalette::getColor()
{
    int randomIndex = QRandomGenerator::global()->bounded(colors.size());
    return colors[randomIndex];
}
