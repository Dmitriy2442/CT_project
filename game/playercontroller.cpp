#include "PlayerController.h"

PlayerController::PlayerController(Character* character, QObject* parent)
    : QObject(parent), character(character)
{
    movingLeft = false;
    movingRight = false;
    jumping = false;
    blocking = false;
    attacking = false;
}

void PlayerController::update() {
    character->deathConditions();
    if (movingLeft) {
        character->accLeft();
    }
    if (movingRight) {
        character->accRight();
    }
    if (jumping) {
        character->jump();
    }
    if (attacking) {
        character->attack();
    }
    character->block(blocking);

    character->acceleration();
    character->movement();
    character->updateImage();
    // character->fixPosition(); // ЭТО ЧЕРТОВ КОСТЫЛЬ, НО ПУСТЬ ПЕРСОНАЖ ХОТЯ БЫ БУДЕТ НА ЭКРАНЕ
}

bool PlayerController::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        switch (keyEvent->key()) {
        case Qt::Key_A:   // Движение влево
            movingLeft = true; break;
        case Qt::Key_D:  // Движение вправо
            movingRight = true; break;
        case Qt::Key_W:     // Прыжок
            jumping = true; break;
        case Qt::Key_S:   // Блокирование
            blocking = true; break;
        case Qt::Key_Space:  // Атака
            attacking = true; break;
        default:
            return QObject::eventFilter(obj, event);
        }
        return true;
    } else if (event->type() == QEvent::KeyRelease) { // Отпускание клавиши
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        switch (keyEvent->key()) {
        case Qt::Key_A:
            movingLeft = false; break;
        case Qt::Key_D:
            movingRight = false; break;
        case Qt::Key_W:
            jumping = false; break;
        case Qt::Key_S:
            blocking = false; break;
        case Qt::Key_Space:
            attacking = false; break;
        default:
            return QObject::eventFilter(obj, event);
        }
        return true;
    } else {
        return QObject::eventFilter(obj, event);
    }
}
