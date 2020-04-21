#ifndef TIMER_AUDIO_H
#define TIMER_AUDIO_H
#include <QRunnable>
#include <QMainWindow>
#include <QtMultimedia>
#include <QtMultimediaWidgets>

class Timer_audio : public QRunnable
{
public:
    Timer_audio(QMediaPlayer * m, QSlider * slide, QLCDNumber * num);
    void run();
    bool play = true;
    bool stop = false;
private:
    QMediaPlayer * player;
    QSlider * slider;
    QLCDNumber * number;

};

#endif // TIMER_AUDIO_H
