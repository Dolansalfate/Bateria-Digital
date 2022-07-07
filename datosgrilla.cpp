#include "datosgrilla.h"

DatosGrilla::DatosGrilla(QObject *parent) : QObject(parent)
{

}


void DatosGrilla::GuardarListas()
{
    /*DatosConfiguracion.GuardarListas("Bombo",Lista2DBombo[1]);
    DatosConfiguracion.GuardarListas("Caja",Lista2DCaja[1]);
    DatosConfiguracion.GuardarListas("Hihat",Lista2DHiHat[1]);*/
    porcentajeConfiguracion=0;
    for(int i=0;i<Lista2DBombo.length();i++)
    {
        DatosConfiguracion.GuardarListas("Bombo",Lista2DBombo[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("Caja",Lista2DCaja[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("HiHat",Lista2DHiHat[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("Tom1",Lista2DTom1[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("Tom2",Lista2DTom2[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("Tom3",Lista2DTom3[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("Tom4",Lista2DTom4[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("Crash1",Lista2DCrash1[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("Crash2",Lista2DCrash2[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("Ride",Lista2DRide[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("Acc",Lista2DAcc[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("Click",Lista2DClick[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
    }

}

void DatosGrilla::CargarListas()
{
    Lista2DBombo[1]= DatosConfiguracion.CargarListas("Bombo",Lista2DBombo[1]);
    Lista2DCaja[1]= DatosConfiguracion.CargarListas("Caja",Lista2DCaja[1]);
    Lista2DHiHat[1]= DatosConfiguracion.CargarListas("Hihat",Lista2DHiHat[1]);
}
