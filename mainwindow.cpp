#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "clientfile.h"
#include "tdaindexfile.h"
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
    producto.path= "Productos.txt";
    categoria.path= "Categories.txt";
    

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
            //connect(correo,SIGNAL(returnPressed(),this,SLOT(LineEdit_guardar_enter()));
            //int ddd=0;
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
    crear_nuevaFila(); // metodo crear nueva fila
    } // fin if clientes

    if(ui->tabWidget->currentIndex() == 1){ // inicio if Categorias
        const int si  =categoria.recordsSize();
        int cont = 0;
        char buffer [24];
        while(cont < si ){

            categoria.readrecord(buffer,cont);
            //qDebug() <<buffer;
            buffer[23] = '\0';
            cont += 24;
            QString sId;//length de 4
            QString sNombre;//length de 20
            for(int i = 0; i < 4; i++){
                sId += buffer[i];
            }
            for(int i = 4; i < 24;i++){
                if(i != 23){
                    if(buffer[i] == ' ' && buffer[i+1] == ' ')
                        break;
                    else{
                        sNombre += buffer[i];
                    }
                }
            }
            const int ultima_fila =  ui->tableWidget_categorias->rowCount();
            if(sId[0] == '*')
                continue;
            ui->tableWidget_categorias->insertRow(ultima_fila);
            QPointer<QCheckBox> eliminar = new QCheckBox(this);
            QPointer<QLineEdit>  id = new QLineEdit(this);
            QPointer<QLineEdit>  nombre = new QLineEdit(this);
            connect(nombre,SIGNAL(returnPressed()),this,SLOT(LineEdit_guardar_enter_Categorias()));
            QRegExp validarNumeros("^[0-9]*$");
            id->setText(sId);
            id->setMaxLength(4);
            id->setValidator(new QRegExpValidator(validarNumeros, this));
            id->setEnabled(false);
            nombre->setMaxLength(19);
            nombre->setText(sNombre);
            ui->tableWidget_categorias->setCellWidget(ultima_fila,0,eliminar);
            ui->tableWidget_categorias->setCellWidget(ultima_fila,1,id);
            ui->tableWidget_categorias->setCellWidget(ultima_fila,2,nombre);

            listaEliminarCate.append(eliminar);
            listaIdCate.append(id);
            listaNombreCate.append(nombre);
        } //fin while
        crear_nuevaFila_Categorias();
    } // fin if categorias
    if(ui->tabWidget->currentIndex() == 2){ // inicio if productos
        const int si  =producto.recordsSize();
        int cont = 0;
        char buffer [37];
        while(cont < si ){

            producto.readrecord(buffer,cont);
            //qDebug() <<buffer;
            buffer[36] = '\0';
            cont += 37;
            QString sId;//length de 4
            QString sNombre;//length de 20
            QString sCategoria;//length de 4
            QString sPrecio;//length de 9
            for(int i = 0; i < 4; i++){
                sId += buffer[i];
            }
            for(int i = 4; i < 24;i++){
                if(i != 23){
                    if(buffer[i] == ' ' && buffer[i+1] == ' ')
                        break;
                    else{
                        sNombre += buffer[i];
                    }
                }
            }
            for(int i = 24; i < 29; i++){
                if(i != 28){
                    if(buffer[i] == ' ' && buffer[i+1] == ' ')
                        break;
                    else{
                        sCategoria += buffer[i];\
                    }
                }
            }
            for(int i = 28; i < 38; i++){
                if(i != 37){
                    if(buffer[i] == ' ' && buffer[i+1] == ' ')
                        break;
                    else{
                        sPrecio += buffer[i];
                    }
                }
            }

            const int ultima_fila =  ui->tableWidget_productos->rowCount();
            if(sId[0] == '*')
                continue;

            ui->tableWidget_productos->insertRow(ultima_fila);
            QPointer<QCheckBox> eliminar = new QCheckBox(this);
            QPointer<QLineEdit>  id = new QLineEdit(this);
            QPointer<QLineEdit>  nombre = new QLineEdit(this);
            QPointer<QLineEdit>  IdCategoria = new QLineEdit(this);
            QPointer<QLineEdit>  precio = new QLineEdit(this);
            connect(precio,SIGNAL(returnPressed()),this,SLOT(LineEdit_guardar_enter_Productos()));
                    QRegExp validarNumeros("^[0-9]*$");

            id->setText(sId);
            id->setMaxLength(4);
            id->setValidator(new QRegExpValidator(validarNumeros, this));
            id->setEnabled(false);

            nombre->setMaxLength(19);
            nombre->setText(sNombre);

            IdCategoria->setMaxLength(4);
            IdCategoria->setText(sCategoria);\

            precio->setMaxLength(7);
            precio->setText(sPrecio);
            ui->tableWidget_productos->setCellWidget(ultima_fila,0,eliminar);
            ui->tableWidget_productos->setCellWidget(ultima_fila,1,id);
            ui->tableWidget_productos->setCellWidget(ultima_fila,2,nombre);
            ui->tableWidget_productos->setCellWidget(ultima_fila,3,IdCategoria);
            ui->tableWidget_productos->setCellWidget(ultima_fila,4,precio);

            listaEliminarProd.append(eliminar);
            listaIdProd.append(id);
            listaNombreProd.append(nombre);
            listaIdCategoriaProd.append(IdCategoria);
            listaPrecio.append(precio);
        } //fin while
        crear_nuevaFila_Productos();
    } // fin if productos


    leer = true;

}

