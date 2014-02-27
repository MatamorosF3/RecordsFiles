#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "clientfile.h"
#include <QMessageBox>
#include <QFileDialog>
#include <list>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabWidget->setTabText(0,"Clientes");
    ui->tabWidget->setTabText(1,"Categorias");
    ui->tabWidget->setTabText(2,"Producto");
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_leer_clicked()
{
    cliente.path = "Clientes.txt";

    if(ui->tabWidget->currentIndex() == 0){ // inicio if clientes
        const int si  =cliente.recordsSize();
        int cont = 0;
        char buffer [84];

        while(cont < si ){

            cliente.readrecord(buffer,cont);
            buffer[83] = '\0';
            cont += 84;
            QString sId;
            QString sNombre;
            QString sCorreo;
            for(int i = 0; i < 4; i++)
                sId += buffer[i];

            for(int i = 4; i < 44;i++){
                if(i != 43){
                    if(buffer[i] == ' ' && buffer[i+1] == ' ')
                        break;
                    else
                        sNombre += buffer[i];
                }
            }

            for(int i = 43; i < 84; i++){
                if(i != 83){
                    if(buffer[i] == ' ' && buffer[i+1] == ' ')
                        break;
                    else
                        sCorreo += buffer[i];
                }
            }

            const int ultima_fila =  ui->tableWidget->rowCount();
            if(sId[0] == '*')
                continue;

            ui->tableWidget->insertRow(ultima_fila);
            QPointer<QCheckBox> eliminar = new QCheckBox(this);
            QPointer<QLineEdit>  id = new QLineEdit(this);
            QPointer<QLineEdit>  nombre = new QLineEdit(this);
            QPointer<QLineEdit>  correo = new QLineEdit(this);

            connect(correo,SIGNAL(returnPressed()),this,SLOT(LineEdit_guardar_enter()));
            QRegExp validarNumeros("^[0-9]*$");

            id->setText(sId);
            id->setMaxLength(4);
            id->setValidator(new QRegExpValidator(validarNumeros, this));
            id->setEnabled(false);

            nombre->setMaxLength(39);
            nombre->setText(sNombre);

            correo->setMaxLength(39);
            correo->setText(sCorreo);

            ui->tableWidget->setCellWidget(ultima_fila,0,eliminar);
            ui->tableWidget->setCellWidget(ultima_fila,1,id);
            ui->tableWidget->setCellWidget(ultima_fila,2,nombre);
            ui->tableWidget->setCellWidget(ultima_fila,3,correo);

            listaEliminar.append(eliminar);
            listaId.append(id);
            listaNombre.append(nombre);
            listaCorreo.append(correo);
        } //fin while

    } // fin if clientes
    leer = true;
    crear_nuevaFila();
}

void MainWindow::on_pushButton_cerrar_clicked()
{
    cliente.updateAvail();
    this->close();
}

void MainWindow::on_pushButton_eliminar_clicked()
{
    if(ui->tabWidget->currentIndex() == 0){ // if clientes
        //int a;
        for (int i = 0;i < ui->tableWidget->rowCount(); i++){
            if(listaEliminar.at(i)->isChecked()){
                cliente.eraserecord(atoi(((QLineEdit*)listaId.at(i))->text().toStdString().c_str()));
                ui->tableWidget->removeRow(i);

                // eliminamos memoria dinamica
                delete listaEliminar.at(i);
                delete listaId.at(i);
                delete listaNombre.at(i);
                delete listaCorreo.at(i);

                // quitamos el puntero de la lista
                listaEliminar.removeAt(i);
                listaId.removeAt(i);
                listaNombre.removeAt(i);
                listaCorreo.removeAt(i);
                i = -1;
            }
        }
        cliente.avail.sort();
        ((QLineEdit*)listaId.at(listaId.length()-1))->setText(QString::number(cliente.avail.front()));
    } // fin if clientes
}

void MainWindow::on_pushButton_guardar_clicked()
{
    if(ui->tabWidget->currentIndex() == 0){ // if clientes
        qDebug() << ui->tabWidget->currentIndex();
        QString registro = "                                                                                    "; // fin

        for(int i = 0; i < ui->tableWidget->rowCount();i++){
            registro.replace (0,strlen(((QLineEdit*)listaId.at(i))->text().toStdString().c_str()),((QLineEdit*)listaId.at(i))->text());
            registro.replace(4,strlen(((QLineEdit*)listaNombre.at(i))->text().toStdString().c_str()),((QLineEdit*)listaNombre.at(i))->text());
            registro.replace(43,strlen(((QLineEdit*)listaCorreo.at(i))->text().toStdString().c_str()),((QLineEdit*)listaCorreo.at(i))->text());
        }
        cliente.writerecord(registro.toStdString().c_str(),2);
    }// fin if clientes
}

