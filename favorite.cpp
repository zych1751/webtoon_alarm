#include "favorite.h"
#include <QDebug>

Favorite::Favorite()
{
}

Favorite::Favorite(Webtoon webtoon)
{
    this->company = webtoon.getCompany();
    this->day = webtoon.getDay();
    this->name = webtoon.getName();
    this->list_url = webtoon.getListUrl();
    this->recent_url = webtoon.getRecentUrl();
    updateDate = QDate(2000, 1, 1);
    updateTime = QTime(0, 0, 0);
}

Favorite::Favorite(int company, int day, QString name, QString list_url, QString recent_url, QDate date, QTime time)
{
    this->company = company;
    this->day = day;
    this->name = name;
    this->list_url = QUrl(list_url);
    this->recent_url = QUrl(recent_url);
    updateDate = date;
    updateTime = time;
}

bool Favorite::same(Webtoon webtoon)
{
    return (company == webtoon.getCompany() && day == webtoon.getDay() && name == webtoon.getName());
}

QDate Favorite::getUpdateDate()
{
    return updateDate;
}

QTime Favorite::getUpdateTime()
{
    return updateTime;
}

void Favorite::setupdateDate(QDate date)
{
    updateDate = date;
}

void Favorite::setupdateTime(QTime time)
{
    updateTime = time;
}
