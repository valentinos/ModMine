#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QLabel>
#include "menu.h"
#include "about.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void SetCurrentRow(int i);

private slots:
    void on_listWidget_currentRowChanged(int i);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
