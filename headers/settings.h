#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
#include <QSlider>

namespace Ui {
class SettingsForm;
}

class SettingsForm : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsForm(QWidget *parent = nullptr);
    ~SettingsForm();

private:
    Ui::SettingsForm *ui;

    int volume;
};

#endif // SETTINGS_H
