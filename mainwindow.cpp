
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //Configuracion
    ListadoColores.append(BeatPlomo);
    ListadoColores.append(BeatBlanco);
    ListadoColores.append(BeatRojo);
    ListadoColores.append(BeatAzul);
    ListadoColores.append(BeatAmarillo);
    ListadoColores.append(BeatVerde);
    ListadoColores.append(BeatNaranjo);
    // Funcion Inicial
    ConfiguracionInicial();
    //Creacion Canales de audio
    Bombo = new AsignarCanal(nullptr,1);
    Caja = new AsignarCanal(nullptr,2);
    HiHatO = new AsignarCanal(nullptr,3);
    ThreadTimerExterno.setObjectName("Timer Thread");
    this->thread()->setObjectName("Thread Mainwindow");
    QString BASEURLAUDIOS = "C:/Users/PC-LAB/Documents/GitHub/BateriaDigital/Bateria-Digital/MP3/";
    connect(&ConfiguracionGrilla,&DatosGrilla::porcentajeTransferenciaCompletado,Ventanacarga,&VentanaCarga::ActualizarPorcentaje);
    connect(this,&MainWindow::ReproducirAudiosConIntensidad,this,&MainWindow::ReproducirBombo);
    connect(this,&MainWindow::ReproducirAudiosConIntensidad,this,&MainWindow::ReproducirCaja);
    connect(this,&MainWindow::ReproducirAudiosConIntensidad,this,&MainWindow::ReproducirHiHat);
    connect(VentanaElegirBeat,&ElegirBeat::CambiarIntensidadGrilla,this,&MainWindow::RecibirValorIntensisdad);
    timerExterno.moveToThread(&ThreadTimerExterno);

    ThreadTimerExterno.start();
    ThreadTimerExterno.setPriority(QThread::HighPriority);


    TiempoTimer=40;
    EstadobotonPlay = false;
    ui->BotonCompas_1->setChecked(true);
    ui->BotonCompas_1->setStyleSheet(BeatNaranjo);
    CompasActual=1;
    ApagarTodolosLed();
    connect(VentanaverMixer,&VentanaMixer::CambioVolumen,this,&MainWindow::AjustarVolumen,Qt::DirectConnection);
    connect(&timerExterno,&Clock::CambiarGrilla,this,&MainWindow::LogicaLeds,Qt::QueuedConnection);
    connect(&timerExterno,&Clock::CambiarGrilla,this,&MainWindow::LogicaledsGrilla,Qt::QueuedConnection);
    connect(&timerExterno,&Clock::CambiarGrilla,this,&MainWindow::ReproducirAudios,Qt::QueuedConnection);

    Bombo->AsignarUrlArchivos(BASEURLAUDIOS+"KickPiano.mp3",BASEURLAUDIOS+"KickMForte.mp3",BASEURLAUDIOS+"KickForte.mp3");
    connect(Bombo,&AsignarCanal::Peak,VentanaverMixer,&VentanaMixer::PintarProgressbar);


    Caja->AsignarUrlArchivos(BASEURLAUDIOS+"SnarePiano.mp3",BASEURLAUDIOS+"SnareMForte.mp3",BASEURLAUDIOS+"SnareForte.mp3");
    connect(Caja,&AsignarCanal::Peak,VentanaverMixer,&VentanaMixer::PintarProgressbar);

    HiHatC = new AsignarCanal(nullptr,3);
    HiHatC->AsignarUrlArchivos(BASEURLAUDIOS+"HihatCPiano.mp3",BASEURLAUDIOS+"HihatCMForte.mp3",BASEURLAUDIOS+"HihatCForte.mp3");
    connect(HiHatC,&AsignarCanal::Peak,VentanaverMixer,&VentanaMixer::PintarProgressbar);


    HiHatC->AsignarUrlArchivos(BASEURLAUDIOS+"HihatOPiano.mp3",BASEURLAUDIOS+"HihatOMForte.mp3",BASEURLAUDIOS+"HihatOForte.mp3");
    connect(HiHatO,&AsignarCanal::Peak,VentanaverMixer,&VentanaMixer::PintarProgressbar);

    qDebug()<<" Mainwindow Incia en Thread :"<<this->thread()->objectName()<<this->thread();
}


MainWindow::~MainWindow()
{

    timerExterno.Stop();

    ThreadTimerExterno.quit();


    delete ui;
    delete Bombo;
    delete Caja;
    delete HiHatC;
    delete HiHatO;
    delete VentanaverMixer;
    //delete ConfiguracionListas;

}

void MainWindow::ConfiguracionInicial()
{

    //Combobox Grilla

    ListadoSubdivisionGrilla  <<""<< "1"<<"1/8"<<"1/8 T"<< "1/16"<<"1/16 5"<<"1/16 T";
    for(int x = 0;x<ListadoSubdivisionGrilla.length();x++)
            {
                ui->comboBoxGrilla->insertItem(x,ListadoSubdivisionGrilla[x]);
            }
    //Establecer Metrica Inicial
   ListaSubdivisionMetrica <<"2"<<"4"<<"8"<<"16";
   ListaInstrumentos<<"Bombo"<<"Caja"<<"HH"<<"Tom1"<<"Tom2"<<"Tom3"<<"Tom4"<<"Crash L"<< "Crash R"<<"Accesorios"<<"Click";
   ListadoColoresIntensidad<<BeatPlomo<<BeatVerde<<BeatAmarillo<<BeatRojo<<BeatBlanco<<BeatNaranjo<<BeatAmarillo;
   for(int x =0;x<ListaSubdivisionMetrica.length();x++)
        {
            ui->comboBoxSubdivision->insertItem(x,ListaSubdivisionMetrica[x]);
        }
    ui->spinBoxBMP->setMinimum(40);
    ui->spinBoxBMP->setMaximum(300);
    ui->spinBoxPulsos->setRange(1,9);
    CargarAjustesMetrica(120,4, 1, 0) ;
    ContadorPulsosParagrilla = 1;
    ContadorPulsos = 1;
    ContadorGrilla = 1;
    ui->comboBoxGrilla->setCurrentIndex(4);
    Actualizargrilla(ui->comboBoxGrilla->currentIndex());
    timerExterno.CambiarMetrica(ui->spinBoxBMP->value(),ui->comboBoxGrilla->currentIndex(),ui->comboBoxSubdivision->currentText().toInt(),CompasActual);
}

