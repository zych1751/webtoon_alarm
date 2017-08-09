#ifndef FAVORITE_H
#define FAVORITE_H

#include "webtoon.h"
#include <QDate>
#include <QTime>

class Favorite : public Webtoon
{
public:
    Favorite();
    Favorite(Webtoon webtoon);
    Favorite(int company, int day, QString name, QString list_url, QString recent_url, QDate date, QTime time);
    bool same(Webtoon webtoon);

    QDate getUpdateDate();
    QTime getUpdateTime();
    void setupdateDate(QDate date);
    void setupdateTime(QTime time);
private:
    QDate updateDate;
    QTime updateTime;
};

#endif // FAVORITE_H
