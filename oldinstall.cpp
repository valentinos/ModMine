#include "oldinstall.h"
#include "ui_oldinstall.h"

OldInstall::OldInstall(QWidget *parent) :
    DownloadWidget(parent),
    ui(new Ui::OldInstall)
{
    ui->setupUi(this);
    ui->verticalLayout->addWidget(downloadManager);

    if(!UpdateList())
        QMessageBox::critical(this, trUtf8("Erreur"), trUtf8("Veuillez vérifier que vous êtes bien connecté à Internet."));

}

OldInstall::~OldInstall()
{
    delete ui;
}

void OldInstall::on_RefreshButton_clicked()
{
    if(!UpdateList())
        QMessageBox::critical(this, trUtf8("Erreur"), trUtf8("Veuillez vérifier que vous êtes bien connecté à Internet."));
}

bool OldInstall::UpdateList()
{
    SetButtonDisabled(true);
    QNetworkReply *download = downloadManager->Download("http://valentinos.byethost17.com/ModMine/MineVersion/version.txt");
    SetButtonDisabled(false);
    if(download==NULL)
        return false;
    ui->listWidget->addItems(QString(download->readAll()).split("\n"));
    ui->listWidget->setCurrentRow(0);
    ui->listWidget->setRowHidden(ui->listWidget->count()-1, true);
    return true;
}

void OldInstall::SetButtonDisabled(bool enable)
{
    ui->InstallButton->setEnabled(!enable);
    ui->RefreshButton->setEnabled(!enable);
}