// Cargar Valores a Etiquetas y Grilla

void MainWindow::IniciarTimer()
{

}

//Guardar Y Cargar Listas de Pulsos

void MainWindow::GuardarListas()
{
   /* ConfiguracionListas.GuardarListas("Bombo",Lista2DBombo[1]);
    ConfiguracionListas.GuardarListas("Caja",Lista2DCaja[1]);
    ConfiguracionListas.GuardarListas("Hihat",Lista2DHiHat[1]);*/
    Ventanacarga->show();
    ConfiguracionGrilla.GuardarListas();
    Ventanacarga->close();
}

void MainWindow::CargarListas()
{
   /*Lista2DBombo[1]= ConfiguracionListas.CargarListas("Bombo",Lista2DBombo[1]);
    Lista2DCaja[1]= ConfiguracionListas.CargarListas("Caja",Lista2DCaja[1]);
    Lista2DHiHat[1]= ConfiguracionListas.CargarListas("Hihat",Lista2DHiHat[1]);*/
    ConfiguracionGrilla.CargarListas();
}

void MainWindow::CargarListasaGrilla()
{

}

void MainWindow::CargarAjustesMetrica(int BMP,int Pulsos, int Subdivision, int PosicionGrilla)
{
    ui->spinBoxBMP->setValue(BMP);
    ui->spinBoxPulsos->setValue(Pulsos);
    ui->comboBoxSubdivision->setCurrentIndex(Subdivision);
    QString TextoMetrica = QString::number(Pulsos)+"/"+QString::number(Subdivision);
    ui->EtiquetaMetrica->setText(TextoMetrica);
    ui->comboBoxGrilla->setCurrentIndex(PosicionGrilla);
    Actualizargrilla(PosicionGrilla);
}

void MainWindow::PasarConfiguracionAlaGrilla()
{

}

// Logica Esconder y mostra botones de la grilla

