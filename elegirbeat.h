#ifndef ELEGIRBEAT_H
#define ELEGIRBEAT_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class ElegirBeat;
}

class ElegirBeat : public QDialog
{
    Q_OBJECT


    QStringList ListaInstrumentos;
public:
    explicit ElegirBeat(QWidget *parent = nullptr);
    ~ElegirBeat();
    void RecibirDatosCompasyTiempo(int Instrumento,int Compas, int Pulso, int Grilla);

signals:
    void CambiarIntensidadGrilla(int Instrumento,int Compas, int Pulso, int Grilla,int intensidad);


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ElegirBeat *ui;
};

#endif // ELEGIRBEAT_H
