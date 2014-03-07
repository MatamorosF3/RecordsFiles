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

    if(ui->tabWidget->currentIndex() == 0){ // inicio if clientes

        cliente.path = "Clientes.txt"; // asignamos el path de clientes para poder manejar el FILE IO de clientes
        const int cantidad_registros  =cliente.recordsSize(); // obtenemos el offset ubicado al final del archivo
        int cont = 0; // contador
        char buffer [84]; // buffer para realizar la lectura del clientes

        while(cont < cantidad_registros ){

            cliente.readrecord(buffer,cont);
            buffer[83] = '\0'; //asignacion del null manualmente
            cont += 84; // contar incrementa de acuerdo al tamaño del registro
            QString sId; // QString para obtener el id
            QString sNombre; // QString para obtener el nombre
            QString sCorreo; // QString para obtener el correo

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

            /* Por medio de los fors anteriores se obtenien los campos de cada registro
             * de modo que puedan ser agregados al QTableWidget sin ningun problema
             */

            const int ultima_fila =  ui->tableWidget->rowCount(); // obtenemos ultima fila generada en el qtablewidget
            if(sId[0] == '*') // verificamos si un archivo ha sido eliminado y asi no mostrarlo en la QTableWidget
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
            /* Las cuatros lineas anteriores representan la forma en la que
             * agregamos los QLineEdit a cada campo de cada registro
             */

            listaEliminar.append(eliminar);
            listaId.append(id);
            /*Las dos lineas anteriores representan la forma en que ingresamos
             * los datos del registro en listas diferentes para mentener un mejor orden
             * de los archivos a la hora de trabajar con ellos
             */

        } //fin while

    } // fin if clientes
    leer = true;
    crear_nuevaFila(); // metodo crear nueva fila
}

void MainWindow::on_pushButton_cerrar_clicked()
{
    cliente.updateAvail(); // actualizamos el availList del cliente
    this->close(); // cerramos el programa
}

void MainWindow::on_pushButton_eliminar_clicked()
{
    if(ui->tabWidget->currentIndex() == 0){ // if clientes

        for (int i = 0;i < ui->tableWidget->rowCount(); i++){
            if(listaEliminar.at(i)->isChecked()){
                cliente.eraserecord(atoi(((QLineEdit*)listaId.at(i))->text().toStdString().c_str()));
                /*En la linea anterior llamos al metodo de eraseRecord por medio del cual asignamos un
                 * asterisco al inicio de cada registro para saber que le hemos eliminado a la hora de
                 * realizar la lectura
                 */

                ui->tableWidget->removeRow(i); // eliminamos la fila del registro que ha sido seleccionado.

                // eliminamos memoria dinamica
                delete listaEliminar.at(i);
                delete listaId.at(i);

                // quitamos el puntero de la lista
                listaEliminar.removeAt(i);
                listaId.removeAt(i);
                i = -1;
            }
        }
        cliente.avail.sort(); // ordenmos el avail list de clientes
        ((QLineEdit*)listaId.at(listaId.length()-1))->setText(QString::number(cliente.avail.front())); // asignacion del nuevo id a utilizar en el QTableWidget
    } // fin if clientes
}


