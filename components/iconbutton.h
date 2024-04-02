#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QPushButton>

class IconButton : public QPushButton
{
    Q_OBJECT
public:
    explicit IconButton(QWidget *parent = nullptr);

public slots:
    void onButtonClicked();

signals:
};

#endif // ICONBUTTON_H
