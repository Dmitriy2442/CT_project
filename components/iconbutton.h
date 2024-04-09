#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QPushButton>
#include <QString>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QPainter>

class IconButton : public QPushButton {
    Q_OBJECT
public:
    IconButton(QWidget *parent = nullptr);

    void setIconFromFile(const QString &filePath, const QColor &color, const QSize &iconSize = QSize(80, 80));
    void updateColor(const QString &styleSheet, const QString &colorString, const QSize &iconSize = QSize(80, 80));

private:
    void updateImagePathFromStyleSheet(const QString& styleSheet);

    QString imagePath;
};

#endif // ICONBUTTON_H
