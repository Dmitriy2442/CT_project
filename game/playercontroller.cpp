#include "PlayerController.h"

PlayerController::PlayerController(int playerId, Character* character, QObject* parent)
    : QObject(parent), character(character)
{
    movingLeft = false;
    movingRight = false;
    jumping = false;
    blocking = false;
    attacking = false;

    id = playerId;
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

    character->attackUpdate();
    character->acceleration();
    character->movement();
    character->updateImage();
    // character->fixPosition(); // ЭТО ЧЕРТОВ КОСТЫЛЬ, НО ПУСТЬ ПЕРСОНАЖ ХОТЯ БЫ БУДЕТ НА ЭКРАНЕ
}

bool PlayerController::eventFilter(QObject* obj, QEvent* event) {
    if (id == 0) {
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
    else if (id == 1) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            switch (keyEvent->key()) {
            case Qt::Key_J:   // Движение влево
                movingLeft = true; break;
            case Qt::Key_L:  // Движение вправо
                movingRight = true; break;
            case Qt::Key_I:     // Прыжок
                jumping = true; break;
            case Qt::Key_K:   // Блокирование
                blocking = true; break;
            case Qt::Key_N:  // Атака
                attacking = true; break;
            default:
                return QObject::eventFilter(obj, event);
            }
            return true;
        } else if (event->type() == QEvent::KeyRelease) { // Отпускание клавиши
            QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
            switch (keyEvent->key()) {
            case Qt::Key_J:
                movingLeft = false; break;
            case Qt::Key_L:
                movingRight = false; break;
            case Qt::Key_I:
                jumping = false; break;
            case Qt::Key_K:
                blocking = false; break;
            case Qt::Key_N:
                attacking = false; break;
            default:
                return QObject::eventFilter(obj, event);
            }
            return true;
        } else {
            return QObject::eventFilter(obj, event);
        }
    }
}