void MainWindow::Actualizargrilla(int SubdivisionGrilla)
{
    if(SubdivisionGrilla==0 | ui->comboBoxGrilla->currentIndex()==0){return;}
    // Esconder Todos los botones

    for(int x = 1;x<7;x++)
    {
    // Bombo

        MainWindow::findChild<QPushButton*>("BotonPulso1Bombo" + QString::number(x)+"_1")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Bombo" + QString::number(x)+"_2")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Bombo" + QString::number(x)+"_3")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Bombo" + QString::number(x)+"_4")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Bombo" + QString::number(x)+"_5")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Bombo" + QString::number(x)+"_6")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Bombo" + QString::number(x)+"_7")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Bombo" + QString::number(x)+"_8")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Bombo" + QString::number(x)+"_9")->setVisible(false);

    // Caja

        MainWindow::findChild<QPushButton*>("BotonPulso1Caja" + QString::number(x)+"_1")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Caja" + QString::number(x)+"_2")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Caja" + QString::number(x)+"_3")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Caja" + QString::number(x)+"_4")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Caja" + QString::number(x)+"_5")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Caja" + QString::number(x)+"_6")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Caja" + QString::number(x)+"_7")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Caja" + QString::number(x)+"_8")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Caja" + QString::number(x)+"_9")->setVisible(false);
    // Hihat

        MainWindow::findChild<QPushButton*>("BotonPulso1HH" + QString::number(x)+"_1")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1HH" + QString::number(x)+"_2")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1HH" + QString::number(x)+"_3")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1HH" + QString::number(x)+"_4")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1HH" + QString::number(x)+"_5")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1HH" + QString::number(x)+"_6")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1HH" + QString::number(x)+"_7")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1HH" + QString::number(x)+"_8")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1HH" + QString::number(x)+"_9")->setVisible(false);
   // Tom 1

        MainWindow::findChild<QPushButton*>("BotonPulso1T1_" + QString::number(x)+"_1")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T1_" + QString::number(x)+"_2")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T1_" + QString::number(x)+"_3")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T1_" + QString::number(x)+"_4")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T1_" + QString::number(x)+"_5")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T1_" + QString::number(x)+"_6")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T1_" + QString::number(x)+"_7")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T1_" + QString::number(x)+"_8")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T1_" + QString::number(x)+"_9")->setVisible(false);

        // Tom 2

        MainWindow::findChild<QPushButton*>("BotonPulso1T2_" + QString::number(x)+"_1")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T2_" + QString::number(x)+"_2")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T2_" + QString::number(x)+"_3")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T2_" + QString::number(x)+"_4")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T2_" + QString::number(x)+"_5")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T2_" + QString::number(x)+"_6")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T2_" + QString::number(x)+"_7")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T2_" + QString::number(x)+"_8")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T2_" + QString::number(x)+"_9")->setVisible(false);
    // Tom 3

        MainWindow::findChild<QPushButton*>("BotonPulso1T3_" + QString::number(x)+"_1")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T3_" + QString::number(x)+"_2")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T3_" + QString::number(x)+"_3")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T3_" + QString::number(x)+"_4")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T3_" + QString::number(x)+"_5")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T3_" + QString::number(x)+"_6")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T3_" + QString::number(x)+"_7")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T3_" + QString::number(x)+"_8")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T3_" + QString::number(x)+"_9")->setVisible(false);
    //Tom 4

        MainWindow::findChild<QPushButton*>("BotonPulso1T4_" + QString::number(x)+"_1")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T4_" + QString::number(x)+"_2")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T4_" + QString::number(x)+"_3")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T4_" + QString::number(x)+"_4")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T4_" + QString::number(x)+"_5")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T4_" + QString::number(x)+"_6")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T4_" + QString::number(x)+"_7")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T4_" + QString::number(x)+"_8")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1T4_" + QString::number(x)+"_9")->setVisible(false);
    //Crash L

        MainWindow::findChild<QPushButton*>("BotonPulso1CrashL" + QString::number(x)+"_1")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1CrashL" + QString::number(x)+"_2")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1CrashL" + QString::number(x)+"_3")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1CrashL" + QString::number(x)+"_4")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1CrashL" + QString::number(x)+"_5")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1CrashL" + QString::number(x)+"_6")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1CrashL" + QString::number(x)+"_7")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1CrashL" + QString::number(x)+"_8")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1CrashL" + QString::number(x)+"_9")->setVisible(false);
    // Crash R

        MainWindow::findChild<QPushButton*>("BotonPulso1CrashR" + QString::number(x)+"_1")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1CrashR" + QString::number(x)+"_2")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1CrashR" + QString::number(x)+"_3")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1CrashR" + QString::number(x)+"_4")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1CrashR" + QString::number(x)+"_5")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1CrashR" + QString::number(x)+"_6")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1CrashR" + QString::number(x)+"_7")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1CrashR" + QString::number(x)+"_8")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1CrashR" + QString::number(x)+"_9")->setVisible(false);
    // Ride

        MainWindow::findChild<QPushButton*>("BotonPulso1Ride" + QString::number(x)+"_1")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Ride" + QString::number(x)+"_2")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Ride" + QString::number(x)+"_3")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Ride" + QString::number(x)+"_4")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Ride" + QString::number(x)+"_5")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Ride" + QString::number(x)+"_6")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Ride" + QString::number(x)+"_7")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Ride" + QString::number(x)+"_8")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Ride" + QString::number(x)+"_9")->setVisible(false);
    //Accesorios

        MainWindow::findChild<QPushButton*>("BotonPulso1Acc" + QString::number(x)+"_1")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Acc" + QString::number(x)+"_2")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Acc" + QString::number(x)+"_3")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Acc" + QString::number(x)+"_4")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Acc" + QString::number(x)+"_5")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Acc" + QString::number(x)+"_6")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Acc" + QString::number(x)+"_7")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Acc" + QString::number(x)+"_8")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Acc" + QString::number(x)+"_9")->setVisible(false);
    //Click

        MainWindow::findChild<QPushButton*>("BotonPulso1Click" + QString::number(x)+"_1")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Click" + QString::number(x)+"_2")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Click" + QString::number(x)+"_3")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Click" + QString::number(x)+"_4")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Click" + QString::number(x)+"_5")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Click" + QString::number(x)+"_6")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Click" + QString::number(x)+"_7")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Click" + QString::number(x)+"_8")->setVisible(false);
        MainWindow::findChild<QPushButton*>("BotonPulso1Click" + QString::number(x)+"_9")->setVisible(false);

}

    // Prender Botonoes utilizados segun grilla

   for(int x = 1;x<=ui->spinBoxPulsos->value();x++)

   {
       for(int i = 1;i<=ui->comboBoxGrilla->currentIndex();i++)

       {

           MainWindow::findChild<QPushButton*>("BotonPulso1Bombo" + QString::number(i)+"_"+QString::number(x))->setVisible(true);
           MainWindow::findChild<QPushButton*>("BotonPulso1Caja" + QString::number(i)+"_"+QString::number(x))->setVisible(true);
           MainWindow::findChild<QPushButton*>("BotonPulso1HH" + QString::number(i)+"_"+QString::number(x))->setVisible(true);
           MainWindow::findChild<QPushButton*>("BotonPulso1HH" + QString::number(i)+"_"+QString::number(x))->setVisible(true);
           MainWindow::findChild<QPushButton*>("BotonPulso1T1_" + QString::number(i)+"_"+QString::number(x))->setVisible(true);
           MainWindow::findChild<QPushButton*>("BotonPulso1T2_" + QString::number(i)+"_"+QString::number(x))->setVisible(true);
           MainWindow::findChild<QPushButton*>("BotonPulso1T3_" + QString::number(i)+"_"+QString::number(x))->setVisible(true);
           MainWindow::findChild<QPushButton*>("BotonPulso1T4_" + QString::number(i)+"_"+QString::number(x))->setVisible(true);
           MainWindow::findChild<QPushButton*>("BotonPulso1CrashL" + QString::number(i)+"_"+QString::number(x))->setVisible(true);
           MainWindow::findChild<QPushButton*>("BotonPulso1CrashR" + QString::number(i)+"_"+QString::number(x))->setVisible(true);
           MainWindow::findChild<QPushButton*>("BotonPulso1Ride" + QString::number(i)+"_"+QString::number(x))->setVisible(true);
           MainWindow::findChild<QPushButton*>("BotonPulso1Acc" + QString::number(i)+"_"+QString::number(x))->setVisible(true);
           MainWindow::findChild<QPushButton*>("BotonPulso1Click" + QString::number(i)+"_"+QString::number(x))->setVisible(true);

       }

   }

}

// Logica Leds: Control de la muestra visual del click

int MainWindow::CalcularBMPaMilisec(int BMP)
{

return 0;
}

