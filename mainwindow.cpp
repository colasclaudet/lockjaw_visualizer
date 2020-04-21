#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionStart, SIGNAL(triggered()), this, SLOT(start()));
    connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(load()));
    connect(ui->actionStop, SIGNAL(triggered()), this, SLOT(stop()));
    connect(ui->actionPause, SIGNAL(triggered()), this, SLOT(pause()));
    connect(ui->commandLinkButton_play_pause, SIGNAL(clicked()), this, SLOT(pause()));
    //connect(ui->commandLinkButton_play_pause, SIGNAL(clicked()), this, SLOT(start()));
    connect(ui->commandLinkButton_stop,SIGNAL(clicked()),this,SLOT(stop()));
    connect(ui->commandLinkButton_start,SIGNAL(clicked()),this,SLOT(start()));
    connect(ui->actionDynamic_Backgroud,SIGNAL(triggered()),this,SLOT(dynamic_backgroud()));
    connect(ui->actionFull_Screen,SIGNAL(triggered()),this,SLOT(full_screen()));
    ui->commandLinkButton_stop->setHidden(true);
    ui->commandLinkButton_play_pause->setHidden(true);
    ui->glarea->setHidden(true);
    ui->lcdNumber->setHidden(true);
    ui->slider_time->setHidden(true);

    QPalette pal = palette();

    // set black background
    pal.setColor(QPalette::Background, Qt::black);
    ui->lcdNumber->setAutoFillBackground(true);
    ui->lcdNumber->setPalette(pal);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timer_changed(int arg)
{

}

void MainWindow::start()
{

    if(this->file == "")
    {
        ui->statusbar->showMessage("pas de fichier audio choisi");
    }
    else
    {
        ui->statusbar->showMessage("play " + file);
        if(this->isInit)
            player->stop();
        player = new QMediaPlayer;

        this->isInit = true;
        player->setMedia(QUrl::fromLocalFile(file));
        //player->setVolume(100);
        player->setVolume(ui->dial_volume->value());
        player->play();

        this->time_au = new Timer_audio(this->player,ui->slider_time, ui->lcdNumber);
        //this->time_au->run();
        threadPool = QThreadPool::globalInstance();
        threadPool->start(time_au);
        ui->commandLinkButton_stop->setHidden(false);
        ui->commandLinkButton_play_pause->setHidden(false);
        ui->glarea->setHidden(false);
        ui->lcdNumber->setHidden(false);
        ui->slider_time->setHidden(false);
        ui->slider_time->setMinimum(0);

        ui->commandLinkButton_start->setHidden(true);
        ui->glarea->draw_bounding_box(50.0,50.0,50.0,-50.0,-50.0,-50.0);
        ui->glarea->set_particle(50.0,50.0,50.0,-50.0,-50.0,-50.0);
        ui->actionStart->setVisible(false);
    }

}

void MainWindow::load()
{
    this->file = QFileDialog::getOpenFileName(this,
        tr("Ouvrir fichier"), "",
        tr("mp3 format(*.mp3);;"
        "Tous les fichiers(*)"));

    if (this->file == "")
    {
        ui->statusbar->showMessage("Pas de fichier choisi");
        return;
    }
}

void MainWindow::stop()
{
    if(this->isInit)
    {
        player->stop();
        ui->glarea->draw_bounding_box(0.0,0.0,0.0,0.0,0.0,0.0);
        ui->glarea->set_particle(0.0,0.0,0.0,0.0,0.0,0.0);
        this->isInit = false;
        this->isPause = true;
        ui->commandLinkButton_play_pause->setIcon(QIcon(":/textures/pause.png"));
        ui->commandLinkButton_stop->setHidden(true);
        ui->commandLinkButton_play_pause->setHidden(true);
        ui->glarea->setHidden(true);
        ui->commandLinkButton_start->setHidden(false);
        ui->lcdNumber->setHidden(true);
        ui->slider_time->setHidden(true);
        this->time_au->stop = true;
        this->threadPool->clear();
        ui->actionStart->setVisible(true);
    }

}

void MainWindow::pause()
{
    if(this->isInit)
    {
        if(this->isPause)
        {
            player->play();
            isPause = false;
            ui->actionPause->setText("pause");
            ui->commandLinkButton_play_pause->setText("pause");
            ui->commandLinkButton_play_pause->setIcon(QIcon(":/textures/pause.png"));
            ui->glarea->set_pause(false);
        }
        else
        {
            player->pause();
            isPause = true;
            ui->actionPause->setText("restart");
            ui->commandLinkButton_play_pause->setText("play");
            ui->commandLinkButton_play_pause->setIcon(QIcon(":/textures/play.png"));
            ui->glarea->set_pause(true);
        }
        ui->slider_time->setMaximum(player->duration()/1000);

    }  

}

void MainWindow::dynamic_backgroud()
{
    if(ui->glarea->getDynamic_b())
    {
        ui->glarea->set_dynamic_background(false);
        ui->actionDynamic_Backgroud->setText("Dynamic Background desactived");
    }
    else
    {
        ui->glarea->set_dynamic_background(true);
        ui->actionDynamic_Backgroud->setText("Dynamic Background actived");
    }
}

void MainWindow::full_screen()
{
    if(this->isFullScreen)
    {
        this->isFullScreen = false;
        ui->actionFull_Screen->setText("Full Screen");
    }
    else
    {
        this->isFullScreen = true;
        ui->actionFull_Screen->setText("Minimize Screen");
    }

    if(this->isInit)
    {
        if(!this->isFullScreen)
        {
            ui->commandLinkButton_stop->setHidden(false);
            ui->commandLinkButton_play_pause->setHidden(false);
            ui->dial_volume->setHidden(false);
            ui->progressBar->setHidden(false);
            ui->lcdNumber->setHidden(false);
            ui->slider_time->setHidden(false);
            ui->statusbar->setHidden(false);
        }
        else
        {
            ui->commandLinkButton_stop->setHidden(true);
            ui->commandLinkButton_play_pause->setHidden(true);
            ui->dial_volume->setHidden(true);
            ui->progressBar->setHidden(true);
            ui->lcdNumber->setHidden(true);
            ui->slider_time->setHidden(true);
            ui->statusbar->setHidden(true);
        }
    }
}




void MainWindow::on_dial_volume_sliderMoved(int position)
{
    if(this->isInit)
    {
        player->setVolume(position);

    }
    ui->progressBar->setValue(position);
}

void MainWindow::on_slider_time_sliderMoved(int position)
{
    if(this->isInit)
    {
        QString disp = QString::number(static_cast<int>(position/60)) + ":" + QString::number(static_cast<int>(position%60));
        ui->lcdNumber->display(disp);
        player->setPosition(position * 1000);


    }
}

void MainWindow::on_slider_time_sliderPressed()
{
    time_au->play = false;
    player->pause();
    ui->glarea->set_pause(true);
}

void MainWindow::on_slider_time_sliderReleased()
{
    player->play();
    time_au->play = true;
    ui->glarea->set_pause(false);
}