void MainWindow::on_pushButton_cerrar_clicked()
{


    cliente.updateAvail(); // actualizamos el availList del cliente
    producto.updateAvail(); // actualizamos el availList de producto
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

    if(ui->tabWidget->currentIndex() == 1){ // if categorias
        for (int i = 0;i < ui->tableWidget_categorias->rowCount(); i++){
            if(listaEliminarCate.at(i)->isChecked()){
                categoria.eraserecord(atoi(((QLineEdit*)listaIdCate.at(i))->text().toStdString().c_str()));
                ui->tableWidget_categorias->removeRow(i);

                // eliminamos memoria dinamica
                delete listaEliminarCate.at(i);
                delete listaIdCate.at(i);
                delete listaNombreCate.at(i);

                // quitamos el puntero de la lista
                listaEliminarCate.removeAt(i);
                listaIdCate.removeAt(i);
                listaNombreCate.removeAt(i);
                i = -1;
            }
        }
        categoria.AvailCat.sort();
        ((QLineEdit*)listaIdCate.at(listaIdCate.length()-1))->setText(QString::number(categoria.AvailCat.front()));
    } // fin if Categorias

    if(ui->tabWidget->currentIndex() == 2){ // if productos
        for (int i = 0;i < ui->tableWidget_productos->rowCount(); i++){
            if(listaEliminarProd.at(i)->isChecked()){
                producto.eraserecord(atoi(((QLineEdit*)listaIdProd.at(i))->text().toStdString().c_str()));
                ui->tableWidget_productos->removeRow(i);

                // eliminamos memoria dinamica
                delete listaEliminarProd.at(i);
                delete listaIdProd.at(i);
                delete listaNombreProd.at(i);
                delete listaIdCategoriaProd.at(i);
                delete listaPrecio.at(i);

                // quitamos el puntero de la lista
                listaEliminarProd.removeAt(i);
                listaIdProd.removeAt(i);
                listaNombreProd.removeAt(i);
                listaIdCategoriaProd.removeAt(i);
                listaPrecio.removeAt(i);
                i = -1;
            }
        }
        producto.avail.sort();
        ((QLineEdit*)listaIdProd.at(listaIdProd.length()-1))->setText(QString::number(producto.avail.front()));
    } // fin if productos
}