void MainWindow::ApagarTodolosLed()
{
    int CompasyGrillaAIndex;
    for(int x = 1;x<10;x++)

    {
        for(int i = 1;i<7;i++)

        {

            CompasyGrillaAIndex = (x-1)*6;
            CompasyGrillaAIndex=CompasyGrillaAIndex+(i-1);
            MainWindow::findChild<QPushButton*>("BotonPulso1Bombo" + QString::number(i)+"_"+QString::number(x))->setStyleSheet(ListadoColoresIntensidad[ConfiguracionGrilla.DevolverValordeunaGrilla(1,CompasActual,CompasyGrillaAIndex)]);
            MainWindow::findChild<QPushButton*>("BotonPulso1Caja" + QString::number(i)+"_"+QString::number(x))->setStyleSheet(ListadoColoresIntensidad[ConfiguracionGrilla.DevolverValordeunaGrilla(2,CompasActual,CompasyGrillaAIndex)]);
            MainWindow::findChild<QPushButton*>("BotonPulso1HH" + QString::number(i)+"_"+QString::number(x))->setStyleSheet(ListadoColoresIntensidad[ConfiguracionGrilla.DevolverValordeunaGrilla(3,CompasActual,CompasyGrillaAIndex)]);
            MainWindow::findChild<QPushButton*>("BotonPulso1T1_" + QString::number(i)+"_"+QString::number(x))->setStyleSheet(ListadoColoresIntensidad[ConfiguracionGrilla.DevolverValordeunaGrilla(4,CompasActual,CompasyGrillaAIndex)]);
            MainWindow::findChild<QPushButton*>("BotonPulso1T2_" + QString::number(i)+"_"+QString::number(x))->setStyleSheet(ListadoColoresIntensidad[ConfiguracionGrilla.DevolverValordeunaGrilla(5,CompasActual,CompasyGrillaAIndex)]);
            MainWindow::findChild<QPushButton*>("BotonPulso1T3_" + QString::number(i)+"_"+QString::number(x))->setStyleSheet(ListadoColoresIntensidad[ConfiguracionGrilla.DevolverValordeunaGrilla(6,CompasActual,CompasyGrillaAIndex)]);
            MainWindow::findChild<QPushButton*>("BotonPulso1T4_" + QString::number(i)+"_"+QString::number(x))->setStyleSheet(ListadoColoresIntensidad[ConfiguracionGrilla.DevolverValordeunaGrilla(7,CompasActual,CompasyGrillaAIndex)]);
            MainWindow::findChild<QPushButton*>("BotonPulso1CrashL" + QString::number(i)+"_"+QString::number(x))->setStyleSheet(ListadoColoresIntensidad[ConfiguracionGrilla.DevolverValordeunaGrilla(8,CompasActual,CompasyGrillaAIndex)]);
            MainWindow::findChild<QPushButton*>("BotonPulso1CrashR" + QString::number(i)+"_"+QString::number(x))->setStyleSheet(ListadoColoresIntensidad[ConfiguracionGrilla.DevolverValordeunaGrilla(9,CompasActual,CompasyGrillaAIndex)]);
            MainWindow::findChild<QPushButton*>("BotonPulso1Ride" + QString::number(i)+"_"+QString::number(x))->setStyleSheet(ListadoColoresIntensidad[ConfiguracionGrilla.DevolverValordeunaGrilla(10,CompasActual,CompasyGrillaAIndex)]);
            MainWindow::findChild<QPushButton*>("BotonPulso1Acc" + QString::number(i)+"_"+QString::number(x))->setStyleSheet(ListadoColoresIntensidad[ConfiguracionGrilla.DevolverValordeunaGrilla(11,CompasActual,CompasyGrillaAIndex)]);
            MainWindow::findChild<QPushButton*>("BotonPulso1Click" + QString::number(i)+"_"+QString::number(x))->setStyleSheet(ListadoColoresIntensidad[ConfiguracionGrilla.DevolverValordeunaGrilla(12,CompasActual,CompasyGrillaAIndex)]);

        }

    }
}

void MainWindow::LogicaLeds(int Pulso,int Grilla)
{
       ui->BotonPulso1->setStyleSheet(BeatBlanco);ui->BotonPulso2->setStyleSheet(BeatBlanco);
       ui->BotonPulso3->setStyleSheet(BeatBlanco);ui->BotonPulso4->setStyleSheet(BeatBlanco);
       ui->BotonPulso5->setStyleSheet(BeatBlanco);ui->BotonPulso6->setStyleSheet(BeatBlanco);
       ui->BotonPulso7->setStyleSheet(BeatBlanco);ui->BotonPulso8->setStyleSheet(BeatBlanco);
       ui->BotonPulso9->setStyleSheet(BeatBlanco);
       MainWindow::findChild<QPushButton*>("BotonPulso"+QString::number(Pulso))->setStyleSheet(BeatAzul);
}

void MainWindow::LogicaledsGrilla(int Pulso,int Grilla)
{
    ApagarTodolosLed();
    MainWindow::findChild<QPushButton*>("BotonPulso1Bombo" + QString::number(Grilla)+"_"+QString::number(Pulso))->setStyleSheet(BeatAzul);
    MainWindow::findChild<QPushButton*>("BotonPulso1Caja" + QString::number(Grilla)+"_"+QString::number(Pulso))->setStyleSheet(BeatAzul);
    MainWindow::findChild<QPushButton*>("BotonPulso1HH" + QString::number(Grilla)+"_"+QString::number(Pulso))->setStyleSheet(BeatAzul);
    MainWindow::findChild<QPushButton*>("BotonPulso1T1_" + QString::number(Grilla)+"_"+QString::number(Pulso))->setStyleSheet(BeatAzul);
    MainWindow::findChild<QPushButton*>("BotonPulso1T2_" + QString::number(Grilla)+"_"+QString::number(Pulso))->setStyleSheet(BeatAzul);
    MainWindow::findChild<QPushButton*>("BotonPulso1T3_" + QString::number(Grilla)+"_"+QString::number(Pulso))->setStyleSheet(BeatAzul);
    MainWindow::findChild<QPushButton*>("BotonPulso1T4_" + QString::number(Grilla)+"_"+QString::number(Pulso))->setStyleSheet(BeatAzul);
    MainWindow::findChild<QPushButton*>("BotonPulso1CrashL" + QString::number(Grilla)+"_"+QString::number(Pulso))->setStyleSheet(BeatAzul);
    MainWindow::findChild<QPushButton*>("BotonPulso1CrashR" + QString::number(Grilla)+"_"+QString::number(Pulso))->setStyleSheet(BeatAzul);
    MainWindow::findChild<QPushButton*>("BotonPulso1Ride" + QString::number(Grilla)+"_"+QString::number(Pulso))->setStyleSheet(BeatAzul);
    MainWindow::findChild<QPushButton*>("BotonPulso1Acc" + QString::number(Grilla)+"_"+QString::number(Pulso))->setStyleSheet(BeatAzul);
    MainWindow::findChild<QPushButton*>("BotonPulso1Click" + QString::number(Grilla)+"_"+QString::number(Pulso))->setStyleSheet(BeatAzul);
}


void MainWindow::LogicaTimers()
{

}

