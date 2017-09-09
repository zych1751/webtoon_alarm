#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client.h"
#include <QPushButton>
#include "linkbutton.h"
#include "favoritebutton.h"
#include <QSystemTrayIcon>
#include "filedownloader.h"
#include <QLayout>
#include <QLabel>
#include <QPixmap>
#include <QCloseEvent>

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
    std::vector<QVBoxLayout*> favorite_list;

    void closeEvent(QCloseEvent* event);
    void create_tray_icon();

public slots:
    void webtoon_update();
    void favorite_update();
    void alarm(int update);
    void refresh();

private slots:
    void loadImage(QPixmap* pixmap, FileDownloader* m_plmgCtr);
    void on_show_hide(QSystemTrayIcon::ActivationReason reason);

signals:
    void endLoading();
};

#endif // MAINWINDOW_H
