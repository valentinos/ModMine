#include "downloadmanager.h"

DownloadManager::DownloadManager(QWidget *parent) :
    QProgressBar(parent)
{
    manager = new QNetworkAccessManager(this);
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(FinishedDownload(QNetworkReply*)));
}

void DownloadManager::DisplayDownloadProgress(qint64 receivedBytes, qint64 totalBytes)
{
    if(totalBytes>0)
    {
        setValue(QString().setNum(receivedBytes*100/totalBytes).toInt());
    }
}

void DownloadManager::FinishedDownload(QNetworkReply* reply)
{
    isFinish = true;
    emit SetBlocked(false);
    QObject::disconnect(download, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(DisplayDownloadProgress(qint64,qint64)));
}

QNetworkReply* DownloadManager::Download(QString urlString)
{
    emit SetBlocked(true);
    isFinish = false;
    download = manager->get(QNetworkRequest(QUrl(urlString)));
    setValue(0);
    QObject::connect(download, SIGNAL(downloadProgress(qint64,qint64)),this, SLOT(DisplayDownloadProgress(qint64,qint64)));
    while(isFinish!=true)
    {
        QTest::qWait(250);
    }
    if(download->error())
        return NULL;
    return download;
}
