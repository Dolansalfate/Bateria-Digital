#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QString>


QString readTextFile(QString path)
{
    QFile file(path);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        return in.readAll();
    }

    return "";
}

int main(int argc, char *argv[])
{
    qDebug()<<"Saliendo";qDebug()<<"Saliendo";qDebug()<<"Saliendo";qDebug()<<"Saliendo";qDebug()<<"Saliendo";
    QApplication a(argc, argv);
    QString css = readTextFile(":/Styles/Estilos.css");

   if( css.length() > 0)
    {
        a.setStyleSheet(css);
    }
    MainWindow w;

    w.show();

    return a.exec();
}
