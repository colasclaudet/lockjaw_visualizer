#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include <QtMultimediaWidgets>

#include "glarea.h"
#include "timer_audio.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void timer_changed(int arg);
public slots:
    void start();
    void load();
    void stop();
    void pause();
    void dynamic_backgroud();
    void full_screen();


private slots:
    void on_dial_volume_sliderMoved(int position);

    void on_slider_time_sliderMoved(int position);

    void on_slider_time_sliderPressed();

    void on_slider_time_sliderReleased();

private:
    Ui::MainWindow *ui;
    QString file = "";
    QMediaPlayer * player;
    bool isInit = false;
    bool isPause = false;
    bool isFullScreen = false;
    QThreadPool *threadPool;
    Timer_audio * time_au;

};
#endif // MAINWINDOW_H
