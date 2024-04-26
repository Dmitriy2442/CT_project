#include "PlayerController.h"

PlayerController::PlayerController(Character* character, QObject* parent)
    : QObject(parent), character(character) {
    // Устанавливаем фильтр событий на объект, который будет принимать ввод с клавиатуры.
    // В обычной ситуации это может быть окно или виджет, где происходит игровой процесс.
}

bool PlayerController::eventFilter(QObject* obj, QEvent* event) {
    // Проверяем, что событие является событием нажатия клавиши
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        switch (keyEvent->key()) {
        case Qt::Key_Left:
            character->moveLeft();
            break;
        case Qt::Key_Right:
            character->moveRight();
            break;
        case Qt::Key_Up:
            character->jump();
            break;
        case Qt::Key_Control:
            character->attack();
            break;
        default:
            return QObject::eventFilter(obj, event);
        }
        return true; // Событие обработано
    } else {
        // Передать обработку другим обработчикам, если событие не является нажатием клавиши
        return QObject::eventFilter(obj, event);
    }
}
