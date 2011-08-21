#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui/QListWidget>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Menu *menu = new Menu();
    ui->horizontalLayout->addWidget(menu);
    SetCurrentRow(3);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SetCurrentRow(int i)
{
    if(i<0 or i>3)
        ui->listWidget->setCurrentRow(0);
    else
        ui->listWidget->setCurrentRow(i);
}

void MainWindow::on_listWidget_currentRowChanged(int i)
{
    QWidget *widgetToDestroy = ui->horizontalLayout->itemAt(2)->widget();
    ui->horizontalLayout->removeItem(ui->horizontalLayout->itemAt(2));
    widgetToDestroy->deleteLater(); //I need to destroy this widget because the layout don't
    QWidget *widgetToAdd;
    switch(i)
    {
        case 3:
            widgetToAdd = new About();
            break;
        default:
            widgetToAdd = new Menu();
            break;
    }
    ui->horizontalLayout->addWidget(widgetToAdd);
}
