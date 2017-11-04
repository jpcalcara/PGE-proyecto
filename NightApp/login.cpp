#include "login.h"
#include "ui_login.h"
#include "admindb.h"
#include <QDebug>

Login::Login(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    im_fondo.load(":/root/Recursos/images/startsiluetaDK.jpg");

    if(im_fondo.isNull())
    {
         qDebug()<<"Esta vacia";
    }

    //ui->pbNoVerPass->hide();

    this->setFixedSize(348,490);

    ui->le_pass->setEchoMode(QLineEdit::Password);

    connect(ui->pb_initSesion,SIGNAL(pressed()),this,SLOT(slot_validar()));
    connect(ui->pb_guest,SIGNAL(pressed()),this,SLOT(slot_Invitado()));
    connect(ui->pb_register,SIGNAL(pressed()),this,SLOT(slot_Formulario()));
    //connect(ui->pbNoVerPass,SIGNAL(clicked(bool)),this,SLOT(slot_noverPass(bool)));
    //connect(ui->pbVerPass,SIGNAL(clicked(bool)),this,SLOT(slot_verPass(bool)));
    //connect(ui->pbInfo,SIGNAL(clicked()),this,SLOT(slot_infoAutores()));

    usuario =new Usuario();
    jarray=new QJsonArray();
    jdoc=new QJsonDocument();

    manager = new QNetworkAccessManager;
   // connect(manager, SIGNAL(finished(QNetworkReply *)), this, SLOT(slot_procesarRespuesta(QNetworkReply *)));
}

Login::~Login()
{
    delete ui;
}

Usuario Login::getUsuario()
{
    return *usuario;
}

void Login::slot_validar(){

    AdminDB *BaseDato = new AdminDB;
    this->setWindowTitle("NIGHTAPP");
    QVector <QStringList> resultados;
    bool usuarioValido=false;
    bool conecta = BaseDato->conectar(":/root/Recursos/database/usuarios.sqlite");

    if(!conecta){
        qDebug()<<"No se pudo ingresar a la base de datos";
    }

    if( BaseDato->getDb().isOpen() ) {

        if(ui->le_user->text().isEmpty()==false)
        {
            resultados = BaseDato->select("select usuario, clave FROM usuario WHERE usuario = '" +
                                             ui->le_user->text() + "' AND clave = '"+
                                             ui->le_pass->text() + "'");
        }

        if(!resultados.isEmpty())
        {
            usuarioValido=true;
        }


        if (usuarioValido == true)
        {
             this->close();
             qDebug()<<"ha iniciado sesion correctamente";

             /*Ventana *ven = new Ventana;
             ven->show();*/

             emit signal_ShowVentana(true);
        }

        else{
            QMessageBox::information(this,"ERROR", "Usuario o contraseña incorrectos");
            ui->le_user->clear();
            ui->le_pass->clear();
        }
    }
}

//Metodos para enviar datos y recibir de la base de datos

/*void Login::slot_validarUsuario(){

    manager->get(QNetworkRequest(QUrl("https://juan-pablo7.000webhostapp.com/1.php?key=abcd1234&tabla=usuarios")));
}
*/

/*void Login::slot_procesarRespuesta(QNetworkReply *reply){

    QString strReply = (QString)reply->readAll();

    QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());

    qDebug() << jsonResponse.isArray();

    QJsonArray arrayGeneral = jsonResponse.array();

    for (int i=0 ; i<arrayGeneral.size() ; i++ )
    {

       // qDebug()<<"recorro el QJsonArray";

        QJsonValue value = arrayGeneral.at(i);

        QJsonObject object = value.toObject();

        qDebug() << "La variables o keys son: " << object.keys();

        qDebug() << "El id es : " << object.value("id").toString();
        qDebug() << "Nombre: " << object.value("name").toString();
        qDebug() << "Apellido : " << object.value("surname").toString();
        qDebug() << "Telefono: " << object.value("telephone").toString();
        qDebug() << "E-Mail: " << object.value("mail").toString();
        qDebug() << "Usuario: " << object.value("user").toString();
        qDebug() << "Password: " << object.value("pass").toString();

        QString user=ui->le_user->text();
        QString pass=ui->le_pass->text();

        if(object.value("user").toString()==user&&object.value("pass")==pass)
        {

            qDebug()<<"SE ENCONTRO COINCIDENCIA";

            usuario->setId(object.value("id").toString().toInt());
            usuario->setName(object.value("name").toString());
            usuario->setSurname(object.value("surname").toString());
            usuario->setTelephone(object.value("telephone").toString());
            usuario->setMail(object.value("mail").toString());
            usuario->setUser(object.value("user").toString());
            usuario->setPass(object.value("pass").toString());

            //user->setConfig(object.value("config").toString());

            qDebug()<<"DENTRO DE LOGIN LOS DATOS DEL USUARIO CORRECTO SON:";

            qDebug()<<"id guardado:"<<user->getId();
            qDebug()<<"nombre guardado:"<<user->getName();
            qDebug()<<"apellido guardado:"<<user->getSurname();
            qDebug()<<"Telefono guardado:"<<user->getTelephone();
            qDebug()<<"Mail guardado:"<<user->getMail();

            emit select(99);
            emit usuarioCorrecto(user);
        }
    }
}
*/
void Login::slot_Formulario(){

    this->close();

    emit signal_ShowFormulario(true);
}

void Login::slot_Invitado(){

    this->close();

    emit signal_ShowVentana(true);
}

void Login::slot_verPass(bool a){

    if(a==false){

      ui->le_pass->setEchoMode(QLineEdit::Normal);
    }
}

void Login::slot_noverPass(bool a){

    if(a==false){

        ui->le_pass->setEchoMode(QLineEdit::Password);
    }
}

void Login::slot_infoAutores(){

    QMessageBox::information(this,"NIGHTAPP", "Desarrollado por -NICOLAS HEINZ--J.PABLO CALCARA-");
}

void Login::paintEvent(QPaintEvent *){

    QPainter painter(this);

    QImage imLogin = im_fondo.scaled(this->height(),this->width()*2);

    painter.drawImage(0,0,imLogin);
}

