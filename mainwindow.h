#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "clientfile.h"
#include "productfile.h"
#include "headerfile.h"
#include "catfile.h"
#include <QPointer>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include "detailfile.h"
#include "arbolb.h"
#include <QMap>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QList<QPointer<QCheckBox> > listaEliminar;
    QList<QPointer<QLineEdit> > listaId;
    QList<QPointer<QCheckBox> > listaEliminarProd;
    QList<QPointer<QLineEdit> > listaIdProd;
    QList<QPointer<QLineEdit> > listaNombreProd;
    QList<QPointer<QLineEdit> > listaIdCategoriaProd;
    QList<QPointer<QLineEdit> > listaPrecio;
    QList<QPointer<QLineEdit> > listaIdCate;
    QList<QPointer<QCheckBox> > listaEliminarCate;
    QPointer<QComboBox> IdCat2;


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_leer_clicked();

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

    void on_lineEdit_buscarCliente_returnPressed();

    void on_comboBox_IdCliente_currentIndexChanged(const QString &arg1);

    void on_comboBox_IdFactura_currentIndexChanged(int index);

    void on_comboBox_metodoDeBusquedad_currentIndexChanged(int index);

    void on_actionClose_triggered();

    void on_actionDelete_Record_triggered();

    void on_pushButton_prodvendido_clicked();

    void on_tabWidget_currentChanged(int index);

private:
    Ui::MainWindow *ui;
    ClientFile cliente;
    ClientFile availCliente;
    ProductFile producto;
    ProductFile availProducto;
    Catfile categoria;
    headerfile header;
    Catfile availCategoria;
    QMap<int,QString> head;
    QMap<int,int> indicedetalle;
    bool leer = false;
    bool Peliminar;
    LinearIndexFile indice;
    LinearIndexFile indiceCat;
    LinearIndexFile indiceProd;
    ArbolB* arbolito=new ArbolB(8);
    detailfile detail;


};

#endif // MAINWINDOW_H
