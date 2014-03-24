#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "clientfile.h"
#include "tdaindexfile.h"
#include "tdafile.h"
#include "arbolb.h"
#include "arbolbnodo.h"
#include <QMessageBox>
#include <QFileDialog>
#include <list>
#include <time.h>
#include <QMap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget_buscarCliente->setFixedHeight(55);
    ui->tableWidget_buscarCategoria->setFixedHeight(55);
    ui->tableWidget_buscarProducto->setFixedHeight(55);
}

MainWindow::~MainWindow()
{

    for (int i = 0;i < listaEliminar.size(); i++){


        /*En la linea anterior llamos al metodo de eraseRecord por medio del cual asignamos un
             * asterisco al inicio de cada registro para saber que le hemos eliminado a la hora de
             * realizar la lectura
             */

        // eliminamos memoria dinamica
        delete listaEliminar.at(i);
        delete listaId.at(i);

        // quitamos el puntero de la lista
        listaEliminar.removeAt(i);
        listaId.removeAt(i);
        i= -1;


    }
    for(int i = 0; i<listaEliminarCate.size();i++){
        delete listaEliminarCate.at(i);
        delete listaIdCate.at(i);
        //delete listaNombreCate.at(i);

        // quitamos el puntero de la lista
        listaEliminarCate.removeAt(i);
        listaIdCate.removeAt(i);
        //listaNombreCate.removeAt(i);
        i= -1;
    }

    for(int i = 0; i <listaEliminarProd.size();i++){

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

    if(leer){
        cliente.updateAvail(); // actualizamos el availList del cliente
        producto.updateAvail(); // actualizamos el availList de producto
        categoria.updateAvailCat();//actualizamos el availList de categoria
        indice.updaterecord("IndexClientes.txt");
        indiceCat.updaterecord("IndexCat.txt");
        indiceProd.updaterecord("IndexProd.txt");
    }
    delete ui;
}



void MainWindow::on_pushButton_leer_clicked()
{
    // cliente.path = "Clientes.txt";
    ui->statusBar->showMessage("Realizando lectura de datos...",2000);
    producto.path= "Productos.txt";
    categoria.path= "Categories.txts";
    ui->pushButton_leer->setDisabled(true);
    int cantregindice=indice.recordsSize("IndexClientes.txt"); // obtenemos el tamaño del archivo de indice de clientes
    int cantIndiceCat = indiceCat.recordsSize("IndexCat.txt");
    int cantIndiceProd = indiceProd.recordsSize("IndexProd.txt");
    bool existeindiceProd = true;
    bool existeindice=true; // variable para saber si el archivo indice existe o no
    bool existeindiceCat = true;
    if(cantregindice==-1 || cantregindice == 0){ // si el tamaño del archivo == -1 el archivo indice de clientes no existe
        existeindice=false;
    }
    if(cantIndiceCat == -1 || cantIndiceCat == 0){
        existeindiceCat = false;
    }
    if(cantIndiceProd == -1 || cantIndiceProd == 0){
        existeindiceProd = false;
    }
    if(existeindiceProd){
        indiceProd.readrecord("IndexProd.txt");
        indiceProd.tamanioInicial = indiceProd.indices2.size();
    }
    if(existeindiceCat){
        indiceCat.readrecord("IndexCat.txt");
        indiceCat.tamanioInicial = indiceCat.indices2.size();
    }
    if(existeindice){ // si el archivo indice cliente existe creamos un tamaño del mapa para verificar si luego se tendrá que volver a crear el archivo indice
        indice.readrecord("IndexClientes.txt");
        indice.tamanioInicial=indice.indices2.size();
    }

    if(ui->tabWidget->currentIndex() == 0 || ui->tabWidget->currentIndex() == 1 || ui->tabWidget->currentIndex() == 2|| ui->tabWidget->currentIndex() == 3){ // inicio if clientes

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
            //manejo de indice
            if(!existeindice){
                int llave=atoi(sId.toStdString().c_str());
                if(llave<1){
                    indice.indices2.insert(atoi(sId.toStdString().c_str()),0);

                }else{
                    indice.indices2.insert(atoi(sId.toStdString().c_str()),(atoi(sId.toStdString().c_str())-1)*84);
                }
            }

            //fin manejo de indice
            ui->comboBox_IdCliente->addItem(QString::number(atoi(sId.toStdString().c_str()))); // agregemos los id de los clientes en el combobox de consultas

            ui->tableWidget->insertRow(ultima_fila); // creamos nueva fila
            QPointer<QCheckBox> eliminar = new QCheckBox(this);
            QPointer<QLineEdit>  id = new QLineEdit(this);
            QPointer<QLineEdit>  nombre = new QLineEdit(this);
            QPointer<QLineEdit>  correo = new QLineEdit(this);
            /*Creamos los LineEdit a insertar en la tabla a mostrar por medio
             * del cual establecemos las validacion para cada campo
             */

            connect(correo,SIGNAL(returnPressed()),this,SLOT(LineEdit_guardar_enter()));
            /*En la linea anterior creamos una señar por medio de la cual nos aseguramos
             * que cuando al usuario haga enter en la ultima columna ya sea para guardar
             * o modificar registro no existan campos vacios
             */
            QRegExp validarNumeros("^[0-9]*$"); // validacion para que solo se puedan ingresar digitos

            id->setText(sId);
            id->setMaxLength(4);
            id->setValidator(new QRegExpValidator(validarNumeros, this));
            id->setEnabled(false);

            nombre->setMaxLength(39);
            nombre->setText(sNombre);

            correo->setMaxLength(39);
            correo->setText(sCorreo);
            /* En las lineas anterior establecemos parametros como
             * la del maximo tamaño que tiene cada campo y a su vez
             * le asignamos el registro leido a cada campo correspondiente
             */

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
        // indice.tamanioInicial=indice.indices2.size();
        crear_nuevaFila(); // metodo crear nueva fila

    } // fin if clientes

    if(ui->tabWidget->currentIndex() == 0 || ui->tabWidget->currentIndex() == 1 || ui->tabWidget->currentIndex() == 2){ // inicio if Categorias
        const int si  =categoria.recordsSize(); // obtenemos el tamaño del archivo de categorias para poder realizar una lectura
        int cont = 0; // incializamos un contador en 0 por medio del cual nos iremos moviendo a traves del archivo ya que funciona como offset
        char buffer [25]; // creamos un buffer de 25 que es del tamaño fijo de un registro de categoroias
        while(cont < si ){ // incia while de lectura de categoria

            categoria.readrecord(buffer,cont); // funcion por medio del cual obtenemos un registro del archivo de categorias
            buffer[24] = '\0'; // asignamos caracter null al arreglo para saber que hemos llegado al final y no tener problemas con basura de caracteres generada aleatoreamente
            cont += 24;
            /*en la linea anterior incrementamos el contador en 24
             * porque sabemos que cada registro del archivo de categorias es
             * de 24 bytes por lo tanto se moverá el offset a conveniencia propia
             */
            QString sId;//length de 4
            QString sNombre;//length de 20
            for(int i = 0; i < 4; i++){ // for para obtener el id del registro leido
                sId += buffer[i]; // obtenemos el id
            }
            for(int i = 4; i < 25;i++){ // for para obtener el nombre del registro leido
                if(i != 24){
                    if(buffer[i] == ' ' && buffer[i+1] == ' ')
                        break;
                    else{
                        sNombre += buffer[i]; // obtenemos el nombre
                    }
                }
            }
            const int ultima_fila =  ui->tableWidget_categorias->rowCount(); // obtenemos la ultima fila de la tabla
            if(sId[0] == '*') // verificamos si el archivo ha sido eliminado
                continue;

            if(!existeindiceCat){
                int llave=atoi(sId.toStdString().c_str());
                if(llave<1){
                    indiceCat.indices2.insert(atoi(sId.toStdString().c_str()),0);

                }else{
                    indiceCat.indices2.insert(atoi(sId.toStdString().c_str()),(atoi(sId.toStdString().c_str())-1)*24);
                }
            }
            ui->tableWidget_categorias->insertRow(ultima_fila); // Creacion de la fila de la tabla de categorias
            QPointer<QCheckBox> eliminar = new QCheckBox(this);
            QPointer<QLineEdit>  id = new QLineEdit(this);
            QPointer<QLineEdit>  nombre = new QLineEdit(this);

            /*En la 3 lineas anteriores se crean los LineEdit que
             * iran en la tabla de categorias cada una con sus validaciones requeridads
             */

            connect(nombre,SIGNAL(returnPressed()),this,SLOT(LineEdit_guardar_enter_Categorias()));
            /* En la linea anterior se crea una conexion para asegurar que cuando se vaya a
             *  guardar un nuevo registro o modificar un nuevo registro no exista campo vacio
             */
            QRegExp validarNumeros("^[0-9]*$"); // validacion de que id solo sean numeros
            id->setText(sId);
            id->setMaxLength(4);
            id->setValidator(new QRegExpValidator(validarNumeros, this));
            id->setEnabled(false);
            nombre->setMaxLength(20);
            nombre->setText(sNombre);
            ui->tableWidget_categorias->setCellWidget(ultima_fila,0,eliminar);
            ui->tableWidget_categorias->setCellWidget(ultima_fila,1,id);
            ui->tableWidget_categorias->setCellWidget(ultima_fila,2,nombre);

            listaEliminarCate.append(eliminar); // se agrega a lista de apuntadores de QLineEdit para llevar un mejor control a la hora de eliminar un registro
            listaIdCate.append(id); // se agrega a la lista id de categorias para mejor control a la hora de realizar cambios o eliminar
            //listaNombreCate.append(nombre);
        } //fin while
        crear_nuevaFila_Categorias(); // metodo de crear nueva fila en la tabla de categorias
    } // fin if categorias

    //inicio if productos
    if(ui->tabWidget->currentIndex() == 0 || ui->tabWidget->currentIndex() == 1 || ui->tabWidget->currentIndex() == 2){ // inicio if productos
        const int si  =producto.recordsSize(); // se obtiene el tamaño del archivo de producto para la lectura
        int cont = 0; // se inicializa el contador en 0 y luego se ira incrementando para la lectura de registro de producto
        char buffer [37]; // se crea buffer de 37 ya que cada registro de producto tiene un tamaño fijo de 36 bytes
        while(cont < si ){ // inicio while de lectura de registros de productos en el archivo de producto

            producto.readrecord(buffer,cont); // metodo para leer un registro de producto
            buffer[36] = '\0'; // asignacion del caracter null para saber que se ha llegado al final y no tener problema con caracteres basura(Q"#!"#$!)
            cont += 36; // incrementacion de contador de 36 porque cada registro de producto es de 36 bytes y recordar que funciona como offset
            QString sId;//length de 4
            QString sNombre;//length de 19
            QString sCategoria;//length de 4
            QString sPrecio;//length de 9
            for(int i = 0; i < 4; i++){ // for para obtene id de producto
                sId += buffer[i]; // obtener id producto
            }
            for(int i = 4; i < 23;i++){ // for para obtener nombre del producto
                if(i != 23){
                    if(buffer[i] == ' ' && buffer[i+1] == ' ')
                        break;
                    else{
                        sNombre += buffer[i]; // obtener nombre del producto
                    }
                }
            }
            for(int i = 23; i < 27; i++){ // for para obtener id de categoria del producto
                if(i != 27){
                    if(buffer[i] == ' ' && buffer[i+1] == ' ')
                        break;
                    else{
                        sCategoria += buffer[i];// obtener id de categoria de producto
                    }
                }
            }
            for(int i = 27; i < 36; i++){ // for para obtener el precio del producto
                if(i != 36){
                    if(buffer[i] == ' ' && buffer[i+1] == ' ')
                        break;
                    else{
                        sPrecio += buffer[i]; // obtener precio de producto
                    }
                }
            }

            int ultima_fila =  ui->tableWidget_productos->rowCount(); // obtener ultima fila de la tabla de productos
            if(sId[0] == '*') // verificar si un registro de productos ha sido borrado y no mostrarlo en tabla de productos
                continue;

            if(!existeindiceProd){
                int llave=atoi(sId.toStdString().c_str());
                if(llave<1){
                    indiceProd.indices2.insert(atoi(sId.toStdString().c_str()),0);

                }else{
                    indiceProd.indices2.insert(atoi(sId.toStdString().c_str()),(atoi(sId.toStdString().c_str())-1)*36);
                }
            }
            ui->tableWidget_productos->insertRow(ultima_fila); // insertar fila en la tabla de producto
            QPointer<QCheckBox> eliminar = new QCheckBox(this);
            QPointer<QLineEdit>  id = new QLineEdit(this);
            QPointer<QLineEdit>  nombre = new QLineEdit(this);
            QPointer<QLineEdit>  IdCategoria = new QLineEdit(this);
            QPointer<QLineEdit>  precio = new QLineEdit(this);
            QPointer<QComboBox> IdCat = new QComboBox(this);

            /*En las 6 lineas anteriores se crean apuntadores de QLineEdit para poder
             * ingresarlos en la tabla de productos cada uno con su validacion y tener
             * mejor manejo de los datos tanto como las validaciones
             */


            for (int i = 0;i < ui->tableWidget_categorias->rowCount()-1; i++){ // inicio for comboBox de id categoria en tabla producto
                IdCat->addItem(((QLineEdit*)ui->tableWidget_categorias->cellWidget(i,1))->text()); // se llena el combobox

            }
            for (int i = 0;i < ui->tableWidget_categorias->rowCount()-1; i++){

                IdCat->setCurrentIndex(i);

                if(IdCat->currentText() == sCategoria){
                    IdCat->setCurrentIndex(i);
                    break;
                }
            } // fin for comboBox


            connect(precio,SIGNAL(returnPressed()),this,SLOT(LineEdit_guardar_enter_Productos()));
            /* En la linea anterior se crea la señal para poder validar que cuando se quiera modificar o
             * guardar un registro no exista ningun campo vacio
             */
            QRegExp validarNumeros("^[0-9]*$"); // valdacion del id


            id->setText(sId);
            id->setMaxLength(4);
            id->setValidator(new QRegExpValidator(validarNumeros, this));
            id->setEnabled(false);

            nombre->setMaxLength(19);
            nombre->setText(sNombre);

            IdCategoria->setMaxLength(4);
            IdCategoria->setText(sCategoria);\

            precio->setMaxLength(9);
            precio->setText(sPrecio);
            /*En las 13 lineas anteriores se crean las validaciones de los campos
             * segun lo requerido por el programa
             */

            ui->tableWidget_productos->setCellWidget(ultima_fila,0,eliminar);
            ui->tableWidget_productos->setCellWidget(ultima_fila,1,id);
            ui->tableWidget_productos->setCellWidget(ultima_fila,2,nombre);
            ui->tableWidget_productos->setCellWidget(ultima_fila,3,IdCat);
            ui->tableWidget_productos->setCellWidget(ultima_fila,4,precio);

            /* En las 4 lineas anteriores se inserta los QLineEdit a la tabla de productos
                 * y cada QLineEdit con su validacion necesaria creada anterioremente
                 */

            listaEliminarProd.append(eliminar);
            listaIdProd.append(id);
            listaNombreProd.append(nombre);
            listaIdCategoriaProd.append(IdCategoria);
            listaPrecio.append(precio);
            /* En las 5 lineas anteriores se ingresan datos a su lista correspondiente
             * y asi poder tener un mejor control de los datos a la hora de agregar,
             * verificar o eliminar
             */
        } //fin while
        crear_nuevaFila_Productos(); // metodo para crear nueva fila en QTableWidget de producto
    } // fin if productos
    leer = true;
    ui->statusBar->showMessage("Lectura de datos realizada...",2000);

}

void MainWindow::LineEdit_guardar_enter()
{
    int rows = ui->tableWidget->rowCount(); // obtenemos la ultima fila del QTableWidget
    QWidget *widget = QApplication::focusWidget(); // obtenemos la fila en la que estamos situados a la hora de realizar enter en la ultima columna del registro
    QModelIndex index = ui->tableWidget->indexAt(widget->pos()); // con esta variable index podemos obtener la fila y columna en la que estemos posicionados
    QString name = ((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()-1))->text(); // obtenemos el nombre del registro de la fila que estemos posicionados
    QString email = ((QLineEdit*)ui->tableWidget->cellWidget(index.row(),index.column()))->text(); // obtenemos el email del registro de la fila en que estemos posicionados

    if(index.row() == rows-1){ // inicio de if de validacion de ultima fila
        if(name.isEmpty() || email.isEmpty()){ // if para verificar que no existan campos vacios
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

            record.replace(4,strlen(name.toStdString().c_str()),name); // ingresamos el nombre al registro nuevo
            record.replace(43,strlen(email.toStdString().c_str()),email); // ingresamos el email al registro nuevo
            indice.indices2.insert(atoi(id.toStdString().c_str()),(atoi(id.toStdString().c_str())-1)*84); // se ingresa id con su offset
            cliente.writerecord(record.toStdString().c_str(),id.toInt()); // mandamos a guardar al archivo el nuevo registro
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
            /*En los ifs anteriores nos aseguramos del tamaño del id
             * ya que los ids tienen un maximo de 4 bytes entonce para
             * llevar un mayor control nos queremos asegurar de que se ocupen
             * los 4 bytes. Si id = 34, se guardara de la siguiente manera
             * 0034 para mejor control
             */

            registro.replace(4,strlen(name.toStdString().c_str()),name); // ingresamos el nombre en la posicion correspondiente para guardar el nuevo registro
            registro.replace(43,strlen(email.toStdString().c_str()),email); // ingresamos el email en la posicion correspondiente para guardar el nuevo registro
            cliente.updaterecord(registro.toStdString().c_str(),id.toInt());  // se manda a escribir el nuevo registro junto con su offset correspondiente
            ui->statusBar->showMessage("Registro Modificado",2000); // status bar el cual indica el la parte inferior de la tabla que el registro ha sido modificado

        }
    } // fin else guardar registro cliente
}

void MainWindow::LineEdit_guardar_enter_Categorias()
{
    int rows = ui->tableWidget_categorias->rowCount(); // se obtiene la ultima fila de la tabla de categorias
    QWidget *widget = QApplication::focusWidget(); // obtenemos en que parte de la tabla esta enfocado el usuario
    QModelIndex index = ui->tableWidget_categorias->indexAt(widget->pos()); // luego se obtiene la inforamcion en que
    QString name = ((QLineEdit*)ui->tableWidget_categorias->cellWidget(index.row(),index.column()))->text(); // obtenemos el nombre del registro de la fila que estemos posicionados
    QString id = ((QLineEdit*)ui->tableWidget_categorias->cellWidget(index.row(),index.column()-1))->text(); // obtenemos el id de la fila en que el usuario se encuentre posicionado



    if(index.row() == rows-1){ // verificamos si esta en la ultima fila y asi poder crear una nueva ya que siempre se creara una fila nueva al final
        if(name.isEmpty()){ // si nombre esta vacio se lanza msj de error
            QMessageBox::critical(this,"Error","Campos Vacios");
        }else{
            QString registro="                        "; // creacion de la variable registro para almacenar el nuevo registro a guardar

            if(id.length()==1){
                registro = "000                     "; // fin
                registro.replace (3,strlen(id.toStdString().c_str()),id);
            }

            if(id.length()==2){
                registro = "00                      "; // fin
                registro.replace (2,strlen(id.toStdString().c_str()),id);
            }

            if(id.length()==3){
                registro = "0                       "; // fin
                registro.replace (1,strlen(id.toStdString().c_str()),id);
            }

            if(id.length()==4){
                registro = "                        "; // fin
                registro.replace (0,strlen(id.toStdString().c_str()),id);
            }

            /* en las lineas anteriores se verifica que el id del registro de categorias se vaya a guardar de forma canonica
             * si el registro solo tiene dos digitos se le debera de agregar 0023 y asi sucesivamente de manera de hacer fijo
             * el tamaño de id de categoria
             */
            registro.replace(4,strlen(name.toStdString().c_str()),name); // ingresamos el nombre el parte correspondiente del registro en blanco
            categoria.writerecord(registro.toStdString().c_str(),id.toInt()); // mandamos a escribir el nuevo registro al archivo junto con su id el cual nos falicita a la hora de econtrar el offset
            ui->statusBar->showMessage("Registro Guardado",2000); // muestra en la parte inferior de la ventana que el registro ha sido guardado
            crear_nuevaFila_Categorias(); // metodo para crear nueva fila de categorias
        }
    }else{//SI ESTA MODIFICANDO
        if(name.isEmpty()){ // if para verificar que no existan campos vacios
            QMessageBox::critical(this,"Error","Campos Vacios");
        }else{
            QString registro="                        ";
            registro.replace(0, strlen(id.toStdString().c_str()),id);
            registro.replace(4,strlen(name.toStdString().c_str()),name);
            categoria.updaterecord(registro.toStdString().c_str(),id.toInt());
            ui->statusBar->showMessage("Registro Modificado",2000); // muestra mensaje en la parte inferior de la ventana
        }
    }
}
void MainWindow::LineEdit_guardar_enter_Productos()
{
    int rows = ui->tableWidget_productos->rowCount(); // obtenemos la ultima fila de la tabla de productos
    QWidget *widget = QApplication::focusWidget(); // averiguamos en que posicion se encuentra
    QModelIndex index = ui->tableWidget_productos->indexAt(widget->pos()); // obtenemos la posicion para poder saber la fila y columna en que se encuentra el usuario

    if(index.row() == rows-1){
        if(((QLineEdit*)listaNombreProd.at(index.row()))->text().isEmpty()  || ((QLineEdit*)listaPrecio.at(index.row()))->text().isEmpty()){ // if para verificar que no este vacio ningun campo
            QMessageBox::critical(this,"Error","Campos Vacios"); // msj de campos vacios
        }else{
            QString s=((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text(); // tomamos el tamaño del indice
            QString registro="                                     ";

            if(s.length()==1){
                registro = "000                                  "; // fin
                registro.replace (3,strlen(((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text());
            }
            if(s.length()==2){
                registro = "00                                   "; // fin
                registro.replace (2,strlen(((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text());
            }
            if(s.length()==3){
                registro = "0                                    "; // fin
                registro.replace (1,strlen(((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text());
            }
            if(s.length()==4){
                registro = "                                     "; // fin
                registro.replace (0,strlen(((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text());
            }
            registro.replace(4,strlen(((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-2))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-2))->text());
            registro.replace(23,strlen(((QComboBox*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-1))->currentText().toStdString().c_str()),((QComboBox*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-1))->currentText());
            registro.replace(27,strlen(((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()))->text());
            producto.writerecord(registro.toStdString().c_str(),(((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),1))->text().toInt()));
            crear_nuevaFila_Productos();
        }
    }else{//SI ESTA MODIFICANDO
        if(((QLineEdit*)listaNombreProd.at(index.row()))->text().isEmpty() ||  ((QLineEdit*)listaPrecio.at(index.row()))->text().isEmpty()){
            QMessageBox::critical(this,"Error","Campos Vacios");

        }else{
            QString id=((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text();
            QString registro = "                                     "; // fin
            registro.replace(0,strlen(id.toStdString().c_str()),id);
            registro.replace(4,strlen(((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-2))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-2))->text());
            registro.replace(23,strlen(((QComboBox*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-1))->currentText().toStdString().c_str()),((QComboBox*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-1))->currentText());
            registro.replace(27,strlen(((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()))->text().toStdString().c_str()),((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()))->text());
            producto.updaterecord(registro.toStdString().c_str(),((QLineEdit*)ui->tableWidget_productos->cellWidget(index.row(),index.column()-3))->text().toInt());
        }
    }
}
void MainWindow::crear_nuevaFila()
{
    const int ultima_fila =  ui->tableWidget->rowCount(); // obtenemos la ultima fila del la tabla de clientes

    ui->tableWidget->insertRow(ultima_fila); // creamos la nueva tabla de registros de clientes
    QPointer<QCheckBox> eliminar = new QCheckBox(this);
    QPointer<QLineEdit>  id = new QLineEdit(this);
    QPointer<QLineEdit>  nombre = new QLineEdit(this);
    QPointer<QLineEdit>  correo = new QLineEdit(this);
    /*En las 4 lineas anteriores se crean los apuntadores de QLineEdit para ingresarlos a
     * a la tabla de clientes
     */
    QRegExp validarNumeros("^[0-9]*$");


    id->setMaxLength(4);
    id->setValidator(new QRegExpValidator(validarNumeros, this));
    id->setEnabled(false);
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

    /* En el if anterior se verfica que todo este en orden el el avail list
     * y poder mostrar el id que corresponde en la tabla al crear o borrar un nuevo registro
     */

    nombre->setMaxLength(39);
    correo->setMaxLength(39);

    connect(correo,SIGNAL(returnPressed()),this,SLOT(LineEdit_guardar_enter()));
    /* creamos la conexion para verificar cada vez que se quiera
     * modificar o guardar un nuevo registro no existan campos vacos
     */

    ui->tableWidget->setCellWidget(ultima_fila,0,eliminar);
    ui->tableWidget->setCellWidget(ultima_fila,1,id);
    ui->tableWidget->setCellWidget(ultima_fila,2,nombre);
    ui->tableWidget->setCellWidget(ultima_fila,3,correo);
    /* asignamos los QLineEdit creados anterioremente a la tabla de clientes*/

    listaEliminar.append(eliminar);
    listaId.append(id);
    nombre->setFocus();

}

void MainWindow::crear_nuevaFila_Categorias()
{
    const int ultima_fila =  ui->tableWidget_categorias->rowCount();
    ui->tableWidget_categorias->insertRow(ultima_fila);
    QPointer<QCheckBox> eliminar = new QCheckBox(this);
    QPointer<QLineEdit>  id = new QLineEdit(this);
    QPointer<QLineEdit>  nombre = new QLineEdit(this);
    /*En las 3 lineas anteriores se crean los apuntadores de QLineEdit para ingresarlos a
     * a la tabla de categoria
     */
    QRegExp validarNumeros("^[0-9]*$");
    id->setMaxLength(4);
    id->setValidator(new QRegExpValidator(validarNumeros, this));
    id->setEnabled(false);
    if(!categoria.AvailCat.empty()){ // verificamos si hay espacio disponible en el avial list
        if(leer){
            leer = false;
            if(((QLineEdit*)listaIdCate.at(listaIdCate.length()-1))->text().toInt() == categoria.AvailCat.front()){
                categoria.AvailCat.pop_front();
                if(!categoria.AvailCat.empty())
                    id->setText(QString::number(categoria.AvailCat.front()));
                else
                    id->setText(QString::number(ui->tableWidget_categorias->rowCount()));
            }
            else{
                if(categoria.AvailCat.empty()){
                    id->setText(QString::number(ui->tableWidget_categorias->rowCount()));
                }
                else{
                    id->setText(QString::number(categoria.AvailCat.front()));
                }
            }
        }else{
            if(!categoria.AvailCat.empty()){
                categoria.AvailCat.pop_front();
                if(!categoria.AvailCat.empty()){
                    categoria.AvailCat.sort();
                    id->setText(QString::number(categoria.AvailCat.front()));
                }else{
                    id->setText(QString::number(ui->tableWidget_categorias->rowCount()));
                }
            }
        }

    }else{
        id->setText(QString::number(ui->tableWidget_categorias->rowCount()));
    }
    /* En el if anterior se verfica que todo este en orden el el avail list
     * y poder mostrar el id que corresponde en la tabla al crear o borrar un nuevo registro
     */
    id->setMaxLength(4);
    nombre->setMaxLength(19);
    connect(nombre,SIGNAL(returnPressed()),this,SLOT(LineEdit_guardar_enter_Categorias()));
    /* creamos la conexion para verificar cada vez que se quiera
     * modificar o guardar un nuevo registro no existan campos vacos
     */
    ui->tableWidget_categorias->setCellWidget(ultima_fila,0,eliminar);
    ui->tableWidget_categorias->setCellWidget(ultima_fila,1,id);
    ui->tableWidget_categorias->setCellWidget(ultima_fila,2,nombre);

    /* asignamos los QLineEdit creados anterioremente a la tabla de categorias*/

    listaEliminarCate.append(eliminar);
    listaIdCate.append(id);
    //listaNombreCate.append(nombre);
    nombre->setFocus();
}


void MainWindow::crear_nuevaFila_Productos()
{
    const int ultima_fila =  ui->tableWidget_productos->rowCount(); // obtenemos ultima fila de la tabla de producto
    ui->tableWidget_productos->insertRow(ultima_fila); // creamos la nueva fila
    QPointer<QCheckBox> eliminar = new QCheckBox(this);
    QPointer<QLineEdit>  id = new   QLineEdit(this);
    QPointer<QLineEdit>  nombre = new QLineEdit(this);
    QPointer<QLineEdit>  idcategoria = new QLineEdit(this);
    QPointer<QLineEdit>  precio = new QLineEdit(this);
    QPointer<QComboBox>  IdCat = new QComboBox(this);
    /*En las 6 lineas anteriores se crean los apuntadores de QLineEdit para ingresarlos a
     * a la tabla de productos
     */
    for (int i = 0;i < ui->tableWidget_categorias->rowCount()-1; i++){ // inicio for comboBox
        IdCat->addItem(((QLineEdit*)ui->tableWidget_categorias->cellWidget(i,1))->text());

    } // fin for comboBox

    QRegExp validarNumeros("^[0-9]*$");

    id->setMaxLength(4);
    id->setValidator(new QRegExpValidator(validarNumeros, this));
    id->setEnabled(false);
    if(!producto.avail.empty()){ // verificamos si hay espacio disponible en el avial list
        if(leer){
            leer = false;
            if(((QLineEdit*)listaIdProd.at(listaIdProd.length()-1))->text().toInt() == producto.avail.front()){
                producto.avail.pop_front();
                if(!producto.avail.empty())
                    id->setText(QString::number(producto.avail.front()));
                else
                    id->setText(QString::number(ui->tableWidget_productos->rowCount()));
            }
            else{
                if(producto.avail.empty()){
                    id->setText(QString::number(ui->tableWidget_productos->rowCount()));
                }
                else{
                    id->setText(QString::number(producto.avail.front()));
                }
            }
        }else{
            if(!producto.avail.empty()){
                producto.avail.pop_front();
                if(!producto.avail.empty()){
                    producto.avail.sort();
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
    precio->setMaxLength(9);
    /* En el if anterior se verfica que todo este en orden el el avail list
     * y poder mostrar el id que corresponde en la tabla al crear o borrar un nuevo registro
     */
    connect(precio,SIGNAL(returnPressed()),this,SLOT(LineEdit_guardar_enter_Productos()));

    ui->tableWidget_productos->setCellWidget(ultima_fila,0,eliminar);
    ui->tableWidget_productos->setCellWidget(ultima_fila,1,id);
    ui->tableWidget_productos->setCellWidget(ultima_fila,2,nombre);
    ui->tableWidget_productos->setCellWidget(ultima_fila,3,IdCat);
    ui->tableWidget_productos->setCellWidget(ultima_fila,4,precio);

    /* asignamos los QLineEdit creados anterioremente a la tabla de productos*/

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

void MainWindow::on_actionNew_triggered()
{

}

void MainWindow::on_actionOpen_triggered()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(), tr("Text File (*.txt)"));
    cliente.path = path;

    on_pushButton_leer_clicked();

}

void MainWindow::on_actionGenerar_Factura_triggered()
{
    TDAFile headFact;
    headFact.open("Encabezado.txt",ios_base::out);
    TDAFile DetailFact;
    DetailFact.open("Detalle.txt",ios_base::out);
    srand (time(NULL));
    QString sGen="";
    QString sEncabezado[7]={"Lun","Mar","Mie","Jue","Vie","Sab","Dom"};
    QString sMeses[4]={"Ene","Feb","Mar","Abr"};
    int l=0;//indices de dias
    int cont=0;//contador de facturas
    sGen="";//generador de fechas
    QString idfact;//id de la factura
    QString idcli;//id de cliente
    int randcli;//generador de cliente random
    int cts=ui->tableWidget->rowCount()-1;//cantidad de clientes
    int prods=ui->tableWidget_productos->rowCount()-1;//cantidad de productos
    for(int j=0;j<4;j++){//meses
        for(int k=1;k<=30;k++){//dias de la semana
            if(l==7){//resetear indice de dias
                l=0;
            }
            for(int m=8;m<21;m++){//horas
                for(int n=0;n<60;n+=((rand()%15)+1)){//minutos
                    sGen.append(sMeses[j]);
                    if(k<10){
                        sGen.append("0");
                    }
                    sGen.append(QString::number(k));
                    sGen.append(sEncabezado[l]);
                    if(m<10){
                        sGen.append("0");
                    }
                    sGen.append(QString::number(m));
                    sGen.append(":");
                    if(n<10){
                        sGen.append("0");
                    }
                    sGen.append(QString::number(n));
                    cont++;
                    randcli=(rand()%cts)+1;
                    if(randcli<10){ // verificamos si id es solamente de 1 digito.
                        idcli="000  ";
                        idcli.replace(3,strlen((QString::number(randcli)).toStdString().c_str()),QString::number(randcli));
                    }else
                        if(randcli<100){ // verificamos si id es solamente de 2 digitos.
                            idcli="00   ";
                            idcli.replace(2,strlen((QString::number(randcli)).toStdString().c_str()),QString::number(randcli));
                        }else
                            if(randcli<1000){ // verificamos si id es solamente de 3 digitos.
                                idcli="0    ";
                                idcli.replace(1,strlen((QString::number(randcli)).toStdString().c_str()),QString::number(randcli));
                            }
                            else
                                if(randcli<10000){// verificamos si id es solamente de 4 digito.
                                    idcli="     ";
                                    idcli.replace(0,strlen((QString::number(randcli)).toStdString().c_str()),QString::number(randcli));
                                }
                    //generar ID de Factura
                    if(cont<10){ // verificamos si id es solamente de 1 digito.
                        idfact="0000  ";
                        idfact.replace(4,strlen((QString::number(cont)).toStdString().c_str()),QString::number(cont));
                    }else
                        if(cont<100){ // verificamos si id es solamente de 2 digitos.
                            idfact="000   ";
                            idfact.replace(3,strlen((QString::number(cont)).toStdString().c_str()),QString::number(cont));
                        }else
                            if(cont<1000){ // verificamos si id es solamente de 3 digitos.
                                idfact="00    ";
                                idfact.replace(2,strlen((QString::number(cont)).toStdString().c_str()),QString::number(cont));
                            }
                            else
                                if(cont<10000){// verificamos si id es solamente de 4 digito.
                                    idfact="0     ";
                                    idfact.replace(1,strlen((QString::number(cont)).toStdString().c_str()),QString::number(cont));
                                }
                                else
                                    if(cont<100000){// verificamos si id es solamente de 4 digito.
                                        idfact="      ";
                                        idfact.replace(0,strlen((QString::number(cont)).toStdString().c_str()),QString::number(cont));
                                    }
                    QString cabecera="                         ";
                    cabecera.replace(0,strlen(idfact.toStdString().c_str()),idfact);
                    cabecera.replace(6,strlen(sGen.toStdString().c_str()),sGen);
                    cabecera.replace(20,strlen(idcli.toStdString().c_str()),idcli);
                    headFact.write(cabecera.toStdString().c_str(),25);
                    idcli.clear();
                    cabecera.clear();

                    for(int h=0;h<((rand()%10)+1);h++){
                        int randprod=(rand()%prods)+1;
                        int cant=(rand()%5)+1;
                        QString sIdProd="";
                        if(randprod<10){ // verificamos si id es solamente de 1 digito.
                            sIdProd="000  ";
                            sIdProd.replace(3,strlen((QString::number(randprod)).toStdString().c_str()),QString::number(randprod));
                        }else
                            if(randprod<100){ // verificamos si id es solamente de 2 digitos.
                                sIdProd="00   ";
                                sIdProd.replace(2,strlen((QString::number(randprod)).toStdString().c_str()),QString::number(randprod));
                            }else
                                if(randprod<1000){ // verificamos si id es solamente de 3 digitos.
                                    sIdProd="0    ";
                                    sIdProd.replace(1,strlen((QString::number(randprod)).toStdString().c_str()),QString::number(randprod));
                                }
                                else
                                    if(randprod<10000){// verificamos si id es solamente de 4 digito.
                                        sIdProd="     ";
                                        sIdProd.replace(0,strlen((QString::number(randprod)).toStdString().c_str()),QString::number(randprod));
                                    }
                        QString sCant=QString::number(cant);
                        QString detalle;
                        detalle.append(idfact);
                        detalle.append(sIdProd);
                        detalle.append(sCant);
                        DetailFact.write(detalle.toStdString().c_str(),12);
                        detalle.clear();
                    }
                    sGen.clear();
                    idfact.clear();
                }//fin minutos
            }
            l++;
        }
    }
    headFact.close();
    DetailFact.close();

}

void MainWindow::on_lineEdit_buscarCliente_returnPressed()
{
    if(ui->tabWidget->currentIndex() == 0){ // inicio if de clientes
        int iDBuscar =atoi(ui->lineEdit_buscarCliente->text().toStdString().c_str()); // obtenemos el id a encontrar

        if(!indice.indices2.contains(iDBuscar)){
            QMessageBox::critical(this,"Error","Cliente no encontrado");

        }else{
            ui->tableWidget_buscarCliente->removeRow(0);
            ui->tableWidget_buscarCliente->insertRow(0);

            QPointer<QLineEdit>  id = new QLineEdit(this);
            QPointer<QLineEdit>  nombre = new QLineEdit(this);
            QPointer<QLineEdit>  correo = new QLineEdit(this);
            char buffer[84];
            cliente.readrecord(buffer,indice.indices2.value(iDBuscar));
            buffer[83] = '\0'; //asignacion del null manualmente
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

            id->setText(sId);
            id->setMaxLength(4);

            id->setEnabled(false);

            nombre->setMaxLength(39);
            nombre->setText(sNombre);

            correo->setMaxLength(39);
            correo->setText(sCorreo);

            ui->tableWidget_buscarCliente->setCellWidget(0,0,id);
            ui->tableWidget_buscarCliente->setCellWidget(0,1,nombre);
            ui->tableWidget_buscarCliente->setCellWidget(0,2,correo);
            /*asignamos los QLineEdit a la tabla de buscar cliente
             * si el cliente se encontro*/
        }
    }else if( ui->tabWidget->currentIndex() == 1){  // if de buscar categoria
        int iDBuscar =atoi(ui->lineEdit_buscarCliente->text().toStdString().c_str()); // obtenemos el id a buscar de categoria

        if(!indiceCat.indices2.contains(iDBuscar)){ // verificamos que exista el id
            QMessageBox::critical(this,"Error","Categoria no encontrado");

        }else{
            ui->tableWidget_buscarCategoria->removeRow(0);
            ui->tableWidget_buscarCategoria->insertRow(0);
            /* removemos la fila y a la vez insertamos por si habian datos de otra busqueda realizada*/
            QPointer<QLineEdit>  id = new QLineEdit(this);
            QPointer<QLineEdit>  nombre = new QLineEdit(this);
            char buffer[25];
            categoria.readrecord(buffer,indiceCat.indices2.value(iDBuscar));
            buffer[24] = '\0'; //asignacion del null manualmente


            QString sId;//length de 4
            QString sNombre;//length de 20
            for(int i = 0; i < 4; i++){ // for para obtener el id del registro leido
                sId += buffer[i]; // obtenemos el id
            }
            for(int i = 4; i < 25;i++){ // for para obtener el nombre del registro leido
                if(i != 24){
                    if(buffer[i] == ' ' && buffer[i+1] == ' ')
                        break;
                    else{
                        sNombre += buffer[i]; // obtenemos el nombre
                    }
                }
            }
            /* Por medio de los fors anteriores se obtenien los campos de cada registro
             * de modo que puedan ser agregados al QTableWidget sin ningun problema
             */

            id->setText(sId);
            id->setMaxLength(4);

            id->setEnabled(false);

            nombre->setMaxLength(39);
            nombre->setText(sNombre);

            ui->tableWidget_buscarCategoria->setCellWidget(0,0,id);
            ui->tableWidget_buscarCategoria->setCellWidget(0,1,nombre);
        }
    }else if(ui->tabWidget->currentIndex() == 2){ // IF PARA BUSCAR PRODUCTO
        int iDBuscar =atoi(ui->lineEdit_buscarCliente->text().toStdString().c_str());

        if(!indiceProd.indices2.contains(iDBuscar)){
            QMessageBox::critical(this,"Error","Producto no encontrado");

        }else{
            ui->tableWidget_buscarProducto->removeRow(0);
            ui->tableWidget_buscarProducto->insertRow(0);
            QPointer<QLineEdit>  id = new QLineEdit(this);
            QPointer<QLineEdit>  nombre = new QLineEdit(this);
            QPointer<QLineEdit>  IdCategoria = new QLineEdit(this);
            QPointer<QLineEdit>  precio = new QLineEdit(this);
            char buffer[37];
            producto.readrecord(buffer,indiceProd.indices2.value(iDBuscar)); // metodo para leer un registro de producto
            buffer[36] = '\0'; // asignacion del caracter null para saber que se ha llegado al final y no tener problema con caracteres basura(Q"#!"#$!)
            QString sId;//length de 4
            QString sNombre;//length de 19
            QString sCategoria;//length de 4
            QString sPrecio;//length de 9
            for(int i = 0; i < 4; i++){ // for para obtene id de producto
                sId += buffer[i]; // obtener id producto
            }
            for(int i = 4; i < 23;i++){ // for para obtener nombre del producto
                if(i != 23){
                    if(buffer[i] == ' ' && buffer[i+1] == ' ')
                        break;
                    else{
                        sNombre += buffer[i]; // obtener nombre del producto
                    }
                }
            }
            for(int i = 23; i < 27; i++){ // for para obtener id de categoria del producto
                if(i != 27){
                    if(buffer[i] == ' ' && buffer[i+1] == ' ')
                        break;
                    else{
                        sCategoria += buffer[i];// obtener id de categoria de producto
                    }
                }
            }
            for(int i = 27; i < 36; i++){ // for para obtener el precio del producto
                if(i != 36){
                    if(buffer[i] == ' ' && buffer[i+1] == ' ')
                        break;
                    else{
                        sPrecio += buffer[i]; // obtener precio de producto
                    }
                }
            }
            /* Por medio de los fors anteriores se obtenien los campos de cada registro
             * de modo que puedan ser agregados al QTableWidget sin ningun problema
             */

            id->setText(sId);
            id->setMaxLength(4);
            id->setEnabled(false);

            nombre->setMaxLength(19);
            nombre->setText(sNombre);

            IdCategoria->setMaxLength(4);
            IdCategoria->setText(sCategoria);\

            precio->setMaxLength(9);
            precio->setText(sPrecio);
            /*En las 13 lineas anteriores se crean las validaciones de los campos
             * segun lo requerido por el programa
             */

            ui->tableWidget_buscarProducto->setCellWidget(0,0,id);
            ui->tableWidget_buscarProducto->setCellWidget(0,1,nombre);
            ui->tableWidget_buscarProducto->setCellWidget(0,2,IdCategoria);
            ui->tableWidget_buscarProducto->setCellWidget(0,3,precio);

            /* En las 4 lineas anteriores se inserta los QLineEdit a la tabla de productos
                 * y cada QLineEdit con su validacion necesaria creada anterioremente
                 */

        }
    }

}


void MainWindow::on_comboBox_IdCliente_currentIndexChanged(const QString &arg1)
{
    char buffer[84];
    cliente.findrecord(buffer,atoi(arg1.toStdString().c_str()));
    buffer[83] = '\0'; //asignacion del null manualmente
    QString Nombre; // QString para obtener el nombre

    for(int i = 4; i < 44;i++){
        if(i != 43){
            if(buffer[i] == ' ' && buffer[i+1] == ' ')
                break;
            else
                Nombre += buffer[i];
        }
    }
    ui->label_nombre->setText(Nombre);
    header.path = "Encabezado.txt";
    int headerSize = header.recordsSize();
    int c = 0;
    char buffer2[26];
    QString sIdCliente;
    QString sDate;
    QString sIdFactura;
    ui->comboBox_IdFactura->clear();
    while(c < headerSize){ // while para realizar una busqueda secuencial en el encabezado de factura
        header.readrecord(buffer2,c);
        buffer2[25] = '\0';
        c+=25;

        for(int i = 21; i < 25; i++)
            sIdCliente += buffer2[i];

        if(atoi(sIdCliente.toStdString().c_str()) == atoi(arg1.toStdString().c_str())){
            for(int i =0;i < 19;i++){
                if(i >= 6){
                    sDate+= buffer2[i];
                }else{
                    sIdFactura+= buffer2[i];
                }
            }
            head.insert(head.size(),sDate);
            ui->comboBox_IdFactura->addItem(QString::number(atoi(sIdFactura.toStdString().c_str())));
        }
        sIdCliente.clear();
        sIdFactura.clear();
        sDate.clear();
    } // fin while
}

void MainWindow::on_comboBox_IdFactura_currentIndexChanged(int index)
{
    double acum=0;//para calcular el total de la factura
    if(ui->comboBox_metodoDeBusquedad->currentIndex()==0){ // inicio if si consulta de factura es secuencialmente
        ui->label_FechaFactura->clear();// limpiamos el label de factura
        ui->label_FechaFactura->setText(head.value(index)); // asignamos al fecha correspondiente
        detail.path = "Detalle.txt"; // asignamos el nomnbre del archivo detalle
        detail.recordsSize();
        int c = 0; // inicializamos el contador en 0 que a su vez funciona como offset
        int detailSize = detail.recordsSize(); // obtenemos el tamaño del archivo de detalle para recorrerlo secuencialemnte
        char buffer[13]; // creacion del buffer de 12 bytes ya que sabemos que cada registro de detalle es de tamaño fijo de 12 bytes
        QString sIdFactura;
        QString sIdProducto;
        QString sCantidad;
        bool f = false;
        for(int i = 0; i < ui->tableWidget_consulta->rowCount();i++){ // for para quitar todas las filas de QTableWidget y poder mostrar la factura nueva
            ui->tableWidget_consulta->removeRow(i);
            i = -1;
        }
        while(c < detailSize){ // inicio while para poder leer de manera secuencial los registros de detalle
            detail.readrecord(buffer,c); // metodo para leer los registros
            buffer[12] = '\0'; // asignacion del caracter null para despues no tener problemas con los caracteres basuras
            c+=12; // incrementaos contador en 12 para poder leer el siguiente registro
            for(int i = 0; i <13;i++){ // for para obtener el id factura
                if(i < 5)
                    sIdFactura += buffer[i];
                else{
                    if(i > 5 && i < 10){ // obtenemos el id del producto
                        sIdProducto += buffer[i];
                    }else{
                        if(i > 10 && i < 12)
                            sCantidad += buffer[i]; // obtenemos la cantidad comprada
                    }
                }

            }
            int idFactura = atoi(sIdFactura.toStdString().c_str()); // int de id factura del registro leido
            int idFacturaComboBox = atoi(ui->comboBox_IdFactura->currentText().toStdString().c_str()); // id factua del comboBox
            if( idFactura == idFacturaComboBox ){ // inicio if para verificar si es el id factura que andamos buscando

                f = true;
                const int ultima_fila =  ui->tableWidget_consulta->rowCount(); // obtenemos la ultima fila del QTableWidget para poder insertar otra fila nueva

                ui->tableWidget_consulta->insertRow(ultima_fila); // insertamos fila en la QTableWidget de consultas
                char buffer2[37]; // creacion de buffer de 36 para leer un registro de producto
                producto.findrecord(buffer2,atoi(sIdProducto.toStdString().c_str())); // mandamos a leer el registro junto con el offset obtenido a traves del id
                buffer2[36] = '\0';
                QString sNombre;//length de 19
                QString sPrecio;//length de 9
                for(int i = 4; i < 23;i++){ // for para obtener el nombre del producto y mostrarlo en la tabla
                    if(i != 23){
                        if(buffer2[i] == ' ' && buffer2[i+1] == ' ')
                            break;
                        else{
                            sNombre += buffer2[i]; // obtener nombre
                        }
                    }
                }

                for(int i = 27; i < 36; i++){ // inicio for para obtener el precio
                    if(i != 36){
                        if(buffer2[i] == ' ' && buffer2[i+1] == ' ')
                            break;
                        else{
                            sPrecio += buffer2[i]; // obtener precio
                        }
                    }
                }
                QPointer<QLineEdit>  producto = new QLineEdit(this);
                QPointer<QLineEdit>  precioUnidad = new QLineEdit(this);
                QPointer<QLineEdit>  cantidad = new QLineEdit(this);
                QPointer<QLineEdit>  precioTotal = new QLineEdit(this);
                /* En las 4 lineas anteriores creamos apuntadores de QLineEdit para poder mostrarlos
             * en la QTableWidget de consultas
             */

                producto->setText(sNombre);
                cantidad->setText(sCantidad);
                precioUnidad->setText(sPrecio);
                /*En las 3 lineas anteriores se asigna texto al QLineEdit para visualizarlo en la tabla
                 */

                ui->tableWidget_consulta->setCellWidget(ultima_fila,0,producto); // poner el nombre del producto en la tabla
                ui->tableWidget_consulta->setCellWidget(ultima_fila,1,cantidad); // poner cantidad del producto en la tabla
                double precio2 = sPrecio.toDouble(); // obtenemos el precio por unidad
                ui->tableWidget_consulta->setCellWidget(ultima_fila,2,precioUnidad); // precio por unidad
                double total = precio2 * atoi(sCantidad.toStdString().c_str()); // obtenemos el precio total de la fila
                acum+=total; // acumulamos el total de la factura
                precioTotal->setText(QString::number(total)); // poner el total en la fila
                ui->tableWidget_consulta->setCellWidget(ultima_fila,3,precioTotal); // precio total

            }
            if(f && atoi(sIdFactura.toStdString().c_str()) != atoi(ui->comboBox_IdFactura->currentText().toStdString().c_str() )){ // verificamos
                break; // para no tener que recorrer todo el archivo de detalle factura
            }
            sIdFactura.clear();
            sIdProducto.clear();
            sCantidad.clear();
            /* limpiamos las variables para poder seguir realizando una lectura
             * secuencial de los registros de detalle factura de una manera correcta
             */

        } // fin while de recorrer archivo
    }
    //Inicio IF ARBOL B
    if(ui->comboBox_metodoDeBusquedad->currentIndex()==1){
        ui->label_FechaFactura->clear(); // limpiamos la fecha del id
        ui->label_FechaFactura->setText(head.value(index)); //
        detail.path = "Detalle.txt";
        int c = 0;
        char buffer[13];
        QString sIdFactura=ui->comboBox_IdFactura->currentText();
        QString sIdProducto;
        QString sCantidad;
        for(int i = 0; i < ui->tableWidget_consulta->rowCount();i++){
            ui->tableWidget_consulta->removeRow(i);
            i = -1;
        }

        //Buscar la factura en en arbol B
        ArbolBNodo* tempNodo=arbolito->buscar(atoi(ui->comboBox_IdFactura->currentText().toStdString().c_str()));
        if(tempNodo!='\0'){
            c=((ArbolBNodo::llave*)((tempNodo)->llaves))->pos;
        }
        //c=indicedetalle.value(atoi(ui->comboBox_IdFactura->currentText().toStdString().c_str()));

        while(atoi(sIdFactura.toStdString().c_str())==atoi(ui->comboBox_IdFactura->currentText().toStdString().c_str())){
            sIdFactura.clear();
            detail.readrecord(buffer,c);
            buffer[12] = '\0';
            c+=12;
            for(int i = 0; i <13;i++){
                if(i < 5)
                    sIdFactura += buffer[i];
                else{
                    if(i > 5 && i < 10){
                        sIdProducto += buffer[i];
                    }else{
                        if(i > 10 && i < 12)
                            sCantidad += buffer[i];
                    }
                }
            }
            if(atoi(sIdFactura.toStdString().c_str())!=atoi(ui->comboBox_IdFactura->currentText().toStdString().c_str())){
                break;
            }
            const int ultima_fila =  ui->tableWidget_consulta->rowCount();
            ui->tableWidget_consulta->insertRow(ultima_fila);
            char buffer2[37];
            producto.findrecord(buffer2,atoi(sIdProducto.toStdString().c_str())); // realizamos lectura del registro de producto
            buffer2[36] = '\0';
            QString sNombre;//length de 19
            QString sPrecio;//length de 9
            for(int i = 4; i < 23;i++){
                if(i != 23){
                    if(buffer2[i] == ' ' && buffer2[i+1] == ' ')
                        break;
                    else{
                        sNombre += buffer2[i];
                    }
                }
            }

            for(int i = 27; i < 36; i++){
                if(i != 36){
                    if(buffer2[i] == ' ' && buffer2[i+1] == ' ')
                        break;
                    else{
                        sPrecio += buffer2[i];
                    }
                }
            }
            /* en los fors anteriores obtenemos los campos de la lectura del registro*/
            QPointer<QLineEdit>  producto = new QLineEdit(this);
            QPointer<QLineEdit>  precioUnidad = new QLineEdit(this);
            QPointer<QLineEdit>  cantidad = new QLineEdit(this);
            QPointer<QLineEdit>  precioTotal = new QLineEdit(this);
            /* En las 4 lineas anteriores creamos QLineEdit para asignaralos a la tabla
             * y llevar un mejor control con las validaciones*/

            producto->setText(sNombre);
            cantidad->setText(sCantidad);
            precioUnidad->setText(sPrecio);
            ui->tableWidget_consulta->setCellWidget(ultima_fila,0,producto); // producto
            ui->tableWidget_consulta->setCellWidget(ultima_fila,1,cantidad); // catidad
            double precio2 = sPrecio.toDouble();
            ui->tableWidget_consulta->setCellWidget(ultima_fila,2,precioUnidad); // precio por unidad
            double total = precio2 * atoi(sCantidad.toStdString().c_str());
            precioTotal->setText(QString::number(total));
            acum+=total;
            ui->tableWidget_consulta->setCellWidget(ultima_fila,3,precioTotal); // precio total

            /*en las lineas anteriores asignamos textos a los QLineEdit para
             * poder mostrarlos luegos en la tabla*/
            sIdProducto.clear();
            sCantidad.clear();

        } // fin while de recorrer archivo
    }
    //Inicio IF INDICE de DETALLE
    if(ui->comboBox_metodoDeBusquedad->currentIndex()==2){
        ui->label_FechaFactura->clear(); // limpiamos la variable de fecha
        ui->label_FechaFactura->setText(head.value(index));
        detail.path = "Detalle.txt";
        int c = 0;
        char buffer[13];
        QString sIdFactura=ui->comboBox_IdFactura->currentText();
        QString sIdProducto;
        QString sCantidad;

        for(int i = 0; i < ui->tableWidget_consulta->rowCount();i++){
            ui->tableWidget_consulta->removeRow(i);
            i = -1;
        }
        c=indicedetalle.value(atoi(ui->comboBox_IdFactura->currentText().toStdString().c_str())); // obtenemos el offset del registro a buscar

        while(atoi(sIdFactura.toStdString().c_str())==atoi(ui->comboBox_IdFactura->currentText().toStdString().c_str())){
            sIdFactura.clear();
            detail.readrecord(buffer,c);
            buffer[12] = '\0';
            c+=12;
            for(int i = 0; i <13;i++){
                if(i < 5)
                    sIdFactura += buffer[i];
                else{
                    if(i > 5 && i < 10){
                        sIdProducto += buffer[i];
                    }else{
                        if(i > 10 && i < 12)
                            sCantidad += buffer[i];
                    }
                }
            }
            /* en el for anterior obtenemos los campos del la lectura del registro realizado*/
            if(atoi(sIdFactura.toStdString().c_str())!=atoi(ui->comboBox_IdFactura->currentText().toStdString().c_str())){
                break; // verificamos que despues de encontrar un id distinto al buscado deje de realizar busqueda
            }

            const int ultima_fila =  ui->tableWidget_consulta->rowCount();
            ui->tableWidget_consulta->insertRow(ultima_fila);
            char buffer2[37];
            producto.findrecord(buffer2,atoi(sIdProducto.toStdString().c_str())); // hacemos lectura del producto
            buffer2[36] = '\0';
            QString sNombre;//length de 19
            QString sPrecio;//length de 9
            for(int i = 4; i < 23;i++){
                if(i != 23){
                    if(buffer2[i] == ' ' && buffer2[i+1] == ' ')
                        break;
                    else{
                        sNombre += buffer2[i];
                    }
                }
            }

            for(int i = 27; i < 36; i++){
                if(i != 36){
                    if(buffer2[i] == ' ' && buffer2[i+1] == ' ')
                        break;
                    else{
                        sPrecio += buffer2[i];
                    }
                }
            }
            /*En los fors anteriores obtenemos los campos del registro deseado*/
            QPointer<QLineEdit>  producto = new QLineEdit(this);
            QPointer<QLineEdit>  precioUnidad = new QLineEdit(this);
            QPointer<QLineEdit>  cantidad = new QLineEdit(this);
            QPointer<QLineEdit>  precioTotal = new QLineEdit(this);

            /* En las 4 lineas anteriore realizamos creacion de QLineEdit para poder
                 * tener mejor contorl de las validaciones*/

            producto->setText(sNombre);
            cantidad->setText(sCantidad);
            precioUnidad->setText(sPrecio);
            ui->tableWidget_consulta->setCellWidget(ultima_fila,0,producto); // producto
            ui->tableWidget_consulta->setCellWidget(ultima_fila,1,cantidad); // catidad
            double precio2 = sPrecio.toDouble();
            ui->tableWidget_consulta->setCellWidget(ultima_fila,2,precioUnidad); // precio por unidad
            double total = precio2 * atoi(sCantidad.toStdString().c_str());
            precioTotal->setText(QString::number(total));
            acum+=total;
            ui->tableWidget_consulta->setCellWidget(ultima_fila,3,precioTotal); // precio total
            sIdProducto.clear();
            sCantidad.clear();
            /* en las lineas anteriores realizamos calculo del total de las facturas e
             * ingresamos los datos a la tabla de consultas*/
        } // fin while de recorrer archivo
    }
    ui->lineEdit_totalFactura->setText(QString::number(acum));

}


void MainWindow::on_comboBox_metodoDeBusquedad_currentIndexChanged(int index)
{
    if(index==1){
        //arbolito =new ArbolB(15);
        if(arbolito->getRaiz()=='\0'){
            ui->statusBar->showMessage("Creando Arbol B....",2000);
            //cargar a arbol factura
            QString sIdFactura,sIdProducto,sCantidad;
            int c=0;
            int detailSize = detail.recordsSize();
            char buffer[13];
            while(c < detailSize){ // while para leer secuencialmente los datos de factura y cargarlos al arbol b
                detail.readrecord(buffer,c);
                buffer[12] = '\0';

                for(int i = 0; i <5;i++){

                    sIdFactura += buffer[i];


                }
                arbolito->insertar(atoi(sIdFactura.toStdString().c_str()),c); // insertar en el arbol b
                c+=12;
                /* limpiamos variables para poder seguir realizando la lectura secuencial */
                sIdFactura.clear();
                sIdProducto.clear();
                sCantidad.clear();

            } // fin while de recorrer archivo
            arbolito->recorrer();
            ui->statusBar->showMessage("Arbol B creado..",2000);

        }

    }else if(index==2){ // inicio if si metodo fue seleccionado de forma
        if(indicedetalle.size()==0){ // if para verificar que solamente se genere en memoria una vez el archivo de indice
            //cargar a indice factura

            ui->statusBar->showMessage("Creando indice de factura....",2000);
            QString sIdFactura,sIdProducto,sCantidad; // variables para poder crear indice de una manera correcta
            int c=0; // inicializamos contador en 0
            int detailSize = detail.recordsSize(); // obtenemos el tamaño del archivo de detalle de factura
            char buffer[13]; // creacion de buffer para leer un registro de detalle factura

            while(c < detailSize){ // while de lectura de registros de factura
                detail.readrecord(buffer,c); // metodo para leer un registro de factura
                buffer[12] = '\0'; // asignacion de caracter null para no tener problemas con los caracteres basuras

                for(int i = 0; i <5;i++){ // inicio for para obtener id factura
                    sIdFactura += buffer[i];  // obtener id factura
                }

                if(!indicedetalle.contains(atoi(sIdFactura.toStdString().c_str()))){ // verificar si existe id de factura
                    indicedetalle.insert(atoi(sIdFactura.toStdString().c_str()),c); // agregar id factura a la lista para realizar las consultas
                }
                c+=12; // incrementar contador en 12 ya que cada registro de factura es tamaño fijo
                sIdFactura.clear();
                sIdProducto.clear();
                sCantidad.clear();
                // en las 3 lineas anteriores se limpian las variables para poder realizar una busquedad sin problemas

            } // fin while de recorrer archivo

            ui->statusBar->showMessage("Indice de factura creado...",2000);
        }
    }
}

void MainWindow::on_actionClose_triggered()
{

    this->close(); // cerramos el programa
}

void MainWindow::on_actionDelete_Record_triggered()
{

    if(ui->tabWidget->currentIndex() == 0){ // if clientes
        for (int i = 0;i < ui->tableWidget->rowCount(); i++){
            if(listaEliminar.at(i)->isChecked()){
                cliente.eraserecord(atoi(((QLineEdit*)listaId.at(i))->text().toStdString().c_str()));
                indice.eraserecord(atoi(((QLineEdit*)listaId.at(i))->text().toStdString().c_str()));


                /*En la linea anterior llamos al metodo de eraseRecord por medio del cual asignamos un
                 * asterisco al inicio de cada registro para saber que le hemos eliminado a la hora de
                 * realizar la lectura
                 */

                ui->tableWidget->removeRow(i); // eliminamos la fila del registro que ha sido seleccionado.
               // indice.indices2.remove(atoi(((QLineEdit*)listaId.at(i))->text().toStdString().c_str()));
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
                indiceCat.eraserecord(atoi(((QLineEdit*)listaIdCate.at(i))->text().toStdString().c_str()));
                ui->tableWidget_categorias->removeRow(i);

                // eliminamos memoria dinamica
                delete listaEliminarCate.at(i);
                delete listaIdCate.at(i);
                //delete listaNombreCate.at(i);

                // quitamos el puntero de la lista
                listaEliminarCate.removeAt(i);
                listaIdCate.removeAt(i);
                //listaNombreCate.removeAt(i);
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
                indiceProd.eraserecord(atoi(((QLineEdit*)listaIdProd.at(i))->text().toStdString().c_str()));
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

void MainWindow::on_pushButton_prodvendido_clicked()
{
    ui->statusBar->showMessage("Realizando consulta de Producto mas vendido....",2000);

    int prods[ui->tableWidget_productos->rowCount()];
    for(int i=0;i<ui->tableWidget_productos->rowCount();i++){
        prods[i]=0;
    }
    detail.path = "Detalle.txt"; // asignamos el nomnbre del archivo detalle
    detail.recordsSize();
    int c = 0; // inicializamos el contador en 0 que a su vez funciona como offset
    int detailSize = detail.recordsSize(); // obtenemos el tamaño del archivo de detalle para recorrerlo secuencialemnte
    char buffer[13]; // creacion del buffer de 12 bytes ya que sabemos que cada registro de detalle es de tamaño fijo de 12 bytes
    QString sIdFactura;
    QString sIdProducto;
    QString sCantidad;
    while(c < detailSize){ // inicio while para poder leer de manera secuencial los registros de detalle
        detail.readrecord(buffer,c); // metodo para leer los registros
        buffer[12] = '\0'; // asignacion del caracter null para despues no tener problemas con los caracteres basuras
        c+=12; // incrementaos contador en 12 para poder leer el siguiente registro
        for(int i = 0; i <13;i++){ // for para obtener el id factura
            if(i < 5)
                sIdFactura += buffer[i];
            else{
                if(i > 5 && i < 10){ // obtenemos el id del producto
                    sIdProducto += buffer[i];
                }else{
                    if(i > 10 && i < 12)
                        sCantidad += buffer[i]; // obtenemos la cantidad comprada
                }
            }

        }
        //Incrementamos en la posicion correspondiente
        prods[atoi(sIdProducto.toStdString().c_str())]+=atoi(sCantidad.toStdString().c_str());
        sIdFactura.clear();
        sIdProducto.clear();
        sCantidad.clear();
        /* limpiamos las variables para poder seguir realizando una lectura
         * secuencial de los registros de detalle factura de una manera correcta
         */
    } // fin while de recorrer archivo
    //Encontrar el mayor
    int mayor=prods[0];
    int indiceproducto=0;
    for(int i=1;i<ui->tableWidget_productos->rowCount();i++){
        if(prods[i]>mayor){
            mayor=prods[i];
            indiceproducto=i;
        }
    }
    char buffer2[37];
    producto.findrecord(buffer2,indiceproducto);
    buffer2[36]='\0';
    QString sNombre;
    for(int i = 4; i < 23;i++){ // for para obtener nombre del producto
        if(i != 23){
            if(buffer2[i] == ' ' && buffer2[i+1] == ' ')
                break;
            else{
                sNombre += buffer2[i]; // obtener nombre del producto
            }
        }
    }
    ui->statusBar->showMessage("Consulta realizada..",2000);

    QMessageBox::information(this,"El producto más vendido es",sNombre);
}

void MainWindow::on_tabWidget_currentChanged(int index)
{
    if(index == 3){ // si nos encontramos en la pestaña de consulta deshabilitamos el LineEdit busqueda
        ui->lineEdit_buscarCliente->clear(); // limpiamos
        ui->lineEdit_buscarCliente->setDisabled(true); // deshabilitamos
    }else
        ui->lineEdit_buscarCliente->setDisabled(false);
}
