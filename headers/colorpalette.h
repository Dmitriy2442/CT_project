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

    QColor getColor(const QString &colorName);

private:
    QVector<QColor> colors;
};

#endif // COLORPALETTE_H
