#ifndef DOWNLOADMANAGER_H
#define DOWNLOADMANAGER_H

#include <QtGui/QProgressBar>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtTest/QTest>
#include <iostream>

class DownloadManager : public QProgressBar
{
    Q_OBJECT
public:
    explicit DownloadManager(QWidget *parent = 0);
    QNetworkReply* Download(QString urlString);

signals:
    void SetBlocked(bool block);

private slots:
    void DisplayDownloadProgress(qint64 receivedBytes, qint64 totalBytes);
    void FinishedDownload(QNetworkReply* reply);

private :
    bool isFinish;
    QNetworkAccessManager *manager;
    QNetworkReply *download;
};

#endif // DOWNLOADMNAGER_H
