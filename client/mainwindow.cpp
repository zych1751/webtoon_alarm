#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QIcon>

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

    tray = new QSystemTrayIcon(this);
    tray->setVisible(true);
}

MainWindow::~MainWindow()
{
    delete ui;
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

        std::vector<Webtoon> webtoon = client->getWebtoon();
        for(Webtoon& it: webtoon)
        {
            LinkButton* new_one = new LinkButton(NULL);
            new_one->setText(it.getName());
            new_one->setUrl(it.getListUrl());
            webtoon_list[it.getCompany()][it.getDay()].push_back(new_one);

            FavoriteButton* new_fone = new FavoriteButton(NULL, client, it);
            if(client->findFavorite(it) != -1)
                new_fone->animateClick();

            LinkButton* new_image = new LinkButton(NULL);
            new_image->setUrl(it.getListUrl());

            QPixmap *pixmap = new QPixmap();
            QUrl imageUrl(it.getImageUrl());
            FileDownloader *m_plmgCtrl = new FileDownloader(imageUrl, pixmap, this);
            connect(m_plmgCtrl, SIGNAL(downloaded(QPixmap*, FileDownloader*)), this, SLOT(loadImage(QPixmap*, FileDownloader*)));

            QEventLoop pause;
            connect(this, SIGNAL(endLoading()), &pause, SLOT(quit()));
            pause.exec();

            QIcon buttonIcon(*pixmap);
            new_image->setIcon(buttonIcon);
            new_image->setIconSize(pixmap->rect().size());

            switch(it.getDay())
            {
                case 0:
                mon_layout->addWidget(new_image);
                mon_layout->addWidget(new_one);
                mon_layout->addWidget(new_fone);
                break;
                case 1:
                tue_layout->addWidget(new_image);
                tue_layout->addWidget(new_one);
                tue_layout->addWidget(new_fone);
                break;
                case 2:
                wed_layout->addWidget(new_image);
                wed_layout->addWidget(new_one);
                wed_layout->addWidget(new_fone);
                break;
                case 3:
                thu_layout->addWidget(new_image);
                thu_layout->addWidget(new_one);
                thu_layout->addWidget(new_fone);
                break;
                case 4:
                fri_layout->addWidget(new_image);
                fri_layout->addWidget(new_one);
                fri_layout->addWidget(new_fone);
                break;
                case 5:
                sat_layout->addWidget(new_image);
                sat_layout->addWidget(new_one);
                sat_layout->addWidget(new_fone);
                break;
                case 6:
                sun_layout->addWidget(new_image);
                sun_layout->addWidget(new_one);
                sun_layout->addWidget(new_fone);
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
            delete item->layout();
        }
        if (item->widget())
        {
            delete item->widget();
        }
        delete item;
    }
}

void MainWindow::favorite_update()
{
    clearLayout(ui->fav_layout);
    for(auto& it: client->getFavorite())
    {
        QLabel *new_one = new QLabel(it.getName());
        ui->fav_layout->addWidget(new_one);
    }
}

void MainWindow::alarm(int update)
{
    tray->showMessage(QString::number(update) + "개의 웹툰이 업데이트 되었습니다.", "");
}

void MainWindow::loadImage(QPixmap* pixmap, FileDownloader* m_plmgCtr)
{
    pixmap->loadFromData(m_plmgCtr->downloadedData());
    emit endLoading();
}