void MainWindow::LineEdit_guardar_enter()
{
    int rows = ui->tableWidget->rowCount();
    qDebug() << rows << " filas:";
    QWidget *widget = QApplication::focusWidget();
    QModelIndex index = ui->tableWidget->indexAt(widget->pos());

    if(index.row() == rows-1){
        if(((QLineEdit*)listaNombre.at(index.row()))->text().isEmpty() || ((QLineEdit*)listaCorreo.at(index.row()))->text().isEmpty()){
            QMessageBox::critical(this,"Error","Campos Vacios");

        }else{
            QString s=((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-2))->text();
            QString registro;
            if(s.length()==1){
                registro = "000                                                                                 "; // fin
                registro.replace (3,strlen(((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-2))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-2))->text());
            }
            if(s.length()==2){
                registro = "00                                                                                  "; // fin
                registro.replace (2,strlen(((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-2))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-2))->text());
            }
            if(s.length()==3){
                registro = "0                                                                                   "; // fin
                registro.replace (1,strlen(((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-2))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-2))->text());
            }
            if(s.length()==4){
                registro = "                                                                                    "; // fin
                registro.replace (0,strlen(((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-2))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-2))->text());
            }
            registro.replace(4,strlen(((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-1))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-1))->text());
            registro.replace(43,strlen(((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()))->text());
            cliente.writerecord(registro.toStdString().c_str(),(((QLineEdit*)ui->tableWidget->cellWidget(index.row(),1))->text().toInt()));
            crear_nuevaFila();
        }
    }else{
        if(((QLineEdit*)listaNombre.at(index.row()))->text().isEmpty() || ((QLineEdit*)listaCorreo.at(index.row()))->text().isEmpty()){
            QMessageBox::critical(this,"Error","Campos Vacios");

        }else{
            QString registro = "00                                                                                  "; // fin

            registro.replace (2,strlen(((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-2))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-2))->text());
            registro.replace(4,strlen(((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-1))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-1))->text());
            registro.replace(43,strlen(((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()))->text());

            cliente.updaterecord(registro.toStdString().c_str(),((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-2))->text().toInt());
        }
    }
}

void MainWindow::crear_nuevaFila()
{
    const int ultima_fila =  ui->tableWidget->rowCount();
    int fila = ui->tableWidget->rowCount();

    ui->tableWidget->insertRow(ultima_fila);
    QPointer<QCheckBox> eliminar = new QCheckBox(this);
    QPointer<QLineEdit>  id = new QLineEdit(this);
    QPointer<QLineEdit>  nombre = new QLineEdit(this);
    QPointer<QLineEdit>  correo = new QLineEdit(this);


    QRegExp validarNumeros("^[0-9]*$");

    id->setMaxLength(4);
    id->setValidator(new QRegExpValidator(validarNumeros, this));
    id->setEnabled(false);
    QString nuevo;
    if(!cliente.avail.empty()){ // verificamos si hay espacio disponible en el avial list
        qDebug() << "1: avail no vacio";
        if(leer){
            qDebug() << "leer por primera vez cierto:";
            leer = false;
            if(((QLineEdit*)listaId.at(listaId.length()-1))->text().toInt() == cliente.avail.front()){
                qDebug() << "id anterior es igual al nuevo: eliminar";
                cliente.avail.pop_front();
                if(!cliente.avail.empty())
                    id->setText(QString::number(cliente.avail.front()));
                else
                    id->setText(QString::number(ui->tableWidget->rowCount()));

            }
            else{
                if(cliente.avail.empty()){
                    id->setText(QString::number(ui->tableWidget->rowCount()));
                    qDebug() << "asignacion de ultima fila:";
                }
                else{
                    id->setText(QString::number(cliente.avail.front()));
                    qDebug() << "asignacion de avail:";
                }
            }
        }else{
            if(!cliente.avail.empty()){
                cliente.avail.pop_front();
                qDebug() << "deberia de borrar";
                if(!cliente.avail.empty()){
                    cliente.avail.sort();
                    qDebug() << "Nuevo: " << nuevo;
                    id->setText(QString::number(cliente.avail.front()));
                }else{

                    id->setText(QString::number(ui->tableWidget->rowCount()));
                }
            }
        }

    }else{

        id->setText(QString::number(ui->tableWidget->rowCount()));
    }
    nombre->setMaxLength(39);
    correo->setMaxLength(39);

    connect(correo,SIGNAL(returnPressed()),this,SLOT(LineEdit_guardar_enter()));

    ui->tableWidget->setCellWidget(ultima_fila,0,eliminar);
    ui->tableWidget->setCellWidget(ultima_fila,1,id);
    ui->tableWidget->setCellWidget(ultima_fila,2,nombre);
    ui->tableWidget->setCellWidget(ultima_fila,3,correo);


    listaEliminar.append(eliminar);
    listaId.append(id);
    listaNombre.append(nombre);
    listaCorreo.append(correo);
    nombre->setFocus();
}

void MainWindow::crear_nuevaFila(QString, QString, QString)
{

}

void MainWindow::on_actionNew_triggered()
{

}

void MainWindow::on_actionOpen_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Text File (*.txt)"));
    qDebug() << "path: " << path;
    //cliente = new ClientFile(path);
    cliente.path = path;

}
