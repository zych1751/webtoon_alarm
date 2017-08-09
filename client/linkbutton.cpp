#include "linkbutton.h"
#include <QDesktopServices>

LinkButton::LinkButton(QWidget *parent) : QPushButton(parent) {
    this->setFlat(true);
    connect(this, &QPushButton::clicked, this, &LinkButton::slotOpenUrl);
}

void LinkButton::setUrl(QString url) {
    this->url = QUrl(url);
}

void LinkButton::setUrl(QUrl url) {
    this->url = url;
}

void LinkButton::slotOpenUrl() {
    QDesktopServices::openUrl(this->url);
}
