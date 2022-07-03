#ifndef VENTANAMIXER_H
#define VENTANAMIXER_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class VentanaMixer;
}

class VentanaMixer : public QDialog
{
    Q_OBJECT

public:
    explicit VentanaMixer(QWidget *parent = nullptr,bool *estadoSignalBuffer=nullptr);
    ~VentanaMixer();
    bool almacenarestadosignal;
    bool *estadoSignal = new bool;
    int peakAlmacenado1;
    int peakAlmacenado2;
    int peakAlmacenado3;

public slots:
    void PintarProgressbar(int Canal, float peak);
private slots:
    void on_Fader1_valueChanged(int value);

    void on_Fader2_valueChanged(int value);

    void on_Fader3_valueChanged(int value);

signals:

    void CambioVolumen(int Canal, int Volumen);

private:
    Ui::VentanaMixer *ui;
};

#endif // VENTANAMIXER_H
