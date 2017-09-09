#ifndef FAVORITEDELETEBUTTON_H
#define FAVORITEDELETEBUTTON_H

#include"client.h"
#include<QPushButton>

class FavoriteDeleteButton: public QPushButton
{
public:
    FavoriteDeleteButton(QWidget *parent, Client* client, Favorite* _favorite);
};

#endif // FAVORITEDELETEBUTTON_H
