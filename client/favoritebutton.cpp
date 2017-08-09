#include "favoritebutton.h"
#include <QSignalMapper>

FavoriteButton::FavoriteButton(QWidget *parent, Client *client, Webtoon _webtoon):
    QPushButton(parent)
{
    select = false;
    webtoon = _webtoon;
    this->setText("☆");

    connect(this, &QPushButton::clicked, this, &FavoriteButton::change);

    connect(this, &FavoriteButton::add, [=]() {
        client->addFavorite(webtoon);
    });
    connect(this, &FavoriteButton::del, [=]() {
        client->delFavorite(webtoon);
    });
}

void FavoriteButton::change()
{
    select = !select;

    if(select)
    {
        this->setText("★");
        emit add();
    }
    else
    {
        this->setText("☆");
        emit del();
    }
}
