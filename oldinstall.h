#ifndef OLDINSTALL_H
#define OLDINSTALL_H

#include "downloadmanager.h"

namespace Ui {
    class OldInstall;
}

class OldInstall : public QWidget
{
    Q_OBJECT

public:
    explicit OldInstall(QWidget *parent = 0);
    ~OldInstall();

private:
    Ui::OldInstall *ui;
    DownloadManager *downloadManager;
};

#endif // OLDINSTALL_H
