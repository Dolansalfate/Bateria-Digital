#include "ventanamixer.h"
#include "ui_ventanamixer.h"


VentanaMixer::VentanaMixer(QWidget *parent,bool *estadoSignalBuffer) :
    QDialog(parent),
    ui(new Ui::VentanaMixer)
{
    float minimo = (1440000000);
    ui->setupUi(this);
    this->estadoSignal=estadoSignalBuffer;
    ui->BarraCanal1L->setRange(-210,0);
    ui->BarraCanal1R->setRange(-210,0);
    ui->BarraCanal2L->setRange(10,100);
    ui->BarraCanal2R->setRange(10,100);
    ui->BarraCanal3L->setRange(880000000,958000000);
    ui->BarraCanal3R->setRange(880000000,958000000);
    ui->Fader1->setRange(0,100);ui->Fader1->setValue(100);
       ui->Fader2->setRange(0,100);ui->Fader2->setValue(100);
          ui->Fader3->setRange(0,100);ui->Fader3->setValue(100);

}

VentanaMixer::~VentanaMixer()
{
    delete ui;
    delete estadoSignal;
}

void VentanaMixer::PintarProgressbar(int Canal, float peak)
{

    float newpeak= (peak);
    if(newpeak<0){newpeak=-newpeak;}
    //qDebug()<<"Entra Boometro Canal : "<<Canal<<"Peak : "<<newpeak;
    almacenarestadosignal=estadoSignal;
   // qDebug()<<"Estado Signal ="<<almacenarestadosignal;
    VentanaMixer::findChild<QProgressBar*>("BarraCanal" + QString::number(Canal)+"L")->setValue(newpeak);
    VentanaMixer::findChild<QProgressBar*>("BarraCanal" + QString::number(Canal)+"R")->setValue(newpeak);
}
void VentanaMixer::on_Fader1_valueChanged(int value)
{
        emit CambioVolumen (1,value);
}


void VentanaMixer::on_Fader2_valueChanged(int value)
{
        emit CambioVolumen (2,value);
}


void VentanaMixer::on_Fader3_valueChanged(int value)
{
        emit CambioVolumen (3,value);
}

