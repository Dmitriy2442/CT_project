#include "PlayerController.h"

PlayerController::PlayerController(Character* character, QObject* parent)
    : QObject(parent), character(character) {
    // Убедитесь, что контроллер устанавливается как фильтр событий для объекта, который получает ввод с клавиатуры.
}

void PlayerController::update() {
    if (movingLeft) {
        character->moveLeft();
    }
    if (movingRight) {
        character->moveRight();
    }
    if (jumping) {
        character->jump();
    }
    if (blocking) {
        character->block();
    }
    if (attacking) {
        character->attack();
    }
}

bool PlayerController::eventFilter(QObject* obj, QEvent* event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        switch (keyEvent->key()) {
        case Qt::Key_Left:   // Движение влево
            movingLeft = true; break;
        case Qt::Key_Right:  // Движение вправо
            movingRight = true; break;
        case Qt::Key_Up:     // Прыжок
            jumping = true; break;
        case Qt::Key_Down:   // Блокирование
            blocking = true; break;
        case Qt::Key_Backslash:  // Атака
            attacking = true; break;
        default:
            return QObject::eventFilter(obj, event);  // Пропустить необработанные клавиши
        }
        return true;
    } else if (event->type() == QEvent::KeyRelease) { // Отпускание клавиши
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        switch (keyEvent->key()) {
        case Qt::Key_Left:
            movingLeft = false; break;
        case Qt::Key_Right:
            movingRight = false; break;
        case Qt::Key_Up:
            jumping = false; break;
        case Qt::Key_Down:
            blocking = false; break;
        case Qt::Key_Backslash:
            attacking = false; break;
        default:
            return QObject::eventFilter(obj, event);
        }
        return true;
    } else {
        return QObject::eventFilter(obj, event);  // Пропустить другие типы событий
    }
}
