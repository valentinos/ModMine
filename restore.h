#ifndef RESTORE_H
#define RESTORE_H

#include "easyzip.h"
#include "easyfile.h"
#include <QtGui/QMessageBox>
#include <QtGui/QInputDialog>
#include <QtGui/QFileSystemModel>
#include <QtGui/QTableView>

namespace Ui {
    class Restore;
}

class Restore : public QWidget
{
    Q_OBJECT

public:
    explicit Restore(QWidget *parent = 0);
    ~Restore();

private slots:
    void on_SaveButton_clicked();
    void on_DeleteButton_clicked();
    void on_RenameButton_clicked();
    void on_RestoreButton_clicked();

private:
    QString SetName();
    bool CheckSelection();

    Ui::Restore *ui;
    QFileSystemModel *model;
    QTableView *RestoreTable;
};

#endif // RESTORE_H
