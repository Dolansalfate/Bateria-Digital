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
        DatosConfiguracion.GuardarListas("BomboCompas"+QString::number(i),Lista2DBombo[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("CajaCompas",Lista2DCaja[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("HiHatCompas"+QString::number(i),Lista2DHiHat[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("Tom1Compas"+QString::number(i),Lista2DTom1[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("Tom2Compas"+QString::number(i),Lista2DTom2[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("Tom3Compas"+QString::number(i),Lista2DTom3[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("Tom4Compas"+QString::number(i),Lista2DTom4[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("Crash1Compas"+QString::number(i),Lista2DCrash1[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("Crash2Compas"+QString::number(i),Lista2DCrash2[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("RideCompas"+QString::number(i),Lista2DRide[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("AccCompas"+QString::number(i),Lista2DAcc[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        DatosConfiguracion.GuardarListas("ClickCompas"+QString::number(i),Lista2DClick[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
    }

}

void DatosGrilla::CargarListas()
{
    /*Lista2DBombo[1]= DatosConfiguracion.CargarListas("Bombo",Lista2DBombo[1]);
    Lista2DCaja[1]= DatosConfiguracion.CargarListas("Caja",Lista2DCaja[1]);
    Lista2DHiHat[1]= DatosConfiguracion.CargarListas("Hihat",Lista2DHiHat[1]);*/
    porcentajeConfiguracion=0;
    for(int i=0;i<Lista2DBombo.length();i++)
    {
        Lista2DBombo[i] = DatosConfiguracion.CargarListas("BomboCompas"+QString::number(i),Lista2DBombo[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        Lista2DCaja[i] = DatosConfiguracion.CargarListas("CajaCompas"+QString::number(i),Lista2DCaja[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        Lista2DHiHat[i] = DatosConfiguracion.CargarListas("HiHatCompas"+QString::number(i),Lista2DHiHat[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        Lista2DTom1[i] = DatosConfiguracion.CargarListas("Tom1Compas"+QString::number(i),Lista2DTom1[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        Lista2DTom2[i] = DatosConfiguracion.CargarListas("Tom2Compas"+QString::number(i),Lista2DTom2[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        Lista2DTom3[i] = DatosConfiguracion.CargarListas("Tom3Compas"+QString::number(i),Lista2DTom3[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        Lista2DTom4[i] = DatosConfiguracion.CargarListas("Tom4Compas"+QString::number(i),Lista2DTom4[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        Lista2DCrash1[i] = DatosConfiguracion.CargarListas("Crash1Compas"+QString::number(i),Lista2DCrash1[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        Lista2DCrash2[i] = DatosConfiguracion.CargarListas("Crash2Compas"+QString::number(i),Lista2DCrash2[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        Lista2DRide[i] = DatosConfiguracion.CargarListas("RideCompas"+QString::number(i),Lista2DRide[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        Lista2DAcc[i] = DatosConfiguracion.CargarListas("AccCompas"+QString::number(i),Lista2DAcc[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
        Lista2DClick[i] = DatosConfiguracion.CargarListas("ClickCompas"+QString::number(i),Lista2DClick[i]);
        porcentajeConfiguracion++;
        emit porcentajeTransferenciaCompletado(porcentajeConfiguracion);
    }

}


void DatosGrilla::CambiarValorGrilla(int canal,int compas, int posicion,int nuevovalor)
{

    switch (canal) {
    case 1:
           Lista2DBombo[compas][posicion]=nuevovalor;
        break;
    case 2:
           Lista2DCaja[compas][posicion]=nuevovalor;
        break;

    case 3:
           Lista2DHiHat[compas][posicion]=nuevovalor;
        break;

    }


}
