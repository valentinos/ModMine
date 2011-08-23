#ifndef DOWNLOADWIDGET_H
#define DOWNLOADWIDGET_H

#include "downloadmanager.h"

class DownloadWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DownloadWidget(QWidget *parent = 0);
    ~DownloadWidget();

signals:
    void SetBlocked(bool block);

private slots:
    void IsBlocked(bool block);

protected:
    DownloadManager *downloadManager;

};

#endif // DOWNLOADWIDGET_H
