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

void Restore::on_RestoreButton_clicked()
{
    bool error = false;
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
