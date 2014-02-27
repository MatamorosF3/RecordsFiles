#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientfile.h"
#include <QPointer>
#include <QLineEdit>
#include <QCheckBox>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QList<QPointer<QCheckBox> > listaEliminar;
    QList<QPointer<QLineEdit> > listaId;
    QList<QPointer<QLineEdit> > listaNombre;
    QList<QPointer<QLineEdit> > listaCorreo;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_leer_clicked();

    void on_pushButton_cerrar_clicked();

    void on_pushButton_eliminar_clicked();

    void on_pushButton_guardar_clicked();

    void LineEdit_guardar_enter();

    void crear_nuevaFila();

    void crear_nuevaFila(QString,QString,QString);


    void on_actionNew_triggered();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    ClientFile cliente;
    ClientFile availCliente;
    bool leer;

};

#endif // MAINWINDOW_H
