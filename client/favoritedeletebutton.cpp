#include "favoritedeletebutton.h"

FavoriteDeleteButton::FavoriteDeleteButton(QWidget *parent, Client *client, Favorite* _favorite) :
    QPushButton(parent)
{
    this->setText("X");

    connect(this, &QPushButton::clicked, [=]() {
        client->delFavorite(_favorite);
    });
}
