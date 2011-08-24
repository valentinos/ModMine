#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui/QListWidget>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    blocked = false;
    ui->setupUi(this);
    Menu *menu = new Menu();
    ui->horizontalLayout->addWidget(menu);
    QObject::connect(menu, SIGNAL(ChangeRow(int)), this, SLOT(SetCurrentRow(int)));
    widgetType = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
 {
    if(blocked)
        event->ignore();
    else
        event->accept();
 }

void MainWindow::SetCurrentRow(int i)
{
    if(i<0 or i>3)
        ui->listWidget->setCurrentRow(0);
    ui->listWidget->setCurrentRow(i);
}

void MainWindow::Block(bool block)
{
    blocked = block;
    ui->listWidget->setDisabled(block);
}

void MainWindow::on_listWidget_currentRowChanged(int i)
{
    QWidget *widgetToDestroy = ui->horizontalLayout->itemAt(1)->widget();
    ui->horizontalLayout->removeItem(ui->horizontalLayout->itemAt(1));
    switch(widgetType)
    {
        case 0:
            QObject::disconnect(widgetToDestroy, SIGNAL(ChangeRow(int)), this, SLOT(SetCurrentRow(int)));
            break;
        case 2:
            QObject::disconnect(widgetToDestroy, SIGNAL(SetBlocked(bool)), this, SLOT(Block(bool)));
            break;
        default:
            break;
    }
    widgetToDestroy->deleteLater(); //I need to destroy this widget because the layout don't
    QWidget *widgetToAdd;
    switch(i)
    {
        case 1:
            widgetToAdd = new Restore();
            break;
        case 2:
            widgetToAdd = new OldInstall();
            QObject::connect(widgetToAdd, SIGNAL(SetBlocked(bool)), this, SLOT(Block(bool)));
            break;
        case 3:
            widgetToAdd = new About();
            break;
        default:
            widgetToAdd = new Menu();
            QObject::connect(widgetToAdd, SIGNAL(ChangeRow(int)), this, SLOT(SetCurrentRow(int)));
            break;
    }
    widgetType = i;
    ui->horizontalLayout->addWidget(widgetToAdd);
}
