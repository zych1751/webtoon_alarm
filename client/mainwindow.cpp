#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLayout>
#include <QLabel>

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


        std::vector<Webtoon> webtoon = client->getWebtoon();
        for(auto& it: webtoon)
        {
            LinkButton* new_one = new LinkButton(NULL);
            new_one->setText(it.getName());
            new_one->setUrl(it.getListUrl());
            webtoon_list[it.getCompany()][it.getDay()].push_back(new_one);

            FavoriteButton* new_fone = new FavoriteButton(NULL, client, it);
            if(client->findFavorite(it) != -1)
                new_fone->animateClick();

            /*new_one->setAttribute(Qt::WA_LayoutUsesWidgetRect);
            new_one->setFixedSize(300, 30);
            new_fone->setAttribute(Qt::WA_LayoutUsesWidgetRect);
            new_fone->setFixedSize(300, 30);*/

            switch(it.getDay())
            {
                case 0:
                ui->mon_layout->addWidget(new_one);
                ui->mon_layout->addWidget(new_fone);
                    break;
                case 1:
                ui->tue_layout->addWidget(new_one);
                ui->tue_layout->addWidget(new_fone);
                    break;
                case 2:
                ui->wed_layout->addWidget(new_one);
                ui->wed_layout->addWidget(new_fone);
                    break;
                case 3:
                ui->thu_layout->addWidget(new_one);
                ui->thu_layout->addWidget(new_fone);
                    break;
                case 4:
                ui->fri_layout->addWidget(new_one);
                ui->fri_layout->addWidget(new_fone);
                    break;
                case 5:
                ui->sat_layout->addWidget(new_one);
                ui->sat_layout->addWidget(new_fone);
                    break;
                case 6:
                ui->sun_layout->addWidget(new_one);
                ui->sun_layout->addWidget(new_fone);
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
