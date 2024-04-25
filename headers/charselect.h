#ifndef CHARSELECT_H
#define CHARSELECT_H

#include <QWidget>
#include <QVector>
#include <QTimer>

namespace Ui {
class CharSelect;
}

class CharSelect : public QWidget
{
    Q_OBJECT

public:
    explicit CharSelect(QWidget *parent = nullptr);
    explicit CharSelect(QVector<QPair<QString, QString>> charData, QWidget *parent = nullptr);
    ~CharSelect();

    void setUpClear();

    QWidget *readyOverlay;

signals:
    void on_backIcon_clicked();
    void cardSelected(const QString &color);
    void playersChose(const QString &name1, const QString &name2);
    void resetAllCards();
    void beginGame();

private slots:
    void updateDots();
    void handleCardClick(const QString &name);
    void handleSelectionDelay();
    void readyCheck();

private:
    void updateVersusText();

    Ui::CharSelect *ui;

    QTimer *dotTimer;
    QString choosingText = "Player 1 is choosing";
    int dotCount = 1;

    int choosingPlayer = 1;
    QHash<int, QString> player2color = {{1, "#ba1012"}, {2, "#1c5ad6"}};
    QString name1;
    QString name2;

    QTimer *selectionTimer;
};

#endif // CHARSELECT_H
