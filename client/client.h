#ifndef CLIENT_H
#define CLIENT_H

#include<QtCore/QObject>
#include<QtWebSockets/QWebSocket>
#include<QtNetwork/QSslError>
#include<QtCore/QList>
#include<QtCore/QString>
#include<QtCore/QUrl>
#include<vector>
#include<webtoon.h>
#include<favorite.h>

QT_FORWARD_DECLARE_CLASS(QWebSocket)

class Client: public QObject
{
    Q_OBJECT
public:
    explicit Client(const QUrl &url, bool debug=false, QObject *parent=Q_NULLPTR);
    std::vector<Webtoon> getWebtoon();
    std::vector<Favorite> getFavorite();
    int findFavorite(Webtoon& obj); // return idx

signals:
    void initialized();
    void changed();
    void favoriteUpdated(int num);

Q_SIGNALS:
    void closed();

public Q_SLOTS:
    void addFavorite(Webtoon obj);
    void delFavorite(Webtoon obj);

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);

private:
    std::vector<Webtoon> webtoon;
    std::vector<Favorite> favorite;
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
    bool initialize;
    int updated;

    void favoriteRead();
    void favoriteWrite();
};

#endif // CLIENT_H
