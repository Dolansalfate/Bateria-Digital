#ifndef VENTANACARGA_H
#define VENTANACARGA_H

#include <QDialog>

namespace Ui {
class VentanaCarga;
}

class VentanaCarga : public QDialog
{
    Q_OBJECT

public:
    explicit VentanaCarga(QWidget *parent = nullptr);
    ~VentanaCarga();
    int estadoBarra = 0;
public slots:
    void ActualizarPorcentaje(int porcentaje);
private:
    Ui::VentanaCarga *ui;
};

#endif // VENTANACARGA_H
