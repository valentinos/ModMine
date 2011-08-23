#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QLabel>
#include "menu.h"
#include "about.h"
#include "restore.h"
#include "oldinstall.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void SetCurrentRow(int i);
    void Block(bool block);
    void on_listWidget_currentRowChanged(int i);

private:
    Ui::MainWindow *ui;
    int widgetType;//widgetType is the actual widget row number
    bool blockedMenu;
};

#endif // MAINWINDOW_H
