#ifndef FAVORITEBUTTON_H
#define FAVORITEBUTTON_H

#include <QPushButton>
#include <webtoon.h>
#include <client.h>

class FavoriteButton: public QPushButton
{
    Q_OBJECT
public:
    FavoriteButton(QWidget *parent, Client* client, Webtoon* _webtoon);

signals:
    void add();
    void del();

public slots:
    void change();

private:
    bool select;
    Webtoon* webtoon;
};

#endif // FAVORITEBUTTON_H
