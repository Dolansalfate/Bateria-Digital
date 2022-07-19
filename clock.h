#ifndef CLOCK_H
#define CLOCK_H

#include <QObject>
#include <QTimer>
#include <math.h>
#include <QDebug>
#include <QThread>


class Clock : public QObject
{
    Q_OBJECT
public:
    explicit Clock(QObject *parent = nullptr);
    ~Clock();
    QTimer *timerGrafico;


    int BMPAlmacenado;
    int indexgrillaAlmacenado=1;
    int MilisegundosCalculados;
    int CantidadPulsosAlmacenada=0;
    int CompasActual=1;
    int Grillaencendida = 1;
    int PulsoEncendido=1;
    int contadorGrilla=0;
    int contadorPulsos=0;
    void CambiarMetrica(int BMP, int indexgrilla,int pulsos, int Compas);

    void Play();
    void Stop();
signals:
    void timeoutGraficos();
    void timeoutGrilaa();
    void CambiarGrilla(int PulsoEncendido,int Grillaencendida,int Compas);


public slots:
    //void CambiarMetrica(int BMP, int indexgrilla);
    void CalculartiempoGrilla();
    void CambioGrilla();
};

#endif // CLOCK_H
