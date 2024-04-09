#ifndef COLORPALETTE_H
#define COLORPALETTE_H

#include <QColor>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QRandomGenerator>
#include <QDebug>

class ColorPalette
{
public:
    ColorPalette();
    ColorPalette(const QString &filePath);

    void resetIterator();
    QString getColor();
    qint8 getIterator();

private:
    QVector<QString> colors;
    qint8 colorIterator = 0;
    qint32 paletteSize = 7;
};

#endif // COLORPALETTE_H
