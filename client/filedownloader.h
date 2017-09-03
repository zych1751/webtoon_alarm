#ifndef FILEDOWNLOADER_H
#define FILEDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QPixmap>

class FileDownloader : public QObject
{
    Q_OBJECT
public:
    explicit FileDownloader(QUrl imageUrl, QPixmap* pixmap, QObject* parent = 0);

    virtual ~FileDownloader();

    QByteArray downloadedData() const;

signals:
    void downloaded(QPixmap* pixmap, FileDownloader* m_plmgCtr);

private slots:
    void fileDownloaded(QNetworkReply* pReply);

private:
    QNetworkAccessManager m_WebCtrl;
    QByteArray m_DownloadedData;
    QPixmap* cur;
};

#endif // FILEDOWNLOADER_H
