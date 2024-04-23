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
    void on_debugButton_clicked();

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::Game *ui;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QWidget *pauseMenu;
};

#endif // GAME_H
