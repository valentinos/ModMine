#ifndef OLDINSTALL_H
#define OLDINSTALL_H

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

private:
    Ui::OldInstall *ui;
};

#endif // OLDINSTALL_H
