#ifndef WEBTOON_H
#define WEBTOON_H

#include<QString>
#include<QUrl>

class Webtoon
{
public:
    Webtoon();
    Webtoon(int company, int day, QString name, QUrl url);
    bool same(int _company, int _day, QString _name);
    int getCompany();
    int getDay();
    QString getName();
    QUrl getListUrl();
    QUrl getRecentUrl();
    QUrl getImageUrl();
    void setImageUrl(QUrl url);

protected:
    int company; // 0 : naver, (maybe 1 : daum, 2 : lezhin)
    int day; // 0 : mon, 1 : tue ....
    QString name;
    QUrl list_url;
    QUrl recent_url;
    QUrl image_url;
};

#endif // WEBTOON_H
