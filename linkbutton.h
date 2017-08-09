#ifndef LINKBUTTON_H
#define LINKBUTTON_H

#include<QPushButton>
#include<QWidget>
#include<QString>
#include<QUrl>

class LinkButton: public QPushButton
{
public:
    LinkButton(QWidget *parent);
    void setUrl(QString url);
    void setUrl(QUrl url);

private:
    QUrl url;

public slots:
    void slotOpenUrl();
};

#endif // LINKBUTTON_H
