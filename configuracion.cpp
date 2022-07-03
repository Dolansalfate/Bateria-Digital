#include "configuracion.h"

Configuracion::Configuracion(QObject *parent)
    : QObject{parent}
{

}
void Configuracion::GuardarListas(QString NombreLista,QList<int> Lista)
{

    ListaRecibida=Lista;
    Listas.beginWriteArray("ListaRecibida");
    for(int i=0;i<ListaRecibida.size();i++)
    {
        Listas.setArrayIndex(i);
        Listas.setValue(NombreLista,ListaRecibida.at(i));
        qDebug()<<"Agregando : "<<ListaRecibida.at(i);
    }
    Listas.endArray();
    ListaRecibida.clear();
}

QList<int> Configuracion::CargarListas(QString NombreLista,QList<int> Lista)
{
    ListaDevuelta=Lista;
    int size = Listas.beginReadArray("ListaDevuelta");
    for(int i=0;i<size;i++)
    {
        Listas.setArrayIndex(i);
        ListaDevuelta.append(Listas.value(NombreLista).toInt());
        qDebug()<<"Agregando "<<ListaDevuelta[i];
    }
    Listas.endArray();
    return ListaDevuelta;
}
