#include "iconbutton.h"

IconButton::IconButton(QWidget *parent)
    : QPushButton(parent) {}

void IconButton::setIconFromFile(const QString &filePath, const QColor &color, const QSize &iconSize) {
    QImage img(filePath);

    // Создание нового изображения для иконки с указанным размером и прозрачным фоном
    QImage coloredImg(iconSize, QImage::Format_ARGB32);
    coloredImg.fill(Qt::transparent);

    QPainter painter(&coloredImg);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.drawImage(QRect(0, 0, iconSize.width(), iconSize.height()), img);

    // Изменение цвета иконки
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(coloredImg.rect(), color);
    painter.end();

    QIcon icon(QPixmap::fromImage(coloredImg));
    this->setIcon(icon);
    this->setIconSize(iconSize);
}

void IconButton::updateImagePathFromStyleSheet(const QString& styleSheet) {
    QRegularExpression re("border-image: url\\(([^)]+)\\);");
    QRegularExpressionMatch match = re.match(styleSheet);

    if (match.hasMatch()) {
        imagePath =  match.captured(1);
    } else {
        imagePath = QString();
    }
}

void IconButton::updateColor(const QString &styleSheet, const QString &colorString, const QSize &iconSize) {

    QColor color = QColor(colorString);

    this->updateImagePathFromStyleSheet(styleSheet);
    QImage img(imagePath);

    // Создание нового изображения для иконки с указанным размером и прозрачным фоном
    QImage coloredImg(iconSize, QImage::Format_ARGB32);
    coloredImg.fill(Qt::transparent);

    QPainter painter(&coloredImg);
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.drawImage(QRect(0, 0, iconSize.width(), iconSize.height()), img);

    // Изменение цвета иконки
    painter.setCompositionMode(QPainter::CompositionMode_SourceIn);
    painter.fillRect(coloredImg.rect(), color);
    painter.end();

    QIcon icon(QPixmap::fromImage(coloredImg));
    this->setIcon(icon);
    this->setIconSize(iconSize);
}
