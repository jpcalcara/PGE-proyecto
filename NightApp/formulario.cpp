#include "formulario.h"
#include "ui_formulario.h"

Formulario::Formulario(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Formulario)
{
    ui->setupUi(this);

    im_fondoform.load(":/root/Recursos/images/startsiluetaDK.jpg");

    if(im_fondoform.isNull())
    {
         qDebug()<<"Esta vacia";
    }

    this->setFixedSize(348,490);

    this->setWindowTitle("NIGHTAPP");
    admin = new AdminDB();


    ui->le_pass->setEchoMode(QLineEdit::Password);

    connect(ui->pb_back,SIGNAL(pressed()),this,SLOT(slot_backlogin()));
    connect(ui->pb_register,SIGNAL(clicked()),this,SLOT(slot_register()));

}

Formulario::~Formulario()
{
    delete ui;
}

void Formulario::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0,0,im_fondoform);
}

void Formulario::slot_backlogin(){
    this->close();

    emit signal_ShowLogin(true);
}

void Formulario::slot_register()
{
   admin->conectar(":/root/Recursos/database/usuarios.sqlite");
   if(!ui->le_user->text().isEmpty() && !ui->le_mail->text().isEmpty() && !ui->le_pass->text().isEmpty())
   {
       admin->insertLog(ui->le_user->text(), ui->le_pass->text(), ui->le_name->text(), ui->le_surname->text(), ui->le_telephone->text(),ui->le_mail->text());

       QMessageBox::information(this,"NIGHTAPP", "Registro Completo!");

       this->close();

       emit signal_ShowLogin(true);
   }

   else
   {
     QMessageBox::information(this,"NIGHTAPP", "Algunos de los campos esta incompletos!!");

   }
}

void Formulario::slot_verPass(bool a){

    if(a==false){

      ui->le_pass->setEchoMode(QLineEdit::Normal);

    }
}

void Formulario::slot_noverPass(bool a){

    if(a==false){

        ui->le_pass->setEchoMode(QLineEdit::Password);

    }
}

