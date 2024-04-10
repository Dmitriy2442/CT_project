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
    explicit CharacterCard(const QString &name, const QString &imagePath, QWidget *parent = nullptr);

signals:
};

#endif // CHARACTERCARD_H
