#include "start.h"
#include "ui_start.h"

Start::Start(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Start)
{
    ui->setupUi(this);

    im_fondoStart.load(":/root/Recursos/images/startsiluetablue.jpg");

    if(im_fondoStart.isNull())
    {
      qDebug()<<"Esta vacia";
    }

    this->setFixedSize(348,490);

    counter = 0;

    timer = new QTimer(this);

    connect(timer,SIGNAL(timeout()),this,SLOT(slot_updateProgressBar()));

    timer->start(10);

    this->setMaximumSize(this->height(), this->width());
}

Start::~Start()
{
    delete ui;
}

void Start::paintEvent(QPaintEvent *){

    QPainter painter(this);
    QImage imStart = im_fondoStart.scaled(this->width(),this->height());
    painter.drawImage(0,0,imStart);

}

void Start::slot_updateProgressBar(){

    if(counter <= 100){
        counter++;
        ui->pbar->setValue(counter);
    }
    else{
        if(counter >= 100){
            this->close();

            timer->stop();

            emit signal_ready(true);
        }

    }
}