void MainWindow::LineEdit_guardar_enter()
{
// <<<<< HEAD
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

void MainWindow::LineEdit_guardar_enter_Categorias()
{
    int rows = ui->tableWidget_categorias->rowCount();
    QWidget *widget = QApplication::focusWidget();
    QModelIndex index = ui->tableWidget_categorias->indexAt(widget->pos());

    if(index.row() == rows-1){

        if(((QLineEdit*)listaNombreCate.at(index.row()))->text().isEmpty() || ((QLineEdit*)listaIdCate.at(index.row()))->text().isEmpty()){

            QMessageBox::critical(this,"Error","Campos Vacios");

        }else{
            QString s=((QLineEdit*)ui->tableWidget_categorias->cellWidget(index.row(),index.column()-1))->text();
            QString registro="";

            if(s.length()==1){
                registro = "000                     "; // fin
                registro.replace (3,strlen(((QLineEdit*)ui->tableWidget_categorias->cellWidget(index.row(),index.column()-1))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_categorias->cellWidget(index.row(),index.column()-1))->text());
            }
            if(s.length()==2){
                registro = "00                      "; // fin
                registro.replace (2,strlen(((QLineEdit*)ui->tableWidget_categorias->cellWidget(index.row(),index.column()-1))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_categorias->cellWidget(index.row(),index.column()-1))->text());
            }
            if(s.length()==3){
                registro = "0                       "; // fin
                registro.replace (1,strlen(((QLineEdit*)ui->tableWidget_categorias->cellWidget(index.row(),index.column()-1))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_categorias->cellWidget(index.row(),index.column()-1))->text());
            }
            if(s.length()==4){
                registro = "                        "; // fin
                registro.replace (0,strlen(((QLineEdit*)ui->tableWidget_categorias->cellWidget(index.row(),index.column()-1))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_categorias->cellWidget(index.row(),index.column()-1))->text());
            }
            registro.replace(4,strlen(((QLineEdit*)ui->tableWidget_categorias->cellWidget(index.row(),index.column()))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_categorias->cellWidget(index.row(),index.column()))->text());
            qDebug() << "REGRISTRO: " << registro;
            categoria.writerecord(registro.toStdString().c_str(),(((QLineEdit*)ui->tableWidget_categorias->cellWidget(index.row(),1))->text().toInt()));
            crear_nuevaFila_Categorias();
        }
    }else{//SI ESTA MODIFICANDO
        if(((QLineEdit*)listaNombreCate.at(index.row()))->text().isEmpty() || ((QLineEdit*)listaIdCate.at(index.row()))->text().isEmpty()){
            QMessageBox::critical(this,"Error","Campos Vacios");

        }else{
            QString registro=((QLineEdit*)ui->tableWidget_categorias->cellWidget(index.row(),index.column()-1))->text();
            qDebug() << "QLineEdit:" << registro.toStdString().c_str() << "Tamanio:" << strlen(((QLineEdit*)ui->tableWidget_categorias->cellWidget(index.row(),index.column()))->text().toStdString().c_str());
            registro.replace(4,strlen(((QLineEdit*)ui->tableWidget_categorias->cellWidget(index.row(),index.column()))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_categorias->cellWidget(index.row(),index.column()))->text());
            qDebug() << "REGRISTRO modificado: " << registro.toStdString().c_str() << "Tamanio:" << strlen(registro.toStdString().c_str());
            categoria.updaterecord(registro.toStdString().c_str(),((QLineEdit*)ui->tableWidget_categorias->cellWidget(index.row(),index.column()-1))->text().toInt());
        }
    }
}
void MainWindow::LineEdit_guardar_enter_Productos()
{

    int rows = ui->tableWidget_productos->rowCount();
    qDebug() << rows << " filas:";
    QWidget *widget = QApplication::focusWidget();
    QModelIndex index = ui->tableWidget_productos->indexAt(widget->pos());

    if(index.row() == rows-1){

        if(((QLineEdit*)listaNombreProd.at(index.row()))->text().isEmpty() || ((QLineEdit*)listaIdCategoriaProd.at(index.row()))->text().isEmpty() || ((QLineEdit*)listaPrecio.at(index.row()))->text().isEmpty()){
            QMessageBox::critical(this,"Error","Campos Vacios");
        }else{
            QString s=((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text();
            QString registro="";

            if(s.length()==1){
                registro = "000                                "; // fin
                registro.replace (3,strlen(((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text());
            }
            if(s.length()==2){
                registro = "00                                 "; // fin
                registro.replace (2,strlen(((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text());
            }
            if(s.length()==3){
                registro = "0                                  "; // fin
                registro.replace (1,strlen(((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text());
            }
            if(s.length()==4){
                registro = "                                   "; // fin
                registro.replace (0,strlen(((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text());
            }
            registro.replace(4,strlen(((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-2))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-2))->text());
            registro.replace(24,strlen(((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-1))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-1))->text());
            registro.replace(28,strlen(((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()))->text());
            qDebug() << "REGRISTRO: " << registro;
            producto.writerecord(registro.toStdString().c_str(),(((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),1))->text().toInt()));
            crear_nuevaFila_Productos();
        }
    }else{//SI ESTA MODIFICANDO
        if(((QLineEdit*)listaNombreProd.at(index.row()))->text().isEmpty() || ((QLineEdit*)listaIdCategoriaProd.at(index.row()))->text().isEmpty()|| ((QLineEdit*)listaPrecio.at(index.row()))->text().isEmpty()){
            QMessageBox::critical(this,"Error","Campos Vacios");

        }else{
            QString s=((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text();
            QString registro=s;
            qDebug() << "s: " << s;
            registro.replace(4,strlen(((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-2))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-2))->text());
            registro.replace(24,strlen(((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-1))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-1))->text());
            registro.replace(28,strlen(((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()))->text());
            qDebug() << "REGRISTRO modificado: " << registro.toStdString().c_str();
            producto.updaterecord(registro.toStdString().c_str(),((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text().toInt());
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

void MainWindow::crear_nuevaFila_Categorias()
{
    const int ultima_fila =  ui->tableWidget_categorias->rowCount();
    int fila = ui->tableWidget_categorias->rowCount();
}

void MainWindow::crear_nuevaFila_Productos()
{
    const int ultima_fila =  ui->tableWidget_productos->rowCount();
    int fila = ui->tableWidget_productos->rowCount();

    ui->tableWidget_productos->insertRow(ultima_fila);
    QPointer<QCheckBox> eliminar = new QCheckBox(this);
    QPointer<QLineEdit>  id = new QLineEdit(this);
    QPointer<QLineEdit>  nombre = new QLineEdit(this);
    QPointer<QLineEdit>  idcategoria = new QLineEdit(this);
    QPointer<QLineEdit>  precio = new QLineEdit(this);

    QRegExp validarNumeros("^[0-9]*$");

    id->setMaxLength(4);
    id->setValidator(new QRegExpValidator(validarNumeros, this));
    id->setEnabled(false);
    QString nuevo;
    if(!producto.avail.empty()){ // verificamos si hay espacio disponible en el avial list
        qDebug() << "1: avail no vacio";
        if(leer){
            qDebug() << "leer por primera vez cierto:";
            leer = false;
            if(((QLineEdit*)listaIdProd.at(listaIdProd.length()-1))->text().toInt() == producto.avail.front()){
                qDebug() << "id anterior es igual al nuevo: eliminar";
                producto.avail.pop_front();
                if(!producto.avail.empty())
                    id->setText(QString::number(producto.avail.front()));
                else
                    id->setText(QString::number(ui->tableWidget_productos->rowCount()));

            }
            else{
                if(producto.avail.empty()){
                    id->setText(QString::number(ui->tableWidget_productos->rowCount()));
                    qDebug() << "asignacion de ultima fila:";
                }
                else{
                    id->setText(QString::number(producto.avail.front()));
                    qDebug() << "asignacion de avail:";
                }
            }
        }else{
            if(!producto.avail.empty()){
                producto.avail.pop_front();
                qDebug() << "deberia de borrar";
                if(!producto.avail.empty()){
                    producto.avail.sort();
                    qDebug() << "Nuevo: " << nuevo;
                    id->setText(QString::number(producto.avail.front()));
                }else{

                    id->setText(QString::number(ui->tableWidget_productos->rowCount()));
                }
            }
        }

    }else{

        id->setText(QString::number(ui->tableWidget_productos->rowCount()));
    }
    id->setMaxLength(4);
    nombre->setMaxLength(19);
    idcategoria->setMaxLength(4);
    precio->setMaxLength(7);
    connect(precio,SIGNAL(returnPressed()),this,SLOT(LineEdit_guardar_enter_Productos()));

    ui->tableWidget_productos->setCellWidget(ultima_fila,0,eliminar);
    ui->tableWidget_productos->setCellWidget(ultima_fila,1,id);
    ui->tableWidget_productos->setCellWidget(ultima_fila,2,nombre);
    ui->tableWidget_productos->setCellWidget(ultima_fila,3,idcategoria);
    ui->tableWidget_productos->setCellWidget(ultima_fila,4,precio);

    listaEliminarProd.append(eliminar);
    listaIdProd.append(id);
    listaNombreProd.append(nombre);
    listaIdCategoriaProd.append(idcategoria);
    listaPrecio.append(precio);
    nombre->setFocus();
}



void MainWindow::crear_nuevaFila(QString, QString, QString)
{

}

void MainWindow::on_actionOpen_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Text File (*.txt)"));
    if(path.endsWith("Cliente.txt")){
        cliente.path = path;
    }

}
