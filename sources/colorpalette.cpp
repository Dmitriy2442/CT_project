#include "../headers/colorpalette.h"

ColorPalette::ColorPalette()
{
    qDebug() << "ColorPalette Error: Palette path not specified!";
}

void ColorPalette::resetIterator() {
    colorIterator = QRandomGenerator::global()->bounded(colors.size());
}

qint8 ColorPalette::getIterator() {
    return colorIterator;
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

    colorIterator = QRandomGenerator::global()->bounded(colors.size());
    paletteSize = colors.size();
}

QString ColorPalette::getColor()
{
    colorIterator = ++colorIterator % paletteSize;
    return colors[colorIterator];
}