void MainWindow::AjustarVolumen(int canal, int volumen)
{
    switch (canal) {
    case 1:
            Bombo->CambiodeVolumen(volumen);
        break;
    case 2:
            Caja->CambiodeVolumen(volumen);
        break;
    case 3:
            HiHatO->CambiodeVolumen(volumen);
            HiHatC->CambiodeVolumen(volumen);
        break;
    }
}
void MainWindow::ReproducirBombo(int PosicionGrilla, int Compas)
{
    int intensidad = ConfiguracionGrilla.DevolverValordeunaGrilla(1,Compas,PosicionGrilla-1);
    switch (intensidad) {
    case 0:
        break;
    case 1:
        Bombo->Reproducir(1);
        break;
    case 2:
        Bombo->Reproducir(2);
        break;
    case 3:

        Bombo->Reproducir(3);
        break;
    }
}

void MainWindow::ReproducirCaja(int PosicionGrilla,int Compas)
{

    int intensidad = ConfiguracionGrilla.DevolverValordeunaGrilla(2,Compas,PosicionGrilla-1);
    switch (intensidad) {
    case 0:
        break;
    case 1:
        Caja->Reproducir(1);
        break;
    case 2:
        Caja->Reproducir(2);
        break;
    case 3:
        Caja->Reproducir(3);
        break;
    }
}
void MainWindow::ReproducirHiHat(int PosicionGrilla, int Compas)
{

    int intensidad = ConfiguracionGrilla.DevolverValordeunaGrilla(3,Compas,PosicionGrilla-1);
    switch (intensidad) {
    case 0:
        break;
    case 1:
        HiHatC->Reproducir(1);
        break;
    case 2:
         HiHatC->Reproducir(2);
        break;
    case 3:
         HiHatC->Reproducir(3);
        break;
    case 4:
        HiHatO->Reproducir(1);
        break;
    case 5:
        HiHatO->Reproducir(2);
        break;
    case 6:
        HiHatO->Reproducir(3);
        break;
    }
}

void MainWindow::TransformarVolumenSlideBar(int volumeSliderValue)
{
    // volumeSliderValue is in the range [0..100]
    qreal linearVolume = QAudio::convertVolume(volumeSliderValue / qreal(100.0),
                                             QAudio::LogarithmicVolumeScale,
                                               QAudio::LinearVolumeScale);
}

void MainWindow::ReproducirAudios(int Pulso, int Grilla, int Compas)
{
    int PulsoaListaIndex= (Pulso-1)*6;
    PulsoaListaIndex = PulsoaListaIndex+Grilla;
    emit ReproducirAudiosConIntensidad(PulsoaListaIndex, Compas);
}

void MainWindow::RecibirValorIntensisdad(int Instrumento,int Compas, int Pulso, int Grilla,int intensidad)
{
    MainWindow::findChild<QPushButton*>("BotonPulso1"+ListaInstrumentos[Instrumento] + QString::number(Grilla)+"_"+QString::number(Pulso))->setStyleSheet(ListadoColoresIntensidad[intensidad]);
    int grillaAIndexLista = ((Pulso-1)*6)+Grilla;
    switch(Instrumento)
    {
    case 0:
        ConfiguracionGrilla.CambiarValorGrilla(1,Compas,grillaAIndexLista-1,intensidad);
        break;
    case 1:
        ConfiguracionGrilla.CambiarValorGrilla(2,Compas,grillaAIndexLista-1,intensidad);
        break;
    case 2:
        ConfiguracionGrilla.CambiarValorGrilla(3,Compas,grillaAIndexLista-1,intensidad);
        break;
    case 3:
        ConfiguracionGrilla.CambiarValorGrilla(4,Compas,grillaAIndexLista-1,intensidad);
        break;
    case 4:
        ConfiguracionGrilla.CambiarValorGrilla(5,Compas,grillaAIndexLista-1,intensidad);
        break;
    case 5:
        ConfiguracionGrilla.CambiarValorGrilla(6,Compas,grillaAIndexLista-1,intensidad);
        break;
    case 6:
        ConfiguracionGrilla.CambiarValorGrilla(7,Compas,grillaAIndexLista-1,intensidad);
        break;

    case 7:
        ConfiguracionGrilla.CambiarValorGrilla(8,Compas,grillaAIndexLista-1,intensidad);
        break;
    case 8:
        ConfiguracionGrilla.CambiarValorGrilla(9,Compas,grillaAIndexLista-1,intensidad);
        break;
    case 9:
        ConfiguracionGrilla.CambiarValorGrilla(10,Compas,grillaAIndexLista-1,intensidad);
        break;
    case 10:
        ConfiguracionGrilla.CambiarValorGrilla(11,Compas,grillaAIndexLista-1,intensidad);
        break;
    case 11:
        ConfiguracionGrilla.CambiarValorGrilla(12,Compas,grillaAIndexLista-1,intensidad);
        break;
    }
}

void MainWindow::DeschekearTodoslosBotonesCompas()
{
    ui->BotonCompas_1->setChecked(false);
    ui->BotonCompas_2->setChecked(false);
    ui->BotonCompas_3->setChecked(false);
    ui->BotonCompas_4->setChecked(false);
    ui->BotonCompas_5->setChecked(false);
    ui->BotonCompas_6->setChecked(false);
    ui->BotonCompas_7->setChecked(false);
    ui->BotonCompas_8->setChecked(false);
    ui->BotonCompas_9->setChecked(false);
    ui->BotonCompas_10->setChecked(false);
    ui->BotonCompas_11->setChecked(false);
    ui->BotonCompas_12->setChecked(false);
    ui->BotonCompas_13->setChecked(false);
    ui->BotonCompas_14->setChecked(false);
    ui->BotonCompas_15->setChecked(false);
    ui->BotonCompas_16->setChecked(false);

    ui->BotonCompas_1->setStyleSheet(BeatPlomo);
    ui->BotonCompas_2->setStyleSheet(BeatPlomo);
    ui->BotonCompas_3->setStyleSheet(BeatPlomo);
    ui->BotonCompas_4->setStyleSheet(BeatPlomo);
    ui->BotonCompas_5->setStyleSheet(BeatPlomo);
    ui->BotonCompas_6->setStyleSheet(BeatPlomo);
    ui->BotonCompas_7->setStyleSheet(BeatPlomo);
    ui->BotonCompas_8->setStyleSheet(BeatPlomo);
    ui->BotonCompas_9->setStyleSheet(BeatPlomo);
    ui->BotonCompas_10->setStyleSheet(BeatPlomo);
    ui->BotonCompas_11->setStyleSheet(BeatPlomo);
    ui->BotonCompas_12->setStyleSheet(BeatPlomo);
    ui->BotonCompas_13->setStyleSheet(BeatPlomo);
    ui->BotonCompas_14->setStyleSheet(BeatPlomo);
    ui->BotonCompas_15->setStyleSheet(BeatPlomo);
    ui->BotonCompas_16->setStyleSheet(BeatPlomo);

}

