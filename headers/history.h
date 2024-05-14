#ifndef HISTORY_H
#define HISTORY_H

#include <QWidget>

namespace Ui {
class HistoryForm;
}

class HistoryForm : public QWidget
{
    Q_OBJECT

public:
    HistoryForm(QWidget *parent = nullptr);
    HistoryForm(QVector<QVector<QString>> matches, QWidget *parent = nullptr);
    ~HistoryForm();

public slots:
    void updateHistory(QVector<QVector<QString>> matches);

signals:
    void on_backIcon_clicked();

private:
    void updateMatches();

    Ui::HistoryForm *ui;

    QVector<QVector<QString>> matches;
};

#endif // HISTORY_H
