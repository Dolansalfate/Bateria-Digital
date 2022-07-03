#ifndef ASIGNARCANAL_H
#define ASIGNARCANAL_H

#include <QObject>
#include <math.h>
#include <QObject>
#include <QProgressBar>
#include <QAudioBuffer>
#include <QAudioProbe>
#include <QMediaPlayer>
#include <QMutex>

class AsignarCanal : public QObject
{
    Q_OBJECT
public:
    explicit AsignarCanal(QObject *parent = nullptr, int CanalAsignado=1, bool *estadoSignalbuffer = nullptr);

    ~AsignarCanal();

    bool *SignalBuffer = new bool();
    bool Almacenarboolsignal;

    QMediaPlayer *SlotP = new QMediaPlayer();
    QMediaPlayer *SlotMF = new QMediaPlayer();
    QMediaPlayer *SlotF = new QMediaPlayer();

    QAudioProbe *AnalizarSlotP = new QAudioProbe();
    QAudioProbe *AnalizarSlotMF = new QAudioProbe();
    QAudioProbe *AnalizarSlotF = new QAudioProbe();
    QMutex Mutex;
    int Canalasignado;

    int *arrayDeDatos;
    float *datosfloat;
    double *datosDouble;
    int peakDelArrayActual = 0;

    bool peakHaBajadoDeVolumen;
    double peakPintadoEnProgressBar;
    int peakAnterior =0;
    float numeroLoopDecaimiento =0;

    void CambiodeVolumen(int volumen);
signals:

    void Peak(int Canal,float Valorpeak);

public slots:
    void Reproducir(int index);
    void processBuffer(QAudioBuffer buffer);
    void pintarProgressBar();
    void AsignarUrlArchivos(QString Slot1, QString Slot2, QString Slot3);
};

#endif // ASIGNARCANAL_H
