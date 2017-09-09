#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include "favoritedeletebutton.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    client = new Client(QUrl("ws://13.113.198.47:8888"),true);

    connect(client, SIGNAL(initialized()), this, SLOT(webtoon_update()));
    connect(client, &Client::changed, this, &MainWindow::favorite_update);
    connect(client, SIGNAL(favoriteUpdated(int)), this, SLOT(alarm(int)));
    initialized = false;
    create_tray_icon();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::create_tray_icon()
{
    tray = new QSystemTrayIcon(this);

    QPixmap oPixmap(16, 16);
    oPixmap.fill(qRgb(255, 0, 255));
    QIcon oIcon(oPixmap);
    tray->setIcon(oIcon);

    connect(tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(on_show_hide(QSystemTrayIcon::ActivationReason)));

    tray->show();
}

void MainWindow::on_show_hide( QSystemTrayIcon::ActivationReason reason )
{
    if( reason )
    {
        if( reason != QSystemTrayIcon::DoubleClick )
        return;
    }

    if( isVisible() )
        hide();
    else
    {
        show();
        raise();
        setFocus();
    }
}

void MainWindow::webtoon_update()
{
    if(!initialized)
    {
        initialized = true;

        QWidget *mon_central = new QWidget();
        QVBoxLayout *mon_layout = new QVBoxLayout();
        ui->mon_scroll->setWidget(mon_central);
        mon_central->setLayout(mon_layout);
        ui->mon_scroll->setWidgetResizable(true);

        QWidget *tue_central = new QWidget();
        QVBoxLayout *tue_layout = new QVBoxLayout();
        ui->tue_scroll->setWidget(tue_central);
        tue_central->setLayout(tue_layout);
        ui->tue_scroll->setWidgetResizable(true);

        QWidget *wed_central = new QWidget();
        QVBoxLayout *wed_layout = new QVBoxLayout();
        ui->wed_scroll->setWidget(wed_central);
        wed_central->setLayout(wed_layout);
        ui->wed_scroll->setWidgetResizable(true);

        QWidget *thu_central = new QWidget();
        QVBoxLayout *thu_layout = new QVBoxLayout();
        ui->thu_scroll->setWidget(thu_central);
        thu_central->setLayout(thu_layout);
        ui->thu_scroll->setWidgetResizable(true);

        QWidget *fri_central = new QWidget();
        QVBoxLayout *fri_layout = new QVBoxLayout();
        ui->fri_scroll->setWidget(fri_central);
        fri_central->setLayout(fri_layout);
        ui->fri_scroll->setWidgetResizable(true);

        QWidget *sat_central = new QWidget();
        QVBoxLayout *sat_layout = new QVBoxLayout();
        ui->sat_scroll->setWidget(sat_central);
        sat_central->setLayout(sat_layout);
        ui->sat_scroll->setWidgetResizable(true);

        QWidget *sun_central = new QWidget();
        QVBoxLayout *sun_layout = new QVBoxLayout();
        ui->sun_scroll->setWidget(sun_central);
        sun_central->setLayout(sun_layout);
        ui->sun_scroll->setWidgetResizable(true);

        std::vector<Webtoon*> webtoon = client->getWebtoon();
        for(Webtoon* it: webtoon)
        {
            LinkButton* new_one = new LinkButton(NULL);
            new_one->setText(it->getName());
            new_one->setUrl(it->getListUrl());
            webtoon_list[it->getCompany()][it->getDay()].push_back(new_one);

            FavoriteButton* new_fone = new FavoriteButton(NULL, client, it);
            if(client->findFavorite(it) != -1)
                new_fone->animateClick();
            new_fone->setMaximumWidth(50);

            LinkButton* new_image = new LinkButton(NULL);
            new_image->setUrl(it->getListUrl());

            QPixmap *pixmap = new QPixmap();
            QUrl imageUrl(it->getImageUrl());
            FileDownloader *m_plmgCtrl = new FileDownloader(imageUrl, pixmap, this);
            connect(m_plmgCtrl, SIGNAL(downloaded(QPixmap*, FileDownloader*)), this, SLOT(loadImage(QPixmap*, FileDownloader*)));

            QEventLoop pause;
            connect(this, SIGNAL(endLoading()), &pause, SLOT(quit()));
            pause.exec();

            QIcon buttonIcon(*pixmap);
            new_image->setIcon(buttonIcon);
            new_image->setIconSize(pixmap->rect().size());
            new_image->setMaximumWidth(150);

            QHBoxLayout* set = new QHBoxLayout();
            set->addWidget(new_image);
            set->addWidget(new_one);
            set->addWidget(new_fone);

            switch(it->getDay())
            {
                case 0:
                    mon_layout->addLayout(set);
                    break;
                case 1:
                    tue_layout->addLayout(set);
                    break;
                case 2:
                    wed_layout->addLayout(set);
                    break;
                case 3:
                    thu_layout->addLayout(set);
                    break;
                case 4:
                    fri_layout->addLayout(set);
                    break;
                case 5:
                    sat_layout->addLayout(set);
                    break;
                case 6:
                    sun_layout->addLayout(set);
                    break;
            }
        }
    }
}

