#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include <QPushButton>
#include "linkbutton.h"
#include "favoritebutton.h"
#include <QSystemTrayIcon>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Client *client;
    bool initialized;
    std::vector<LinkButton*> webtoon_list[3][7]; // company, day
    QSystemTrayIcon* tray;

public slots:
    void webtoon_update();
    void favorite_update();
    void alarm(int update);
};

#endif // MAINWINDOW_H
