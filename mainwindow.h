#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QThread>
#include <QMainWindow>
#include <QTimer>
#include <QAudio>
#include <QMediaPlayer>
#include <QSoundEffect>
#include <QList>
#include <elegirbeat.h>
#include <ventanamixer.h>
#include <QMediaPlaylist>
#include <QVector>
#include <asignarcanal.h>
#include <clock.h>
//#include <configuracion.h>



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    //Configuracion

    //Configuracion ConfiguracionListas;

    // Timmer

    Clock *timerExterno;

    AsignarCanal *Bombo;
    AsignarCanal *Caja;
    AsignarCanal *HiHatC;
    AsignarCanal *HiHatO;

    QThread *ThreadTimerExterno;

    //QThread nuevoThread;


    //Variables Utilizadas
    int CompasActual;
    QStringList ListadoColoresIntensidad;
    int TiempoTimer;
    QStringList ListaInstrumentos;
    int FramesGrilla;
    int ContadorFramesGrilla;
    int ContadorTimer;
    int MilisecaFramesGrilla;
    int ContadorPulsosParagrilla;
    int ContadorPulsos;
    int ContadorGrilla;
    int BMPaMilisegundos;
    double BMPMilisecFloat;
    bool EstadobotonPlay;

    QStringList ListadoSubdivisionGrilla;
    QStringList ListaSubdivisionMetrica;
    QStringList ListadoColores;

    //FUnciones
    void CargarAjustesMetrica(int BMP,int Pulsos, int Sundivision, int PosicionGrilla);
    void Actualizargrilla(int SubdivisionGrilla);

    int CalcularBMPaMilisec(int BMP);


    // Colores

    QString BeatPlomo = "    border: 1px solid #8f8f91;"
         " background-color: gray; ";
    QString BeatBlanco = "    border: 1px solid #8f8f91;"
         "background-color: white; ";
    QString BeatRojo = "    border: 1px solid #8f8f91;"
         " background-color: red; ";
    QString BeatAzul = "    border: 1px solid #8f8f91;"
         " background-color: blue; ";
    QString BeatAmarillo = "    border: 1px solid #8f8f91;"
         " background-color: yellow; ";
    QString BeatVerde = "    border: 1px solid #8f8f91;"
         " background-color: green; ";
    QString BeatNaranjo = "    border: 1px solid #8f8f91;"
         " background-color: orange; ";




    void ApagarTodolosLed();

    //Arrays Estado Botones

    QList<QList<int>> Lista2DBombo;

    QList<int> EstadoBombo1 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoBombo2 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoBombo3 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoBombo4 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoBombo5 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoBombo6 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoBombo7 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoBombo8 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoBombo9 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoBombo10 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoBombo11 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoBombo12 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoBombo13 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoBombo14 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoBombo15 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoBombo16 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


    QList<QList<int>> Lista2DCaja;

    QList<int> EstadoCaja1 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoCaja2 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoCaja3 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoCaja4 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoCaja5 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoCaja6 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoCaja7 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoCaja8 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoCaja9 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoCaja10 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoCaja11 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoCaja12 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoCaja13 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoCaja14 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoCaja15 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoCaja16 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    QList<QList<int>> Lista2DHiHat;

    QList<int> EstadoHiHat1 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoHiHat2 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoHiHat3 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoHiHat4 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoHiHat5 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoHiHat6 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoHiHat7 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoHiHat8 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoHiHat9 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoHiHat10 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoHiHat11 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoHiHat12 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoHiHat13 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoHiHat14 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoHiHat15 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoHiHat16 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};



    QList<int> EstadoTom1_1 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoTom2_1 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoTom3_1 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoTom4_1 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoCrash1_1 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoCrash2_1 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoRide_1 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoAcc_1 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    QList<int> EstadoClick_1 ={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};



    // Ventanas Adicionales

    ElegirBeat *VentanaElegirBeat = new ElegirBeat(this);
    VentanaMixer *VentanaverMixer = new VentanaMixer(this);


    void CargarListasaGrilla();