void clearLayout(QLayout *layout)
{
    QLayoutItem *item;
    while((item = layout->takeAt(0)))
    {
        if (item->layout())
        {
            clearLayout(item->layout());
        }
        if (item->widget())
        {
            delete item->widget();
        }
        delete item;
    }
}

void MainWindow::refresh()
{
    client->refresh();
    favorite_update();
}

void MainWindow::favorite_update()
{
    for(auto it: favorite_list)
        clearLayout(it);
    favorite_list.clear();

    QWidget* unread_widget = new QWidget();
    QVBoxLayout* unread_layout = new QVBoxLayout();
    QWidget* read_widget = new QWidget();
    QVBoxLayout* read_layout = new QVBoxLayout();
    unread_layout->setAlignment(Qt::AlignHCenter);
    read_layout->setAlignment(Qt::AlignHCenter);

    ui->unread_scroll->setWidget(unread_widget);
    unread_widget->setLayout(unread_layout);
    ui->unread_scroll->setWidgetResizable(true);

    ui->read_scroll->setWidget(read_widget);
    read_widget->setLayout(read_layout);
    ui->read_scroll->setWidgetResizable(true);

    QPushButton* refresh = new QPushButton(NULL);
    refresh->setText("all_read");
    connect(refresh, SIGNAL(clicked(bool)), this, SLOT(refresh()));
    refresh->setMaximumWidth(150);
    unread_layout->addWidget(refresh);
    unread_layout->setAlignment(refresh, Qt::AlignHCenter);

    for(Favorite* it: client->getFavorite())
    {
        LinkButton *new_one = new LinkButton(NULL);
        new_one->setUrl(it->getRecentUrl());
        new_one->setText(it->getName());
        new_one->setMinimumWidth(250);
        FavoriteDeleteButton *fav_del = new FavoriteDeleteButton(NULL, client, it);
        fav_del->setMaximumWidth(50);

        QHBoxLayout* set = new QHBoxLayout();
        set->addWidget(new_one);
        set->addWidget(fav_del);

        if(it->getRead())
            read_layout->addLayout(set);
        else
            unread_layout->addLayout(set);
    }
    favorite_list.push_back(unread_layout);
    favorite_list.push_back(read_layout);
}

void MainWindow::alarm(int update)
{
    tray->showMessage(QString::number(update) + "개의 웹툰이 추가로 업데이트 되었습니다.", "");
    favorite_update();
}

void MainWindow::loadImage(QPixmap* pixmap, FileDownloader* m_plmgCtr)
{
    pixmap->loadFromData(m_plmgCtr->downloadedData());
    emit endLoading();
}

void MainWindow::closeEvent(QCloseEvent *close_event)
{
    this->hide();
    close_event->ignore();
}
