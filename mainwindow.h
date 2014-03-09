#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientfile.h"
#include "productfile.h"
#include "catfile.h"
#include <QPointer>
#include <QLineEdit>
#include <QComboBox>
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
    QList<QPointer<QCheckBox> > listaEliminarProd;
    QList<QPointer<QLineEdit> > listaIdProd;
    QList<QPointer<QLineEdit> > listaNombreProd;
    QList<QPointer<QLineEdit> > listaIdCategoriaProd;
    QList<QPointer<QLineEdit> > listaPrecio;
    QList<QPointer<QLineEdit> > listaIdCate;
    QList<QPointer<QLineEdit> > listaNombreCate;
    QList<QPointer<QCheckBox> > listaEliminarCate;
    QPointer<QComboBox> IdCat2;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_leer_clicked();

    void on_pushButton_cerrar_clicked();

    void on_pushButton_eliminar_clicked();

    void LineEdit_guardar_enter();
    void LineEdit_guardar_enter_Categorias();
    void LineEdit_guardar_enter_Productos();

    void crear_nuevaFila();
    void crear_nuevaFila_Productos();
    void crear_nuevaFila_Categorias();
    void crear_nuevaFila(QString,QString,QString);
    void on_actionNew_triggered();
    void on_actionOpen_triggered();

    void on_actionGenerar_Factura_triggered();

private:
    Ui::MainWindow *ui;
    ClientFile cliente;
    ClientFile availCliente;
    ProductFile producto;
    ProductFile availProducto;
    Catfile categoria;
    Catfile availCategoria;
    bool leer;
    bool Peliminar;

};

#endif // MAINWINDOW_H
