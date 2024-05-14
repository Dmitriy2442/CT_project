#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include <QTimer>
#include <QMediaPlayer>
#include <QAudioOutput>

#include "game/arena.h"
#include "game/character.h"
#include "game/playercontroller.h"

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

signals:
    void updateTick();
    void endGameSignal();

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

    void startGame();
    void pauseGame();
    void resumeGame();
    void endGame();

public slots:
    void updateGame();
    void endGameButtonClicked();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:

    Ui::Game *ui;

    Arena *arena;
    Character *player1;
    Character *player2;
    PlayerController *player1Controller;
    PlayerController *player2Controller;

    QTimer *gameTimer;
    QGraphicsView *view;

    QWidget *pauseMenu;
};

#endif // GAME_H
