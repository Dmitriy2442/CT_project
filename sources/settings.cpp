#include "headers/settings.h"
#include "../ui/ui_settings.h"

SettingsForm::SettingsForm(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SettingsForm)
{
    ui->setupUi(this);

    ui->volumeSlider->setRange(0, 100);
    ui->volumeSlider->setValue(100);
    volume = ui->volumeSlider->sliderPosition();
}

SettingsForm::~SettingsForm()
{
    delete ui;
}
