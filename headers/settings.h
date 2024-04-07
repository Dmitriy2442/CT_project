#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>

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
};

#endif // SETTINGS_H
