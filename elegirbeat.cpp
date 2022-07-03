#include "elegirbeat.h"
#include "ui_elegirbeat.h"

ElegirBeat::ElegirBeat(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ElegirBeat)
{
    ui->setupUi(this);
    ListaInstrumentos<<"Bombo"<<"Caja"<<"HiHat"<<"Tom1"<<"Tom2"<<"Tom3"<<"Tom4"<<"Crash L"<< "Crash R"<<"Accesorios"<<"Click";
    ui->comboBoxHiHat->insertItem(0,"Cerrado");
    ui->comboBoxHiHat->insertItem(1,"Abierto");
}

ElegirBeat::~ElegirBeat()
{
    delete ui;
}


void ElegirBeat::RecibirDatosCompasyTiempo(int Instrumento,int Compas, int Pulso, int Grilla)
{
    ui->EtiquetaCompas->setText(QString::number(Compas));
    ui->EtiquetaTiempo->setText(QString::number(Pulso));
    ui->EtiquetaSubdivision->setText(QString::number(Grilla));
    ui->EtiquetaNombreInstrumento->setText(ListaInstrumentos[Instrumento]);
    if(Instrumento == 2)
    {
        ui->comboBoxHiHat->setVisible(true);
    }
    else
    {
        ui->comboBoxHiHat->setVisible(false);
    }
}

void ElegirBeat::on_pushButton_clicked()
{
    this->close();
}


void ElegirBeat::on_pushButton_2_clicked()
{
    int intensidad;
    intensidad = ui->dial->value();
    if(ui->EtiquetaNombreInstrumento->text()=="HiHat"&&ui->comboBoxHiHat->currentText()=="Abierto"){

             intensidad = intensidad+3;
    }

    emit CambiarIntensidadGrilla(ListaInstrumentos.indexOf(ui->EtiquetaNombreInstrumento->text()),ui->EtiquetaCompas->text().toInt(),ui->EtiquetaTiempo->text().toInt(),
                                 ui->EtiquetaSubdivision->text().toInt(),intensidad);
    this->close();

}

