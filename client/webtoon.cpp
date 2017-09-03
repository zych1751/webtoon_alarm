#include "webtoon.h"
#include <algorithm>
#include <qDebug>

Webtoon::Webtoon()
{

}


Webtoon::Webtoon(int company, int day, QString name, QUrl url):company(company), day(day), name(name)
{
    if(company == 0)
    {
        QString str = url.toString();
        for(int i = 0; i < str.size(); i++)
            if(str[i] == '&')
                str.remove(i, str.size()-i);

        str.replace("detail", "list");

        QString naver = "http://comic.naver.com";
        recent_url = QUrl(naver+url.toString());
        list_url = QUrl(naver+str);
    }
}

bool Webtoon::same(int _company, int _day, QString _name)
{
    return (company == _company && day == _day && name == _name);
}

int Webtoon::getCompany()
{
    return company;
}

int Webtoon::getDay()
{
    return day;
}

QString Webtoon::getName()
{
    return name;
}

QUrl Webtoon::getListUrl()
{
    return list_url;
}

QUrl Webtoon::getRecentUrl()
{
    return recent_url;
}

QUrl Webtoon::getImageUrl()
{
    return image_url;
}

void Webtoon::setImageUrl(QUrl url)
{
    image_url = url;
}
