#include "restore.h"
#include "ui_restore.h"

Restore::Restore(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Restore)
{
    ui->setupUi(this);

    model = new QFileSystemModel(this);

    if(!QDir("save").exists())
        QDir(".").mkdir("save");

    RestoreTable = new QTableView(this);

    RestoreTable->setModel(model);
    RestoreTable->setRootIndex(model->setRootPath("save"));
    RestoreTable->setColumnHidden(2, true);
    RestoreTable->setSelectionMode(QAbstractItemView::SingleSelection);
    RestoreTable->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->horizontalLayout->insertWidget(0, RestoreTable);
}

Restore::~Restore()
{
    delete ui;
}

void Restore::on_SaveButton_clicked()
{
    QString name = SetName();
    if(!name.isEmpty())
    {
        EasyZip::Zip(EasyFile::GetMinecraftDirectory()+"/.minecraft", QString("./save/"+name));
    }
}

void Restore::on_DeleteButton_clicked()
{
    if(!QFile("save/"+model->fileName(RestoreTable->rootIndex().child(RestoreTable->selectionModel()->currentIndex().row(), 0))).exists())
    {
        QMessageBox::information(this, trUtf8("Aucune sélection"), trUtf8("Vous n'avez rien sélectionner."));
        return;
    }
    if(QMessageBox::question(this, trUtf8("Supprimer le fichier"), trUtf8("Voulez-vous vraiment supprimer cette sauvegarde ?"), QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes)
    {
        if(!model->remove(RestoreTable->selectionModel()->currentIndex()))
            QMessageBox::critical(this,trUtf8("Erreur"), trUtf8("Une erreur s'est produite, veuillez vérifier que vous possédez les droits d'écritures."));
    }
}

void Restore::on_RenameButton_clicked()
{
    QString oldName = "save/"+model->fileName(RestoreTable->rootIndex().child(RestoreTable->selectionModel()->currentIndex().row(), 0));
    if(!QFile(oldName).exists())
    {
        QMessageBox::information(this, trUtf8("Aucune sélection"), trUtf8("Vous n'avez rien sélectionner."));
        return;
    }
    QString newName = SetName();
    if(!newName.isEmpty())
    {
        newName.insert(0, "save/");
        QFile file(oldName);
        if(!file.rename(oldName, newName))
            QMessageBox::critical(this, trUtf8("Erreur"), trUtf8("Impossible de renommer le fichier."));
    }
}


void Restore::on_RestoreButton_clicked()
{
    bool error = false;
    if(!QFile("save/"+model->fileName(RestoreTable->rootIndex().child(RestoreTable->selectionModel()->currentIndex().row(), 0))).exists())
    {
        QMessageBox::information(this, trUtf8("Aucune sélection"), trUtf8("Vous n'avez rien sélectionner."));
        return;
    }
    if(QMessageBox::question(this, trUtf8("Charger la sauvegarde"), trUtf8("Voulez-vous vraiment remplacer votre dossier .minecraft actuel ?"), QMessageBox::Yes | QMessageBox::No)==QMessageBox::Yes)
    {
       if(!EasyFile::RemoveDirectory(EasyFile::GetMinecraftDirectory()+"/.minecraft"))
       {
           error = true;
       }
       else
       {
           if(!EasyZip::Unzip("save/"+model->fileName(RestoreTable->rootIndex().child(RestoreTable->selectionModel()->currentIndex().row(), 0)),EasyFile::GetMinecraftDirectory()+"/.minecraft/"))
           error = true;
       }
    }
    if(error)
        QMessageBox::critical(this,trUtf8("Erreur"), trUtf8("Une erreur s'est produite, veuillez vérifier que vous possédez les droits d'écritures."));
    else
        QMessageBox::information(this, trUtf8("Chargement réussi"), trUtf8("La sauvegarde a bien été restaurée."));
}


QString Restore::SetName()
{
    QString name;
    QDir save("./save/");
    bool ok = true;
    do{
        name = QInputDialog::getText(this, trUtf8("Nommer la sauvegarde"), trUtf8("Nom de la sauvegarde:"), QLineEdit::Normal, "", &ok);
    }while((save.exists(name)) && (ok == true));
    if(!ok)
        return "";
    return name;
}
