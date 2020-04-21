#include "timer_audio.h"

Timer_audio::Timer_audio(QMediaPlayer * m, QSlider * slide, QLCDNumber * num)
{
    this->player = m;
    this->slider = slide;
    this->number = num;

}

void Timer_audio::run()
{
    qDebug()<<"Thread Start";
    while(!stop)
    {
        while(!play)
        {

        }
        if(this->player->position()>1000 && this->player->position()<1100)
            this->slider->setMaximum(player->duration()/1000);
        this->slider->setValue(this->player->position()/1000);
        QString disp = QString::number(static_cast<int>((player->position()/1000)/60)) + ":" + QString::number(static_cast<int>((player->position()/1000)%60));

        this->number->display(disp);
    }
}

