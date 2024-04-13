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
    void fixCard(const QString &color);
    bool isBlocked();

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
    QColor color;

    bool hover = false;
    bool fixColor = false;
    bool blocked = false;
};

#endif // CHARACTERCARD_H