signals:
    void CambioPulso(int Pulso, int Grilla, int Compas);
    void ReproducirAudiosConIntensidad(int PosicionGrilla,int Compas);



public slots:
    void LogicaledsGrilla(int Pulso,int Grilla);
    void LogicaTimers();
    void IniciarTimer();
    void TransformarVolumenSlideBar(int volumeSliderValue);
    void ReproducirAudios(int Pulso, int Grilla, int Compas);
    void RecibirValorIntensisdad(int Instrumento, int Compas, int Pulso, int Grilla, int intensidad);
    void ReproducirBombo(int PosicionGrilla, int Compas);
    void ReproducirCaja(int PosicionGrilla, int Compas);
    void ReproducirHiHat(int PosicionGrilla,int Compas);
    void DeschekearTodoslosBotonesCompas();
    void AjustarVolumen(int canal, int volumen);
    void GuardarListas();
    void CargarListas();
private slots:
    void on_comboBoxGrilla_currentIndexChanged(int index);

    void on_spinBoxPulsos_valueChanged(int arg1);
    void LogicaLeds(int Pulso, int Grilla);


    void on_spinBoxBMP_valueChanged(int arg1);

    void on_Subdivision_currentIndexChanged(int index);

    void on_BotonPlay_toggled(bool checked);

    void on_BotonMixer_clicked();


    // Botones Bombo

    void on_BotonPulso1Bombo1_1_clicked();
    void on_BotonPulso1Bombo2_1_clicked();
    void on_BotonPulso1Bombo3_1_clicked();
    void on_BotonPulso1Bombo4_1_clicked();
    void on_BotonPulso1Bombo5_1_clicked();
    void on_BotonPulso1Bombo6_1_clicked();
    void on_BotonPulso1Bombo1_2_clicked();
    void on_BotonPulso1Bombo2_2_clicked();
    void on_BotonPulso1Bombo3_2_clicked();
    void on_BotonPulso1Bombo4_2_clicked();
    void on_BotonPulso1Bombo5_2_clicked();
    void on_BotonPulso1Bombo6_2_clicked();
    void on_BotonPulso1Bombo1_3_clicked();
    void on_BotonPulso1Bombo2_3_clicked();
    void on_BotonPulso1Bombo3_3_clicked();
    void on_BotonPulso1Bombo4_3_clicked();
    void on_BotonPulso1Bombo5_3_clicked();
    void on_BotonPulso1Bombo6_3_clicked();
    void on_BotonPulso1Bombo1_4_clicked();
    void on_BotonPulso1Bombo2_4_clicked();
    void on_BotonPulso1Bombo3_4_clicked();
    void on_BotonPulso1Bombo4_4_clicked();
    void on_BotonPulso1Bombo5_4_clicked();
    void on_BotonPulso1Bombo6_4_clicked();
    void on_BotonPulso1Bombo1_5_clicked();
    void on_BotonPulso1Bombo2_5_clicked();
    void on_BotonPulso1Bombo3_5_clicked();
    void on_BotonPulso1Bombo4_5_clicked();
    void on_BotonPulso1Bombo5_5_clicked();
    void on_BotonPulso1Bombo6_5_clicked();
    void on_BotonPulso1Bombo1_6_clicked();
    void on_BotonPulso1Bombo2_6_clicked();
    void on_BotonPulso1Bombo3_6_clicked();
    void on_BotonPulso1Bombo4_6_clicked();
    void on_BotonPulso1Bombo5_6_clicked();
    void on_BotonPulso1Bombo6_6_clicked();
    void on_BotonPulso1Bombo1_7_clicked();
    void on_BotonPulso1Bombo2_7_clicked();
    void on_BotonPulso1Bombo3_7_clicked();
    void on_BotonPulso1Bombo4_7_clicked();
    void on_BotonPulso1Bombo5_7_clicked();
    void on_BotonPulso1Bombo6_7_clicked();
    void on_BotonPulso1Bombo1_8_clicked();
    void on_BotonPulso1Bombo2_8_clicked();
    void on_BotonPulso1Bombo3_8_clicked();
    void on_BotonPulso1Bombo4_8_clicked();
    void on_BotonPulso1Bombo5_8_clicked();
    void on_BotonPulso1Bombo6_8_clicked();
    void on_BotonPulso1Bombo1_9_clicked();
    void on_BotonPulso1Bombo2_9_clicked();
    void on_BotonPulso1Bombo3_9_clicked();
    void on_BotonPulso1Bombo4_9_clicked();
    void on_BotonPulso1Bombo5_9_clicked();
    void on_BotonPulso1Bombo6_9_clicked();

    // Botones Caja

    void on_BotonPulso1Caja1_1_clicked();
    void on_BotonPulso1Caja2_1_clicked();
    void on_BotonPulso1Caja3_1_clicked();
    void on_BotonPulso1Caja4_1_clicked();
    void on_BotonPulso1Caja5_1_clicked();
    void on_BotonPulso1Caja6_1_clicked();
    void on_BotonPulso1Caja1_2_clicked();
    void on_BotonPulso1Caja2_2_clicked();
    void on_BotonPulso1Caja3_2_clicked();
    void on_BotonPulso1Caja4_2_clicked();
    void on_BotonPulso1Caja5_2_clicked();
    void on_BotonPulso1Caja6_2_clicked();
    void on_BotonPulso1Caja1_3_clicked();
    void on_BotonPulso1Caja2_3_clicked();
    void on_BotonPulso1Caja3_3_clicked();
    void on_BotonPulso1Caja4_3_clicked();
    void on_BotonPulso1Caja5_3_clicked();
    void on_BotonPulso1Caja6_3_clicked();
    void on_BotonPulso1Caja1_4_clicked();
    void on_BotonPulso1Caja2_4_clicked();
    void on_BotonPulso1Caja3_4_clicked();
    void on_BotonPulso1Caja4_4_clicked();
    void on_BotonPulso1Caja5_4_clicked();
    void on_BotonPulso1Caja6_4_clicked();
    void on_BotonPulso1Caja1_5_clicked();
    void on_BotonPulso1Caja2_5_clicked();
    void on_BotonPulso1Caja3_5_clicked();
    void on_BotonPulso1Caja4_5_clicked();
    void on_BotonPulso1Caja5_5_clicked();
    void on_BotonPulso1Caja6_5_clicked();
    void on_BotonPulso1Caja1_6_clicked();
    void on_BotonPulso1Caja2_6_clicked();
    void on_BotonPulso1Caja3_6_clicked();
    void on_BotonPulso1Caja4_6_clicked();
    void on_BotonPulso1Caja5_6_clicked();
    void on_BotonPulso1Caja6_6_clicked();
    void on_BotonPulso1Caja1_7_clicked();
    void on_BotonPulso1Caja2_7_clicked();
    void on_BotonPulso1Caja3_7_clicked();
    void on_BotonPulso1Caja4_7_clicked();
    void on_BotonPulso1Caja5_7_clicked();
    void on_BotonPulso1Caja6_7_clicked();
    void on_BotonPulso1Caja1_8_clicked();
    void on_BotonPulso1Caja2_8_clicked();
    void on_BotonPulso1Caja3_8_clicked();
    void on_BotonPulso1Caja4_8_clicked();
    void on_BotonPulso1Caja5_8_clicked();
    void on_BotonPulso1Caja6_8_clicked();
    void on_BotonPulso1Caja1_9_clicked();
    void on_BotonPulso1Caja2_9_clicked();
    void on_BotonPulso1Caja3_9_clicked();
    void on_BotonPulso1Caja4_9_clicked();
    void on_BotonPulso1Caja5_9_clicked();
    void on_BotonPulso1Caja6_9_clicked();

    // Botones HiHat

    void on_BotonPulso1HH1_1_clicked();
    void on_BotonPulso1HH2_1_clicked();
    void on_BotonPulso1HH3_1_clicked();
    void on_BotonPulso1HH4_1_clicked();
    void on_BotonPulso1HH5_1_clicked();
    void on_BotonPulso1HH6_1_clicked();
    void on_BotonPulso1HH1_2_clicked();
    void on_BotonPulso1HH2_2_clicked();
    void on_BotonPulso1HH3_2_clicked();
    void on_BotonPulso1HH4_2_clicked();
    void on_BotonPulso1HH5_2_clicked();
    void on_BotonPulso1HH6_2_clicked();
    void on_BotonPulso1HH1_3_clicked();
    void on_BotonPulso1HH2_3_clicked();
    void on_BotonPulso1HH3_3_clicked();
    void on_BotonPulso1HH4_3_clicked();
    void on_BotonPulso1HH5_3_clicked();
    void on_BotonPulso1HH6_3_clicked();
    void on_BotonPulso1HH1_4_clicked();
    void on_BotonPulso1HH2_4_clicked();
    void on_BotonPulso1HH3_4_clicked();
    void on_BotonPulso1HH4_4_clicked();
    void on_BotonPulso1HH5_4_clicked();
    void on_BotonPulso1HH6_4_clicked();
    void on_BotonPulso1HH1_5_clicked();
    void on_BotonPulso1HH2_5_clicked();
    void on_BotonPulso1HH3_5_clicked();
    void on_BotonPulso1HH4_5_clicked();
    void on_BotonPulso1HH5_5_clicked();
    void on_BotonPulso1HH6_5_clicked();
    void on_BotonPulso1HH1_6_clicked();
    void on_BotonPulso1HH2_6_clicked();
    void on_BotonPulso1HH3_6_clicked();
    void on_BotonPulso1HH4_6_clicked();
    void on_BotonPulso1HH5_6_clicked();
    void on_BotonPulso1HH6_6_clicked();
    void on_BotonPulso1HH1_7_clicked();
    void on_BotonPulso1HH2_7_clicked();
    void on_BotonPulso1HH3_7_clicked();
    void on_BotonPulso1HH4_7_clicked();
    void on_BotonPulso1HH5_7_clicked();
    void on_BotonPulso1HH6_7_clicked();
    void on_BotonPulso1HH1_8_clicked();
    void on_BotonPulso1HH2_8_clicked();
    void on_BotonPulso1HH3_8_clicked();
    void on_BotonPulso1HH4_8_clicked();
    void on_BotonPulso1HH5_8_clicked();
    void on_BotonPulso1HH6_8_clicked();
    void on_BotonPulso1HH1_9_clicked();
    void on_BotonPulso1HH2_9_clicked();
    void on_BotonPulso1HH3_9_clicked();
    void on_BotonPulso1HH4_9_clicked();
    void on_BotonPulso1HH5_9_clicked();
    void on_BotonPulso1HH6_9_clicked();

    // Botones Tom 1

    void on_BotonPulso1Tom1_1_1_clicked();
    void on_BotonPulso1Tom1_2_1_clicked();
    void on_BotonPulso1Tom1_3_1_clicked();
    void on_BotonPulso1Tom1_4_1_clicked();
    void on_BotonPulso1Tom1_5_1_clicked();
    void on_BotonPulso1Tom1_6_1_clicked();
    void on_BotonPulso1Tom1_1_2_clicked();
    void on_BotonPulso1Tom1_2_2_clicked();
    void on_BotonPulso1Tom1_3_2_clicked();
    void on_BotonPulso1Tom1_4_2_clicked();
    void on_BotonPulso1Tom1_5_2_clicked();
    void on_BotonPulso1Tom1_6_2_clicked();
    void on_BotonPulso1Tom1_1_3_clicked();
    void on_BotonPulso1Tom1_2_3_clicked();
    void on_BotonPulso1Tom1_3_3_clicked();
    void on_BotonPulso1Tom1_4_3_clicked();
    void on_BotonPulso1Tom1_5_3_clicked();
    void on_BotonPulso1Tom1_6_3_clicked();
    void on_BotonPulso1Tom1_1_4_clicked();
    void on_BotonPulso1Tom1_2_4_clicked();
    void on_BotonPulso1Tom1_3_4_clicked();
    void on_BotonPulso1Tom1_4_4_clicked();
    void on_BotonPulso1Tom1_5_4_clicked();
    void on_BotonPulso1Tom1_6_4_clicked();
    void on_BotonPulso1Tom1_1_5_clicked();
    void on_BotonPulso1Tom1_2_5_clicked();
    void on_BotonPulso1Tom1_3_5_clicked();
    void on_BotonPulso1Tom1_4_5_clicked();
    void on_BotonPulso1Tom1_5_5_clicked();
    void on_BotonPulso1Tom1_6_5_clicked();
    void on_BotonPulso1Tom1_1_6_clicked();
    void on_BotonPulso1Tom1_2_6_clicked();
    void on_BotonPulso1Tom1_3_6_clicked();
    void on_BotonPulso1Tom1_4_6_clicked();
    void on_BotonPulso1Tom1_5_6_clicked();
    void on_BotonPulso1Tom1_6_6_clicked();
    void on_BotonPulso1Tom1_1_7_clicked();
    void on_BotonPulso1Tom1_2_7_clicked();
    void on_BotonPulso1Tom1_3_7_clicked();
    void on_BotonPulso1Tom1_4_7_clicked();
    void on_BotonPulso1Tom1_5_7_clicked();
    void on_BotonPulso1Tom1_6_7_clicked();
    void on_BotonPulso1Tom1_1_8_clicked();
    void on_BotonPulso1Tom1_2_8_clicked();
    void on_BotonPulso1Tom1_3_8_clicked();
    void on_BotonPulso1Tom1_4_8_clicked();
    void on_BotonPulso1Tom1_5_8_clicked();
    void on_BotonPulso1Tom1_6_8_clicked();
    void on_BotonPulso1Tom1_1_9_clicked();
    void on_BotonPulso1Tom1_2_9_clicked();
    void on_BotonPulso1Tom1_3_9_clicked();
    void on_BotonPulso1Tom1_4_9_clicked();
    void on_BotonPulso1Tom1_5_9_clicked();
    void on_BotonPulso1Tom1_6_9_clicked();


    void on_comboBoxSubdivision_currentIndexChanged(int index);

    //Rvoid on_BotonCompas_clicked();

    void on_BotonCompas_1_clicked();
    void on_BotonCompas_2_clicked();
    void on_BotonCompas_3_clicked();
    void on_BotonCompas_4_clicked();
    void on_BotonCompas_5_clicked();
    void on_BotonCompas_6_clicked();
    void on_BotonCompas_7_clicked();
    void on_BotonCompas_8_clicked();
    void on_BotonCompas_9_clicked();
    void on_BotonCompas_10_clicked();
    void on_BotonCompas_11_clicked();
    void on_BotonCompas_12_clicked();
    void on_BotonCompas_13_clicked();
    void on_BotonCompas_14_clicked();
    void on_BotonCompas_15_clicked();
    void on_BotonCompas_16_clicked();


    void on_actionCargar_triggered();

    void on_actionGuardar_triggered();

private:
    Ui::MainWindow *ui;
    //Variables

    // Funciones
    void ConfiguracionInicial();
    void PasarConfiguracionAlaGrilla();

};
#endif // MAINWINDOW_H
