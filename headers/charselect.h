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

signals:
    void on_backIcon_clicked();

private:
    Ui::CharSelect *ui;

};

#endif // CHARSELECT_H
