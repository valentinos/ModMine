#include "downloadwidget.h"

DownloadWidget::DownloadWidget(QWidget *parent) :
    QWidget(parent)
{
    downloadManager = new DownloadManager(this);
    QObject::connect(downloadManager, SIGNAL(SetBlocked(bool)), this, SLOT(IsBlocked(bool)));
}

DownloadWidget::~DownloadWidget()
{
    QObject::disconnect(downloadManager, SIGNAL(SetBlocked(bool)), this, SLOT(IsBlocked(bool)));
}

void DownloadWidget::IsBlocked(bool block)
{
    emit SetBlocked(block);
}