// SLOTS UI

void MainWindow::on_comboBoxGrilla_currentIndexChanged(int index)
{

    Actualizargrilla(index);
    if(ui->comboBoxGrilla->currentIndex()>0){timerExterno.CambiarMetrica(ui->spinBoxBMP->value(),ui->comboBoxGrilla->currentIndex(),ui->comboBoxSubdivision->currentText().toInt(),CompasActual);}
}

void MainWindow::on_spinBoxPulsos_valueChanged(int arg1)
{
    switch (arg1) {
    case 1:
        ui->GrupoPulso_1->setVisible(true);
        ui->GrupoPulso_2->setVisible(false);
        ui->GrupoPulso_3->setVisible(false);
        ui->GrupoPulso_4->setVisible(false);
        ui->GrupoPulso_5->setVisible(false);
        ui->GrupoPulso_6->setVisible(false);
        ui->GrupoPulso_7->setVisible(false);
        ui->GrupoPulso_8->setVisible(false);
        ui->GrupoPulso_9->setVisible(false);
        break;
    case 2:
        ui->GrupoPulso_1->setVisible(true);
        ui->GrupoPulso_2->setVisible(true);
        ui->GrupoPulso_3->setVisible(false);
        ui->GrupoPulso_4->setVisible(false);
        ui->GrupoPulso_5->setVisible(false);
        ui->GrupoPulso_6->setVisible(false);
        ui->GrupoPulso_7->setVisible(false);
        ui->GrupoPulso_8->setVisible(false);
        ui->GrupoPulso_9->setVisible(false);
        break;
    case 3:
        ui->GrupoPulso_1->setVisible(true);
        ui->GrupoPulso_2->setVisible(true);
        ui->GrupoPulso_3->setVisible(true);
        ui->GrupoPulso_4->setVisible(false);
        ui->GrupoPulso_5->setVisible(false);
        ui->GrupoPulso_6->setVisible(false);
        ui->GrupoPulso_7->setVisible(false);
        ui->GrupoPulso_8->setVisible(false);
        ui->GrupoPulso_9->setVisible(false);
        break;
    case 4:
        ui->GrupoPulso_1->setVisible(true);
        ui->GrupoPulso_2->setVisible(true);
        ui->GrupoPulso_3->setVisible(true);
        ui->GrupoPulso_4->setVisible(true);
        ui->GrupoPulso_5->setVisible(false);
        ui->GrupoPulso_6->setVisible(false);
        ui->GrupoPulso_7->setVisible(false);
        ui->GrupoPulso_8->setVisible(false);
        ui->GrupoPulso_9->setVisible(false);
        break;
    case 5:
        ui->GrupoPulso_1->setVisible(true);
        ui->GrupoPulso_2->setVisible(true);
        ui->GrupoPulso_3->setVisible(true);
        ui->GrupoPulso_4->setVisible(true);
        ui->GrupoPulso_5->setVisible(true);
        ui->GrupoPulso_6->setVisible(false);
        ui->GrupoPulso_7->setVisible(false);
        ui->GrupoPulso_8->setVisible(false);
        ui->GrupoPulso_9->setVisible(false);
        break;
    case 6:
        ui->GrupoPulso_1->setVisible(true);
        ui->GrupoPulso_2->setVisible(true);
        ui->GrupoPulso_3->setVisible(true);
        ui->GrupoPulso_4->setVisible(true);
        ui->GrupoPulso_5->setVisible(true);
        ui->GrupoPulso_6->setVisible(true);
        ui->GrupoPulso_7->setVisible(false);
        ui->GrupoPulso_8->setVisible(false);
        ui->GrupoPulso_9->setVisible(false);
        break;
    case 7:
        ui->GrupoPulso_1->setVisible(true);
        ui->GrupoPulso_2->setVisible(true);
        ui->GrupoPulso_3->setVisible(true);
        ui->GrupoPulso_4->setVisible(true);
        ui->GrupoPulso_5->setVisible(true);
        ui->GrupoPulso_6->setVisible(true);
        ui->GrupoPulso_7->setVisible(true);
        ui->GrupoPulso_8->setVisible(false);
        ui->GrupoPulso_9->setVisible(false);
        break;
    case 8:
        ui->GrupoPulso_1->setVisible(true);
        ui->GrupoPulso_2->setVisible(true);
        ui->GrupoPulso_3->setVisible(true);
        ui->GrupoPulso_4->setVisible(true);
        ui->GrupoPulso_5->setVisible(true);
        ui->GrupoPulso_6->setVisible(true);
        ui->GrupoPulso_7->setVisible(true);
        ui->GrupoPulso_8->setVisible(true);
        ui->GrupoPulso_9->setVisible(false);
        break;
    case 9:
        ui->GrupoPulso_1->setVisible(true);
        ui->GrupoPulso_2->setVisible(true);
        ui->GrupoPulso_3->setVisible(true);
        ui->GrupoPulso_4->setVisible(true);
        ui->GrupoPulso_5->setVisible(true);
        ui->GrupoPulso_6->setVisible(true);
        ui->GrupoPulso_7->setVisible(true);
        ui->GrupoPulso_8->setVisible(true);
        ui->GrupoPulso_9->setVisible(true);
        break;
    }
    Actualizargrilla(ui->comboBoxGrilla->currentIndex());
}
void MainWindow::on_spinBoxBMP_valueChanged(int arg1)
{
    if(ui->comboBoxGrilla->currentIndex()>0){timerExterno.CambiarMetrica(ui->spinBoxBMP->value(),ui->comboBoxGrilla->currentIndex(),ui->comboBoxSubdivision->currentText().toInt(),CompasActual);}
}

