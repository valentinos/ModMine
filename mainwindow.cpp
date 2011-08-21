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
    QObject::connect(menu, SIGNAL(ChangeRow(int)), this, SLOT(SetCurrentRow(int)));
    isMenu=true;
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
    if(isMenu)
        QObject::disconnect(widgetToDestroy, SIGNAL(ChangeRow(int)), this, SLOT(SetCurrentRow(int)));
    isMenu=false;
    widgetToDestroy->deleteLater(); //I need to destroy this widget because the layout don't
    QWidget *widgetToAdd;
    switch(i)
    {
        case 1:
            widgetToAdd = new Restore();
            break;
        case 3:
            widgetToAdd = new About();
            break;
        default:
            widgetToAdd = new Menu();
            QObject::connect(widgetToAdd, SIGNAL(ChangeRow(int)), this, SLOT(SetCurrentRow(int)));
            isMenu = true;
            break;
    }
    ui->horizontalLayout->addWidget(widgetToAdd);
}
