#include "filedownloader.h"

FileDownloader::FileDownloader(QUrl imageUrl, QPixmap *pixmap, QObject* parent) :
    QObject(parent)
{
    cur = pixmap;
    connect(&m_WebCtrl, SIGNAL (finished(QNetworkReply*)),
    SLOT (fileDownloaded(QNetworkReply*)));

    QNetworkRequest request(imageUrl);
    m_WebCtrl.get(request);
}

void FileDownloader::fileDownloaded(QNetworkReply* pReply)
{
    m_DownloadedData = pReply->readAll();
    //emit a signal
    pReply->deleteLater();
    emit downloaded(cur, this);
}

QByteArray FileDownloader::downloadedData() const
{
    return m_DownloadedData;
}
