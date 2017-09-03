#include "client.h"
#include <QtCore/Qdebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QFile>
#include <QTextStream>
#include <QSystemTrayIcon>

QT_USE_NAMESPACE

Client::Client(const QUrl &url, bool debug, QObject *parent):
    QObject(parent),
    m_url(url),
    m_debug(debug)
{
    if(m_debug)
        qDebug() << "Websocket server: " << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &Client::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &Client::closed);

    m_webSocket.open(QUrl(url));

    initialize = false;
    updated = 0;
}

void Client::onConnected()
{
    if(m_debug)
        qDebug() << "Connected!";
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &Client::onTextMessageReceived);
}

QJsonObject ObjectFromString(const QString& in)
{
    QJsonObject obj;

    QJsonDocument doc = QJsonDocument::fromJson(in.toUtf8());
    return doc.object();
}

void Client::onTextMessageReceived(QString message)
{
    QString day[7] = {"mon", "tue", "wed", "thu", "fri", "sat", "sun"};
    QJsonObject data = ObjectFromString(message);

    QJsonObject naver = data["naver"].toObject();

    qDebug() << "Message Received";
    if(!initialize)
    {
        initialize = true;

        for(int i = 0; i < 7; i++)
        {
            auto cur = naver[day[i]].toObject();

            for(auto& it: cur.keys())
            {
                webtoon.push_back(Webtoon(0, i, it, QUrl(cur[it].toObject()["recent_href"].toString())));
                webtoon.back().setImageUrl(QUrl(cur[it].toObject()["img_link"].toString()));
            }
        }

        favoriteRead();
        emit initialized();
    }
    else /* 변경된 내용 새로저장 */
    {
        updated = 0;
        for(int i = 0; i < 7; i++)
        {
            auto cur = naver[day[i]].toObject();

            for(auto& it: cur.keys())
            {
                Webtoon webtoon(0, i, it, QUrl(cur[it].toObject()["recent_href"].toString()));
                int idx = findFavorite(webtoon);
                if(idx == -1)   continue;

                QString time = cur[it].toObject()["recent_time"].toString();
                QDate currentDate = QDate::fromString(time.split(' ')[0], "yyyy-MM-dd");
                QTime currentTime = QTime::fromString(time.split(' ')[1].split('.')[0]);

                if(favorite[idx].getUpdateDate() < currentDate || (favorite[idx].getUpdateDate() == currentDate && favorite[idx].getUpdateTime() < currentTime))
                {
                    updated++;
                    favorite[idx].setupdateDate(currentDate);
                    favorite[idx].setupdateTime(currentTime);
                }
            }
        }

        if(updated != 0)
        {
            emit favoriteUpdated(updated);
            favoriteWrite();
        }
    }
}

int Client::findFavorite(Webtoon& obj)
{
    for(int i = 0; i < (int)favorite.size(); i++)
        if(favorite[i].same(obj))
            return i;
    return -1;
}

void Client::addFavorite(Webtoon obj)
{
    int it = findFavorite(obj);
    if(it != -1)  return;

    favorite.push_back(Favorite(obj));
    emit changed();
    favoriteWrite();
}

void Client::delFavorite(Webtoon obj)
{
    int it = findFavorite(obj);
    if(it == -1)  return;

    favorite.erase(favorite.begin()+it);
    emit changed();
    favoriteWrite();
}

std::vector<Webtoon> Client::getWebtoon()
{
    return webtoon;
}

std::vector<Favorite> Client::getFavorite()
{
    return favorite;
}

void Client::favoriteRead()
{
    QString filename = "favorite.txt";
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream in(&file);
        in.setCodec("UTF-8");
        while(!in.atEnd())
        {
            QString line = in.readLine();
            auto it = line.split('|');
            favorite.push_back(Favorite(it[0].toInt(), it[1].toInt(), it[2], it[3], it[4], it[5], QDate::fromString(it[6]), QTime::fromString(it[7])));
        }
        emit changed();
        file.close();
    }
}

void Client::favoriteWrite()
{
    QString filename = "favorite.txt";
    QFile file(filename);
    if(file.open(QIODevice::WriteOnly))
    {
        file.resize(0);

        for(auto& it: favorite)
        {
            QString cur = QString::number(it.getCompany()) + "|" + QString::number(it.getDay()) + "|" + it.getName() +
                    "|" + it.getListUrl().toEncoded() + "|" + it.getRecentUrl().toEncoded() + "|" + it.getImageUrl().toEncoded() +
                    "|" + it.getUpdateDate().toString() + "|" + it.getUpdateTime().toString() + "\n";
            QByteArray line;
            line.append(cur);
            file.write(line);
        }
    }
}
