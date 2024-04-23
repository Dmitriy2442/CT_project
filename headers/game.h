#ifndef GAME_H
#define GAME_H

#include <QWidget>

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QKeyEvent>

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
    void on_endGameButton_clicked();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void hidePauseMenu();
    void showPauseMenu();

    Ui::Game *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QWidget *pauseMenu;
};

#endif // GAME_H
