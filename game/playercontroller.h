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
    // Обработка состояния персонажа
    void update();

protected:
    // Перехват событий клавиатуры
    bool eventFilter(QObject* obj, QEvent* event) override;

private:
    // Графическая модель персонажа (внутри есть хитбокс)
    Character* character;

    // Флаги обновления состояния персонажа
    bool movingLeft;
    bool movingRight;
    bool jumping;
    bool blocking;
    bool attacking;
};

#endif // PLAYERCONTROLLER_H
