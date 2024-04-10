#ifndef CHARSELECT_H
#define CHARSELECT_H

#include <QWidget>

namespace Ui {
class CharSelect;
}

class CharSelect : public QWidget
{
    Q_OBJECT

public:
    explicit CharSelect(QWidget *parent = nullptr);
    ~CharSelect();

private:
    Ui::CharSelect *ui;
};

#endif // CHARSELECT_H
