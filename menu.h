#ifndef MENU_H
#define MENU_H

#include "mainwindow.h"

namespace Ui {
    class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

signals :
    void ChangeRow(int i);

private slots:
    void on_AboutButton_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
