#ifndef CHARSELECT_H
#define CHARSELECT_H

#include "components/charactercard.h"

#include <QWidget>
#include <QVector>
#include <QTimer>

namespace Ui {
class CharSelect;
}

class CharSelect : public QWidget
{
    Q_OBJECT

public:
    explicit CharSelect(QWidget *parent = nullptr);
    ~CharSelect();

    QTimer *dotTimer;

signals:
    void on_backIcon_clicked();

private slots:
    void updateDots();
    void playerOneChoosing();
    void playerTwoChoosing();

private:
    Ui::CharSelect *ui;

    QString baseText = "Player 1 is choosing";
    int dotCount = 1;
};

#endif // CHARSELECT_H
