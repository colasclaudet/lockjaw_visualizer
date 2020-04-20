#include "timer_audio.h"

Timer_audio::Timer_audio(QMediaPlayer * m, QSlider * slide, QLCDNumber * num)
{
    this->player = m;
    this->slider = slide;
    this->number = num;

    this->slider->setMaximum(player->duration()/1000);
    this->slider->repaint();
}

void Timer_audio::run()
{
    qDebug()<<"Thread Start";
    while(true)
    {
        this->slider->setValue(this->player->position()/1000);
        this->number->display(static_cast<int>(player->position()/1000));
    }
}

