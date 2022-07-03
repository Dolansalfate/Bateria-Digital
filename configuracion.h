#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include <QObject>
#include <QSettings>
#include <QDebug>
#include <QList>

class Configuracion : public QObject
{
    Q_OBJECT
public:
    explicit Configuracion(QObject *parent = nullptr);

    QSettings Listas;
    QList<int> ListaRecibida;
    QList<int> ListaDevuelta;
    void GuardarListas(QString NombreLista,QList<int> Lista);
    QList<int> CargarListas(QString NombreLista,QList<int>);
signals:

};

#endif // CONFIGURACION_H
