#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include <QTimer>

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

    void pauseGame();
    void resumeGame();
    void endGame();

    void setupClear();

    QWidget *pauseMenu;
    QWidget *endGameMenu;

public slots:
    void updateGame();
    void playerDead(int id);
    void endGameButtonClicked();

    void getNames(const QString &name1, const QString &name2);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:

    Arena *arena;
    Character *player1;
    Character *player2;
    PlayerController *player1Controller;
    PlayerController *player2Controller;

    QVector<QString> names = {"", ""};

    QTimer *gameTimer;
    QGraphicsView *view;

    Ui::Game *ui;
};

#endif // GAME_H
