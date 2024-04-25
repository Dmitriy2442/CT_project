#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QGraphicsTextItem>
#include <QTimer>



namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

signals:
    void endGameSignal();

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

    void startGame();
    void pauseGame();
    void resumeGame();
    void endGame();

public slots:
    void endGameButtonClicked();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void updateView();

    Ui::Game *ui;

    // Arena *arena;
    // QVector<Character*> characters;
    // GameController *gameController;
    QTimer *gameTimer;

    QWidget *pauseMenu;
};

#endif // GAME_H
