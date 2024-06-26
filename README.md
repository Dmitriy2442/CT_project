# CT_project
Курсовая работа по компьютерным технологиям 2курса ФРКТ МФТИ.  
Авторы:  
Тимченко Даниил  
Клименко Виталий  
Киркича Андрей  
Воложинов Дмитрий  
## Реализованные технологии
### Объектность языка
Для обработки взаимодействия различных частей программы используются элементы объектно-ориентированности.
В проекте используются классы:
Character - класс, отвечающий за поведение персонажа в игре, его скорость, здоровье и т.д.  
PlayerController - класс, отвечающий за управление персонажем, назначение клавиш, вызов функций управления.  
Arena - класс, содержащий в себе информацию об арене - фон и платформы.  
DBController - класс, содежащий в себе ссылку на базу данных и методы удобного обращения к ней.  
Вспомогательные классы attackZone и platfrom, отвечающий, соответственно, за информацию о зонах атаки и платформах.  
Также используются виджеты, каждые для своего раздела геймплея, воде Settings и Game, для настроек и игрового экрана соответственно.

### Многопоточность
Многопоточность реализована при помощи встроенных средств QT - класса QThread. На этапе создания MainWindow в другой поток выделяется взаимодействие с базой данных - оно будет происходить параллельно с выолнением основной программы.

### Стандартная библиотека
В проекте использовались элементы STL языка C++, адаптированные под QT, т.е. вместо vector использовались QVector, вместо pair - QPair и т.д.
Примеры применения:  
Методы initPos1 и initPos2 в классе Arena возвращают класс QPair т.е этот класс оптимален для возвращения пары двумерных координат.  
Вектор QVector platfroms хранит список текущих платформ на арене, так как количество платформ заранее неизвестно, но при этом нам необходимо проходить по структуре с ними по порядку для проверки коллизий в Character.  
Использование библиотеки cmath для вычисления абсолютного значения вреда атаки.

### Визуальный интерфейс
Сначала создаётся QStackedWidget, в который добавляются QWidget - страницы игрового интерфейса, некоторые из которых генерируются динамически в зависимости от введённых пользователем данных.
