#ifndef CHARACTERCARD_H
#define CHARACTERCARD_H

#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QGraphicsOpacityEffect>
#include <QDebug>

class CharacterCard : public QWidget
{
    Q_OBJECT
public:
    explicit CharacterCard(QWidget *parent = nullptr);
    CharacterCard(const QString &name, const QString &imagePath, QWidget *parent = nullptr);

signals:
    void cardClicked(const QString &name);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QString name;
    QString imagePath;
};

#endif // CHARACTERCARD_H
