#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include <QKeyEvent>

#include "game/character.h"

class PlayerController : public QObject {
    Q_OBJECT
public:
    explicit PlayerController(Character* character, QObject* parent = nullptr);

public slots:
    void update();

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    Character* character;

    bool movingLeft = false;
    bool movingRight = false;
    bool jumping = false;
    bool blocking = false;
    bool attacking = false;
};

#endif // PLAYERCONTROLLER_H
