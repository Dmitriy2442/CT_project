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
    // Это плохая реализация, её нужно улучшить (переделать)
    if (movingLeft) {
        character->accLeft();
    }
    if (movingRight) {
        character->accRight();
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
    character->acceleration();
    character->updateImage();
    character->fixPosition(); // ЭТО ЧЕРТОВ КОСТЫЛЬ, НО ПУСТЬ ОН БУДЕТ ХОТЯ БЫ НА ЭКРАНЕ
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
        case Qt::Key_Slash:  // Атака
            attacking = true; break;
        default:
            return QObject::eventFilter(obj, event);
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
        case Qt::Key_Slash:
            attacking = false; break;
        default:
            return QObject::eventFilter(obj, event);
        }
        return true;
    } else {
        return QObject::eventFilter(obj, event);
    }
}
