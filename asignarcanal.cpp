#include "asignarcanal.h"

AsignarCanal::AsignarCanal(QObject *parent, int CanalAsignado, bool *estadoSignalBuffer)
    : QObject{parent}
{
    const QString Mp3decoderprueba = "C:/Users/PC-LAB/Documents/GitHub/BateriaDigital/Bateria-Digital/MP3/ENSAYO PITOWILSONmp32.mp3";
    Decoder->setSourceFilename(Mp3decoderprueba);
    QAudioDeviceInfo device = QAudioDeviceInfo::defaultOutputDevice();
    qDebug()<<"Formato salida predefinida = "<<device.preferredFormat();
    Decoder->setAudioFormat(device.preferredFormat());

    this->SignalBuffer = estadoSignalBuffer;
    this->Canalasignado=CanalAsignado;
    AnalizarSlotP->setSource(SlotP);
    AnalizarSlotMF->setSource(SlotMF);
    AnalizarSlotF->setSource(SlotF);
    emit AnalizarSlotF->flush();
    emit AnalizarSlotP->flush();
    emit AnalizarSlotMF->flush();

    connect(AnalizarSlotP, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(QAudioBuffer)));
    connect(AnalizarSlotMF, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(QAudioBuffer)));
    connect(AnalizarSlotF, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(QAudioBuffer)));
    connect(Decoder,SIGNAL(bufferReady(QAudioBuffer)),this,SLOT(ProcesarDecoder(QAudioBUffer)));



}



void AsignarCanal::IniciarDecoder()
{

}

AsignarCanal::~AsignarCanal()
{
    disconnect(AnalizarSlotF, SIGNAL(audioBufferProbed(QAudioBuffer)), this, SLOT(processBuffer(QAudioBuffer)));
    delete SignalBuffer;

    emit AnalizarSlotF->flush();
    emit AnalizarSlotP->flush();
    emit AnalizarSlotMF->flush();


}

void AsignarCanal::Reproducir(int index)
{

    switch (index) {
    case 0:

        break;

    case 1:


            SlotP->stop();
            SlotP->play();
            Decoder->start();
        break;

    case 2:

            SlotMF->stop();
            SlotMF->play();
            Decoder->start();
        break;

    case 3:

            //SlotF->stop();
            //SlotF->play();
        qDebug()<<"Fuente del decoder"<<Decoder->sourceFilename();
            Decoder->start();

        break;

    }
}

void AsignarCanal::processBuffer(QAudioBuffer buffer)
{
    Almacenarboolsignal=true;
    this->SignalBuffer=&Almacenarboolsignal;
Mutex.lock();

    //qDebug()<<"Procesar buffer inicia";
    //qDebug()<< "estado QPRobe 0 "<<AnalizarSlotF->isActive();

    arrayDeDatos = buffer.data<int>();
    datosfloat = buffer.data<float>();
    datosDouble = buffer.data<double>();
    const unsigned char *ptr = reinterpret_cast<const unsigned char *>(buffer.data<char>());
    peakDelArrayActual = 0;
    int n = buffer.frameCount();
    //double x[n];
    //double y[n];
    int almacenarpeaksdividir;

    /*for (int i=0; i<n; i++) {
        double hannWindow = 0.5 * (1 - sin((2 * M_PI * i) / (n - 1)));
        x[i] = hannWindow*datosDouble[i];

    }
    //qDebug()<<" X "<<x[int(n/2)];
*/
   m_maxAmplitude = 32767;
    quint32 value = 0;
    quint32 maxValue = 0;
    for(int i=0;i<buffer.frameCount()-1;i++)

    {
        //peakDelArrayActual = qMax(int(arrayDeDatos[i]),peakDelArrayActual);
        //if(datosDouble[i]<0){datosDouble[i]=-datosDouble[i];}

        //qDebug()<<datosDouble[i];
        quint32 value = 0;

        value = qAbs(qFromLittleEndian<qint16>(ptr));
        almacenarpeaksdividir =almacenarpeaksdividir+std::abs(arrayDeDatos[i]);
        peakDelArrayActual = qMax(arrayDeDatos[i],peakDelArrayActual);
        maxValue = qMax(value, maxValue);

    }
    maxValue = qMin(maxValue, m_maxAmplitude);
    m_level = qreal(maxValue) / m_maxAmplitude;
    m_level=20*log(m_level);
    //qDebug()<<"Media Peak = "<<-20*log10(almacenarpeaksdividir/n);
    peakHaBajadoDeVolumen = peakPintadoEnProgressBar >= float(peakDelArrayActual);
    peakAnterior = peakDelArrayActual;
    qDebug()<<"NuevoIntento meter = "<<m_level;
    m_level=m_level+200;
    if(m_level<0){m_level=0;}
    emit Peak(Canalasignado,m_level);
    //pintarProgressBar();


    emit AnalizarSlotF->flush();
    emit AnalizarSlotP->flush();
    emit AnalizarSlotMF->flush();

Mutex.unlock();


}


void AsignarCanal::pintarProgressBar()
{

    if(peakHaBajadoDeVolumen){
        numeroLoopDecaimiento++;
        peakPintadoEnProgressBar = (1.00 - (0.001*numeroLoopDecaimiento))  * peakPintadoEnProgressBar;
    }
    else
    {
        numeroLoopDecaimiento = 0.00;
        peakPintadoEnProgressBar = double(peakAnterior);
        peakPintadoEnProgressBar = (20*log10(peakPintadoEnProgressBar)-100);
    }

    //emit Peak(Canalasignado,peakPintadoEnProgressBar);
    Almacenarboolsignal=false;
    this->SignalBuffer=&Almacenarboolsignal;

    //qDebug()<<"Señal Emitida Peak = "<<peakPintadoEnProgressBar;

}

void AsignarCanal::AsignarUrlArchivos(QString Slot1, QString Slot2, QString Slot3)
{

    SlotP->setMedia(QUrl::fromLocalFile(Slot1));
    SlotMF->setMedia(QUrl::fromLocalFile(Slot2));
    SlotF->setMedia(QUrl::fromLocalFile(Slot3));



    qDebug()<<"Formato = "<<Decoder->audioFormat();

}

void AsignarCanal::CambiodeVolumen(int volumen)
{
    qreal linearVolume = QAudio::convertVolume(volumen / qreal(100.0),
                                               QAudio::LogarithmicVolumeScale,
                                               QAudio::LinearVolumeScale);

    SlotF->setVolume(qRound(linearVolume * 100));
    SlotMF->setVolume(qRound(linearVolume * 100));
    SlotP->setVolume(qRound(linearVolume * 100));
}

void AsignarCanal::ProcesarDecoder(QAudioBuffer bufferDecoder)
{
 qDebug()<<"Analizando Decoder";
}
