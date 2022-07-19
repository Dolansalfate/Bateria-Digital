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

    case 4:
           Lista2DTom1[compas][posicion]=nuevovalor;
        break;

    case 5:
           Lista2DTom2[compas][posicion]=nuevovalor;
        break;
    case 6:
           Lista2DTom3[compas][posicion]=nuevovalor;
        break;

    case 7:
           Lista2DTom4[compas][posicion]=nuevovalor;
        break;

    case 8:
           Lista2DCrash1[compas][posicion]=nuevovalor;
        break;
    case 9:
           Lista2DCrash2[compas][posicion]=nuevovalor;
        break;
    case 10:
           Lista2DRide[compas][posicion]=nuevovalor;
        break;

    case 11:
           Lista2DAcc[compas][posicion]=nuevovalor;
        break;

    case 12:
           Lista2DClick[compas][posicion]=nuevovalor;
        break;
    }


}

int DatosGrilla::DevolverValordeunaGrilla(int canal,int compas, int posicion)
{
    int valorDevuelto=0;
    switch (canal) {
    case 1:
           valorDevuelto = Lista2DBombo[compas][posicion];
        break;
    case 2:
           valorDevuelto = Lista2DCaja[compas][posicion];
        break;

    case 3:
           valorDevuelto = Lista2DHiHat[compas][posicion];
        break;

    case 4:
           valorDevuelto = Lista2DTom1[compas][posicion];
        break;

    case 5:
           valorDevuelto = Lista2DTom2[compas][posicion];
        break;
    case 6:
           valorDevuelto = Lista2DTom3[compas][posicion];
        break;

    case 7:
           valorDevuelto = Lista2DTom4[compas][posicion];
        break;

    case 8:
           valorDevuelto = Lista2DCrash1[compas][posicion];
        break;
    case 9:
           valorDevuelto = Lista2DCrash2[compas][posicion];
        break;
    case 10:
          valorDevuelto = Lista2DRide[compas][posicion];
        break;

    case 11:
           valorDevuelto = Lista2DAcc[compas][posicion];
        break;

    case 12:
           valorDevuelto = Lista2DClick[compas][posicion];
        break;
    }
    return valorDevuelto;
}
