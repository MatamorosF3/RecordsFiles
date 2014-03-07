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
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_leer_clicked();

    void on_pushButton_cerrar_clicked();

    void on_pushButton_eliminar_clicked();

    void LineEdit_guardar_enter();

    void crear_nuevaFila();

    void on_actionNew_triggered();

    void on_actionOpen_triggered();

private:
    Ui::MainWindow *ui;
    ClientFile cliente;
    ClientFile availCliente;
    bool leer;
    bool Peliminar;

};

#endif // MAINWINDOW_H
