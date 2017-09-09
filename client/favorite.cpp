#include "favorite.h"
#include <QDebug>

Favorite::Favorite(Webtoon* webtoon)
{
    this->company = webtoon->getCompany();
    this->day = webtoon->getDay();
    this->name = webtoon->getName();
    this->list_url = webtoon->getListUrl();
    this->recent_url = webtoon->getRecentUrl();
    this->image_url = webtoon->getImageUrl();
    updateDate = QDate(2000, 1, 1);
    updateTime = QTime(0, 0, 0);
    read = false;
}

Favorite::Favorite(int company, int day, QString name, QString list_url, QString recent_url, QString image_url, QDate date, QTime time)
{
    this->company = company;
    this->day = day;
    this->name = name;
    this->list_url = QUrl(list_url);
    this->recent_url = QUrl(recent_url);
    this->image_url = QUrl(image_url);
    updateDate = date;
    updateTime = time;
    read = false;
}

Favorite::Favorite(int company, int day, QString name, QString list_url, QString recent_url, QString image_url, QDate date, QTime time, bool read)
{
    this->company = company;
    this->day = day;
    this->name = name;
    this->list_url = QUrl(list_url);
    this->recent_url = QUrl(recent_url);
    this->image_url = QUrl(image_url);
    this->read = read;
    updateDate = date;
    updateTime = time;
    read = false;
}

bool Favorite::same(Webtoon* webtoon)
{
    return (company == webtoon->getCompany() && day == webtoon->getDay() && name == webtoon->getName());
}

bool Favorite::same(Favorite* fav)
{
    return (company == fav->getCompany() && day == fav->getDay() && name == fav->getName());
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

bool Favorite::getRead()
{
    return read;
}

void Favorite::setReadTrue()
{
    read = true;
}
void Favorite::setReadFalse()
{
    read = false;
}
