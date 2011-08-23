#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QtGui/QProgressBar>

class DownloadManager : public QProgressBar
{
    Q_OBJECT
public:
    explicit DownloadManager(QWidget *parent = 0);

signals:
    void SetBlocked(bool block);

private slots:

private :

};

#endif // DOWNLOADMNAGER_H
