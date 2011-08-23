#include "oldinstall.h"
#include "ui_oldinstall.h"

OldInstall::OldInstall(QWidget *parent) :
    DownloadWidget(parent),
    ui(new Ui::OldInstall)
{
    ui->setupUi(this);
    ui->verticalLayout->addWidget(downloadManager);
}

OldInstall::~OldInstall()
{
    delete ui;
}
