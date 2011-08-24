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

void OldInstall::on_InstallButton_clicked()
{
    SetButtonDisabled(true);
    if(QMessageBox::question(this, trUtf8("Installation de minecraft"), trUtf8("L'installation d'une nouvelle version de minecraft supprimera la précédente. Êtes-vous surs de vouloir continuer quand même ?"), QMessageBox::Yes | QMessageBox::No)!=QMessageBox::Yes)
    {
        SetButtonDisabled(false);
    }
    QString version;
    version = ui->listWidget->currentItem()->text();
    if(EasyFile::GetMinecraftDirectory().isEmpty())
    {
        QMessageBox::critical(this,trUtf8("Erreur"), trUtf8("Une erreur s'est produite, il semble que votre système ne soit pas supporté."));
        SetButtonDisabled(false);
        return;
    }
    QDir minecraftDirectory(EasyFile::GetMinecraftDirectory());
    if(!minecraftDirectory.exists(".minecraft/bin/"))
    {
        if(!minecraftDirectory.exists(".minecraft/"))
            minecraftDirectory.mkdir(".minecraft");
        minecraftDirectory.mkdir(".minecraft/bin");
    }
    if(minecraftDirectory.exists(".minecraft/bin/minecraft.jar"))
        minecraftDirectory.remove(".minecraft/bin/minecraft.jar");
    QString downloadUrl = "http://valentinos.byethost17.com/ModMine/MineVersion/";
    downloadUrl+=version+".jar";
    QNetworkReply *reply=downloadManager->Download(downloadUrl);
    if(reply==NULL)
    {
        QMessageBox::critical(this,trUtf8("Erreur"), trUtf8("Une erreur s'est produite, veuillez vérifier que vous êtes bien connectés à internet."));
        SetButtonDisabled(false);
        return;
    }
    QFile* jarMinecraft = new QFile(minecraftDirectory.absolutePath()+"/.minecraft/bin/minecraft.jar" ,this);
    if (!jarMinecraft->open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this,trUtf8("Erreur"), trUtf8("Une erreur s'est produite, veuillez vérifier que vous possédez les droits d'écritures."));
        SetButtonDisabled(false);
        return;
    }
    jarMinecraft->write(reply->readAll());
    jarMinecraft->close();
    QMessageBox::information(this,trUtf8("Minecraft a bien été installé"), trUtf8("La version "+version.toUtf8()+" de Minecraft a bien été installer sur votre ordinateur."));
    SetButtonDisabled(false);
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
    ui->RefreshButton->setEnabled(true);
    if(download==NULL)
        return false;
    ui->listWidget->clear();
    ui->listWidget->addItems(QString(download->readAll()).split("\n"));
    ui->listWidget->setCurrentRow(0);
    ui->listWidget->setRowHidden(ui->listWidget->count()-1, true);
    ui->InstallButton->setEnabled(true);
    return true;
}

void OldInstall::SetButtonDisabled(bool enable)
{
    ui->InstallButton->setEnabled(!enable);
    ui->RefreshButton->setEnabled(!enable);
}
