#include "clock.h"

Clock::Clock(QObject *parent)
    : QObject{parent}
{
    timerGrafico=new QTimer;
    timerGrafico->setInterval(60);
    timerGrafico->setTimerType(Qt::PreciseTimer);


    connect(timerGrafico,&QTimer::timeout,this,&Clock::CambioGrilla);
}

Clock::~Clock()
{
    delete timerGrafico;

}


void Clock::CambiarMetrica(int BMP,int indexgrilla,int pulsos,int compas)
{

    BMPAlmacenado = BMP;
    indexgrillaAlmacenado = indexgrilla;
    CantidadPulsosAlmacenada=pulsos;
    CompasActual=compas;
    CalculartiempoGrilla();
}


void Clock::CalculartiempoGrilla()
{
    MilisegundosCalculados=((60000/BMPAlmacenado)/60)/indexgrillaAlmacenado;

}

void Clock::Play()
{
  qDebug()<<"Incia Timer Externo";
    timerGrafico->start();
  contadorGrilla=1;
  Grillaencendida=1;
  PulsoEncendido=1;
}

void Clock::Stop()
{
     qDebug()<<"Termina Timer Externo";
    timerGrafico->stop();
}

void Clock::CambioGrilla()
{

    if(contadorGrilla>=MilisegundosCalculados)
    {
        contadorGrilla=0;
        Grillaencendida++;
        if(Grillaencendida>indexgrillaAlmacenado)
        {
            Grillaencendida=1;
            PulsoEncendido++;
            if(PulsoEncendido>CantidadPulsosAlmacenada){PulsoEncendido=1;}
        }
        emit CambiarGrilla(PulsoEncendido,Grillaencendida,CompasActual);

    }
    contadorGrilla++;
}
