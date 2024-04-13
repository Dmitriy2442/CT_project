#ifndef CHARACTERCARD_H
#define CHARACTERCARD_H

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGraphicsOpacityEffect>
#include <QDebug>
#include <QPainter>

class CharacterCard : public QWidget
{
    Q_OBJECT
public:
    explicit CharacterCard(QWidget *parent = nullptr);
    CharacterCard(const QString &name, const QString &imagePath, QWidget *parent = nullptr);

    void clearCardColor();

public slots:
    void fixCardColor(const QColor &color);

signals:
    void cardClicked(const QString &name);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    QString name;
    QString imagePath;

    bool hover = false;
    bool fixColor = false;
    QColor color;
};

#endif // CHARACTERCARD_H
