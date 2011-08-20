#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtGui/QListWidget>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Menu *menu = new Menu(this);
    ui->horizontalLayout->addWidget(menu);
}

MainWindow::~MainWindow()
{
    delete ui;
}
