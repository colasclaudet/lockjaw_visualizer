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
    ui->commandLinkButton_stop->setHidden(true);
    ui->commandLinkButton_play_pause->setHidden(true);
    ui->glarea->setHidden(true);
    ui->lcdNumber->setHidden(true);
    ui->slider_time->setHidden(true);

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
        ui->lcdNumber->display(position);
        player->setPosition(position * 1000);
    }
}
