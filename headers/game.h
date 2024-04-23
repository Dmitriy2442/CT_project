#ifndef GAME_H
#define GAME_H

#include <QWidget>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include <QTimer>

#include "headers/gamemodel.h"

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

signals:
    void endGame();

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

public slots:
    void endGameButtonClicked();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void resumeGame();
    void pauseGame();
    void updateView();

    Ui::Game *ui;

    QGraphicsScene *scene;
    QGraphicsView *view;
    QWidget *pauseMenu;

    GameModel *model; // Модель игры, не должна содержать никакой логики отрисовки (GUI)
    QTimer *updateTime; // Таймер обновления игры (60 FPS)
};

#endif // GAME_H