void MainWindow::on_Subdivision_currentIndexChanged(int index)
{

}

void MainWindow::on_BotonPlay_toggled(bool checked)
{
    timerExterno.CambiarMetrica(ui->spinBoxBMP->value(),ui->comboBoxGrilla->currentIndex(),ui->comboBoxSubdivision->currentText().toInt(),CompasActual);
    EstadobotonPlay=checked;
    if(EstadobotonPlay)
    {
        timerExterno.Play();
           qDebug()<<"Timer inicia en Thread"<<timerExterno.thread()->objectName()<<timerExterno.thread();
    }
    if(!EstadobotonPlay){timerExterno.Stop();}
    ContadorTimer=1;
    ContadorPulsos=1;
    ContadorGrilla=1;
}

void MainWindow::on_BotonMixer_clicked()
{
    VentanaverMixer->show();
}

void MainWindow::on_BotonCompas_1_clicked()
{
    DeschekearTodoslosBotonesCompas();
    ui->BotonCompas_1->setChecked(true);
    ui->BotonCompas_1->setStyleSheet(BeatNaranjo);
    CompasActual = 1;
    timerExterno.CambiarMetrica(ui->spinBoxBMP->value(),ui->comboBoxGrilla->currentIndex(),ui->comboBoxSubdivision->currentText().toInt(),CompasActual);
    ApagarTodolosLed();
}
void MainWindow::on_BotonCompas_2_clicked()
{
    DeschekearTodoslosBotonesCompas();
    ui->BotonCompas_2->setChecked(true);
    ui->BotonCompas_2->setStyleSheet(BeatNaranjo);
    CompasActual = 2;
    timerExterno.CambiarMetrica(ui->spinBoxBMP->value(),ui->comboBoxGrilla->currentIndex(),ui->comboBoxSubdivision->currentText().toInt(),CompasActual);
    ApagarTodolosLed();
}
void MainWindow::on_BotonCompas_3_clicked()
{
    DeschekearTodoslosBotonesCompas();
    ui->BotonCompas_3->setChecked(true);
    ui->BotonCompas_3->setStyleSheet(BeatNaranjo);
    timerExterno.CambiarMetrica(ui->spinBoxBMP->value(),ui->comboBoxGrilla->currentIndex(),ui->comboBoxSubdivision->currentText().toInt(),CompasActual);
    CompasActual = 3;
}
void MainWindow::on_BotonCompas_4_clicked()
{
    DeschekearTodoslosBotonesCompas();
    ui->BotonCompas_4->setChecked(true);
    ui->BotonCompas_4->setStyleSheet(BeatNaranjo);
    CompasActual = 4;
}
void MainWindow::on_BotonCompas_5_clicked()
{
    DeschekearTodoslosBotonesCompas();
    ui->BotonCompas_5->setChecked(true);
    ui->BotonCompas_5->setStyleSheet(BeatNaranjo);
    CompasActual = 5;
}
void MainWindow::on_BotonCompas_6_clicked()
{
    DeschekearTodoslosBotonesCompas();
    ui->BotonCompas_6->setChecked(true);
    ui->BotonCompas_6->setStyleSheet(BeatNaranjo);
    CompasActual = 6;
}
void MainWindow::on_BotonCompas_7_clicked()
{
    DeschekearTodoslosBotonesCompas();
    ui->BotonCompas_7->setChecked(true);
    ui->BotonCompas_7->setStyleSheet(BeatNaranjo);
    CompasActual = 7;
}
void MainWindow::on_BotonCompas_8_clicked()
{
    DeschekearTodoslosBotonesCompas();
    ui->BotonCompas_8->setChecked(true);
    ui->BotonCompas_8->setStyleSheet(BeatNaranjo);
    CompasActual = 8;
}
void MainWindow::on_BotonCompas_9_clicked()
{
    DeschekearTodoslosBotonesCompas();
    ui->BotonCompas_9->setChecked(true);
    ui->BotonCompas_9->setStyleSheet(BeatNaranjo);
    CompasActual = 9;
}
void MainWindow::on_BotonCompas_10_clicked()
{
    DeschekearTodoslosBotonesCompas();
    ui->BotonCompas_10->setChecked(true);
    ui->BotonCompas_10->setStyleSheet(BeatNaranjo);
    CompasActual = 10;
}
void MainWindow::on_BotonCompas_11_clicked()
{
    DeschekearTodoslosBotonesCompas();
    ui->BotonCompas_11->setChecked(true);
    ui->BotonCompas_11->setStyleSheet(BeatNaranjo);
    CompasActual = 11;
}
void MainWindow::on_BotonCompas_12_clicked()
{
    DeschekearTodoslosBotonesCompas();
    ui->BotonCompas_12->setChecked(true);
    ui->BotonCompas_12->setStyleSheet(BeatNaranjo);
    CompasActual = 12;
}
void MainWindow::on_BotonCompas_13_clicked()
{
    DeschekearTodoslosBotonesCompas();
    ui->BotonCompas_13->setChecked(true);
    ui->BotonCompas_13->setStyleSheet(BeatNaranjo);
    CompasActual = 13;
}
void MainWindow::on_BotonCompas_14_clicked()
{
    DeschekearTodoslosBotonesCompas();
    ui->BotonCompas_14->setChecked(true);
    ui->BotonCompas_14->setStyleSheet(BeatNaranjo);
    CompasActual = 14;
}
void MainWindow::on_BotonCompas_15_clicked()
{
    DeschekearTodoslosBotonesCompas();
    ui->BotonCompas_15->setChecked(true);
    ui->BotonCompas_15->setStyleSheet(BeatNaranjo);
    CompasActual = 15;
}
void MainWindow::on_BotonCompas_16_clicked()
{
    DeschekearTodoslosBotonesCompas();
    ui->BotonCompas_16->setChecked(true);
    ui->BotonCompas_16->setStyleSheet(BeatNaranjo);
    CompasActual = 16;
}

