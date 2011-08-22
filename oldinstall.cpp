#include "oldinstall.h"
#include "ui_oldinstall.h"

OldInstall::OldInstall(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OldInstall)
{
    ui->setupUi(this);
    downloadManager = new DownloadManager(this);
    ui->verticalLayout->addWidget(downloadManager);
}

OldInstall::~OldInstall()
{
    delete ui;
}
