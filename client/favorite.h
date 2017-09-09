#ifndef FAVORITE_H
#define FAVORITE_H

#include "webtoon.h"
#include <QDate>
#include <QTime>

class Favorite : public Webtoon
{

public:
    Favorite(Webtoon* webtoon);
    Favorite(int company, int day, QString name, QString list_url, QString recent_url, QString image_url, QDate date, QTime time);
    Favorite(int company, int day, QString name, QString list_url, QString recent_url, QString image_url, QDate date, QTime time, bool read);
    bool same(Webtoon* webtoon);
    bool same(Favorite* fav);

    QDate getUpdateDate();
    QTime getUpdateTime();
    void setupdateDate(QDate date);
    void setupdateTime(QTime time);
    bool getRead();

public slots:
    void setReadTrue();
    void setReadFalse();

private:
    QDate updateDate;
    QTime updateTime;
    bool read;
};

#endif // FAVORITE_H