void MainWindow::on_BotonPulso1Bombo1_1_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,1,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo2_1_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,1,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo3_1_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,1,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo4_1_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,1,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo5_1_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,1,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo6_1_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,1,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo1_2_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,2,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo2_2_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,2,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo3_2_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,2,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo4_2_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,2,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo5_2_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,2,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo6_2_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,2,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo1_3_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,3,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo2_3_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,3,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo3_3_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,3,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo4_3_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,3,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo5_3_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,3,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo6_3_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,3,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo1_4_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,4,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo2_4_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,4,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo3_4_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,4,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo4_4_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,4,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo5_4_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,4,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo6_4_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,4,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo1_5_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,5,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo2_5_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,5,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo3_5_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,5,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo4_5_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,5,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo5_5_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,5,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo6_5_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,5,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo1_6_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,6,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo2_6_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,6,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo3_6_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,6,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo4_6_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,6,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo5_6_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,6,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo6_6_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,6,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo1_7_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,7,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo2_7_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,7,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo3_7_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,7,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo4_7_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,7,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo5_7_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,7,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo6_7_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,7,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo1_8_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,8,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo2_8_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,8,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo3_8_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,8,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo4_8_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,8,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo5_8_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,8,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo6_8_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,8,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo1_9_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,9,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo2_9_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,9,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo3_9_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,9,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo4_9_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,9,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo5_9_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,9,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Bombo6_9_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(0,CompasActual,9,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja1_1_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,1,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja2_1_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,1,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja3_1_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,1,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja4_1_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,1,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja5_1_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,1,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja6_1_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,1,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja1_2_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,2,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja2_2_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,2,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja3_2_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,2,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja4_2_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,2,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja5_2_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,2,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja6_2_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,2,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja1_3_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,3,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja2_3_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,3,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja3_3_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,3,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja4_3_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,3,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja5_3_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,3,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja6_3_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,3,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja1_4_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,4,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja2_4_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,4,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja3_4_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,4,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja4_4_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,4,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja5_4_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,4,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja6_4_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,4,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja1_5_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,5,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja2_5_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,5,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja3_5_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,5,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja4_5_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,5,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja5_5_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,5,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja6_5_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,5,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja1_6_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,6,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja2_6_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,6,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja3_6_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,6,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja4_6_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,6,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja5_6_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,6,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja6_6_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,6,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja1_7_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,7,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja2_7_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,7,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja3_7_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,7,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja4_7_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,7,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja5_7_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,7,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja6_7_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,7,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja1_8_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,8,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja2_8_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,8,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja3_8_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,8,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja4_8_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,8,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja5_8_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,8,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja6_8_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,8,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja1_9_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,9,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja2_9_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,9,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja3_9_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,9,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja4_9_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,9,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja5_9_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,9,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Caja6_9_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(1,CompasActual,9,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH1_1_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,1,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH2_1_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,1,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH3_1_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,1,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH4_1_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,1,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH5_1_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,1,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH6_1_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,1,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH1_2_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,2,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH2_2_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,2,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH3_2_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,2,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH4_2_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,2,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH5_2_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,2,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH6_2_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,2,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH1_3_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,3,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH2_3_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,3,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH3_3_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,3,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH4_3_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,3,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH5_3_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,3,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH6_3_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,3,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH1_4_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,4,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH2_4_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,4,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH3_4_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,4,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH4_4_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,4,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH5_4_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,4,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH6_4_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,4,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH1_5_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,5,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH2_5_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,5,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH3_5_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,5,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH4_5_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,5,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH5_5_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,5,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH6_5_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,5,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH1_6_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,6,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH2_6_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,6,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH3_6_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,6,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH4_6_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,6,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH5_6_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,6,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH6_6_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,6,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH1_7_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,7,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH2_7_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,7,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH3_7_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,7,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH4_7_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,7,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH5_7_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,7,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH6_7_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,7,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH1_8_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,8,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH2_8_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,8,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH3_8_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,8,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH4_8_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,8,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH5_8_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,8,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH6_8_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,8,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH1_9_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,9,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH2_9_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,9,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH3_9_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,9,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH4_9_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,9,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH5_9_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,9,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1HH6_9_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(2,CompasActual,9,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_1_1_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,1,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_2_1_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,1,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_3_1_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,1,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_4_1_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,1,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_5_1_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,1,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_6_1_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,1,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_1_2_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,2,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_2_2_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,2,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_3_2_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,2,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_4_2_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,2,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_5_2_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,2,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_6_2_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,2,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_1_3_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,3,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_2_3_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,3,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_3_3_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,3,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_4_3_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,3,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_5_3_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,3,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_6_3_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,3,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_1_4_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,4,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_2_4_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,4,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_3_4_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,4,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_4_4_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,4,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_5_4_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,4,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_6_4_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,4,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_1_5_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,5,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_2_5_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,5,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_3_5_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,5,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_4_5_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,5,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_5_5_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,5,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_6_5_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,5,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_1_6_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,6,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_2_6_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,6,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_3_6_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,6,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_4_6_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,6,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_5_6_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,6,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_6_6_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,6,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_1_7_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,7,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_2_7_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,7,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_3_7_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,7,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_4_7_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,7,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_5_7_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,7,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_6_7_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,7,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_1_8_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,8,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_2_8_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,8,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_3_8_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,8,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_4_8_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,8,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_5_8_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,8,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_6_8_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,8,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_1_9_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,9,1);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_2_9_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,9,2);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_3_9_clicked()
{

    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,9,3);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_4_9_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,9,4);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_5_9_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,9,5);
    VentanaElegirBeat->show();
}
void MainWindow::on_BotonPulso1Tom1_6_9_clicked()
{
    VentanaElegirBeat->RecibirDatosCompasyTiempo(3,CompasActual,9,6);
    VentanaElegirBeat->show();
}
void MainWindow::on_comboBoxSubdivision_currentIndexChanged(int index)
{
    ui->EtiquetaMetrica->setText(QString::number(ui->spinBoxPulsos->value())+"/"+ui->comboBoxSubdivision->currentText());
}

void MainWindow::on_actionCargar_triggered()
{
    CargarListas();

}

void MainWindow::on_actionGuardar_triggered()
{
    GuardarListas();
}
