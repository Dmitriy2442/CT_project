#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include <QKeyEvent>

#include "game/character.h"

class PlayerController : public QObject {
    Q_OBJECT
public:
    explicit PlayerController(Character* character, QObject* parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    Character* character;
};

#endif // PLAYERCONTROLLER_H
