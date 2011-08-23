#ifndef OLDINSTALL_H
#define OLDINSTALL_H

#include<QtGui/QMessageBox>
#include <QTemporaryFile>
#include <QTextStream>
#include "downloadwidget.h"

namespace Ui {
    class OldInstall;
}

class OldInstall : public DownloadWidget
{
    Q_OBJECT

public:
    explicit OldInstall(QWidget *parent = 0);
    ~OldInstall();

private slots:
    void on_RefreshButton_clicked();

private:
    bool UpdateList();
    void SetButtonDisabled(bool enable);

    Ui::OldInstall *ui;
};

#endif // OLDINSTALL_H
