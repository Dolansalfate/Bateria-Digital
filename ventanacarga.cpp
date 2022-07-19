#include "ventanacarga.h"
#include "ui_ventanacarga.h"

VentanaCarga::VentanaCarga(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VentanaCarga)
{
    ui->setupUi(this);
    ui->BarraPorcentaje->setRange(0,256);

}

VentanaCarga::~VentanaCarga()
{
    delete ui;
}


void VentanaCarga::ActualizarPorcentaje(int porcentaje)
{
    ui->BarraPorcentaje->setValue(porcentaje);
}