void MainWindow::LineEdit_guardar_enter()
{
    int rows = ui->tableWidget->rowCount(); // obtenemos la ultima fila del QTableWidget
    QWidget *widget = QApplication::focusWidget(); // obtenemos la fila en la que estamos situados a la hora de realizar enter en la ultima columna del registro
    QModelIndex index = ui->tableWidget->indexAt(widget->pos()); // con esta variable index podemos obtener la fila y columna en la que estemos posicionados
    QString name = ((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-1))->text(); // obtenemos el nombre del registro de la fila que estemos posicionados
    QString email = ((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()))->text(); // obtenemos el email del registro de la fila en que estemos posicionados

    if(index.row() == rows-1){ // inicio de if de validacion de ultima fila

        if(name.isEmpty() || email.isEmpty()){
            QMessageBox::critical(this,"Error","Campos Vacios");

        }else{
            QString id =((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-2))->text(); // obtenemos el id del registro de la fila en que estemos posicionados
            QString record; // creacion de un registro vacio para despues solomante sustituir los datos obtenidos de registro de la fila en que estemos posicionados
            if(id.length()==1){ // verificamos si id es solamente de 1 digito.
                record = "000                                                                                 "; // fin
                record.replace (3,strlen(id.toStdString().c_str()),id);
            }
            if(id.length()==2){ // verificamos si id es solamente de 2 digitos.
                record = "00                                                                                  "; // fin
                record.replace (2,strlen(id.toStdString().c_str()),id);
            }
            if(id.length()==3){ // verificamos si id es solamente de 3 digitos.
                record = "0                                                                                   "; // fin
                record.replace (1,strlen(id.toStdString().c_str()),id);
            }
            if(id.length()==4){// verificamos si id es solamente de 4 digito.
                record = "                                                                                    "; // fin
                record.replace (0,strlen(id.toStdString().c_str()),id);
            }
            //    QString name = ((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-1))->text(); // obtenemos el nombre del registro de la fila que estemos posicionados
            //   QString email = ((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()))->text(); // obtenemos el email del registro de la fila en que estemos posicionados
            record.replace(4,strlen(name.toStdString().c_str()),name); // ingresamos el nombre al registro nuevo
            record.replace(43,strlen(email.toStdString().c_str()),email); // ingresamos el email al registro nuevo
            cliente.writerecord(record.toStdString().c_str(),(((QLineEdit*)ui->tableWidget->cellWidget(index.row(),1))->text().toInt())); // mandamos a guardar al archivo el nuevo registro
            ui->statusBar->showMessage("Registro Guardado",2000);

            crear_nuevaFila(); // creacion de una nueva fila
        }
    }else{
        if(name.isEmpty() || email.isEmpty()){
            QMessageBox::critical(this,"Error","Campos Vacios");

        }else{
            QString id =((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-2))->text();
            QString registro;
            if(id.length()==1){
                registro = "000                                                                                 "; // fin
                registro.replace (3,strlen(id.toStdString().c_str()),id);
            }
            if(id.length()==2){
                registro = "00                                                                                  "; // fin
                registro.replace (2,strlen(id.toStdString().c_str()),id);
            }
            if(id.length()==3){
                registro = "0                                                                                   "; // fin
                registro.replace (1,strlen(id.toStdString().c_str()),id);
            }
            if(id.length()==4){
                registro = "                                                                                    "; // fin
                registro.replace (0,strlen(id.toStdString().c_str()),id);
            }
            registro.replace(4,strlen(name.toStdString().c_str()),name);
            registro.replace(43,strlen(email.toStdString().c_str()),email);
            qDebug() << "update:";
            cliente.updaterecord(registro.toStdString().c_str(),((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-2))->text().toInt());
            ui->statusBar->showMessage("Registro Modificado",2000);

        }
    }
}

void MainWindow::crear_nuevaFila()
{
    const int ultima_fila =  ui->tableWidget->rowCount();

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
        if(leer){
            leer = false;
            if(((QLineEdit*)listaId.at(listaId.length()-1))->text().toInt() == cliente.avail.front()){
                cliente.avail.pop_front();
                if(!cliente.avail.empty())
                    id->setText(QString::number(cliente.avail.front()));
                else
                    id->setText(QString::number(ui->tableWidget->rowCount()));
            }
            else{
                if(cliente.avail.empty()){
                    id->setText(QString::number(ui->tableWidget->rowCount()));
                }
                else{
                    id->setText(QString::number(cliente.avail.front()));
                }
            }
        }else{
            if(!cliente.avail.empty()){
                cliente.avail.pop_front();

                if(!cliente.avail.empty()){
                    cliente.avail.sort();
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
    nombre->setFocus();
}

void MainWindow::on_actionNew_triggered()
{

}

void MainWindow::on_actionOpen_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Text File (*.txt)"));
    cliente.path = path;
}
