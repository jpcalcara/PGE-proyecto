#include "ventana.h"
#include "ui_ventana.h"


Ventana::Ventana(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ventana)
{
    ui->setupUi(this);

    this->setFixedSize(348,490);

    im_fondoven.load(":/root/Recursos/images/startsiluetablue.jpg");

    if(im_fondoven.isNull()){
        qDebug()<<"Esta vacia";
    }

    map = new Mapa(this);
    loc = new Localizacion(this);
    sites = new Sites;
    siteroute = new SitesRoute;
    infolugar = new InfoLugar;
    BNombre = new BusquedaNombre;



    ui->spinBox->hide();
    ui->spinBox->setRange(10,20);
    ui->spinBox_2->hide();
    ui->spinBox_2->setRange(10,20);

    ui->lw_listcharac->hide();

    ui->stackedWidget->show();
    ui->sw_page1->setEnabled(true);
    ui->sw_page2->setEnabled(true);

    ui->lw_listplaces->hide();

    ui->map1->hide();
    ui->map2->hide();
    ui->datos_Lugar->hide();


    lista = new QStringList;

    ui->le_search->setDiccionario("palabras");


    connect(loc,SIGNAL(signal_domicilioObtenido(QString)),this,SLOT(slot_ObtieneDom(QString)));
    connect(BNombre,SIGNAL(signal_listadoBusqueda(QStringList,QStringList,QStringList)),this,SLOT(slot_recivBusqueda(QStringList,QStringList,QStringList)));
    connect(sites,SIGNAL(signal_listadoLugares(QStringList,QStringList,QStringList)),this,SLOT(slot_recivListado(QStringList,QStringList,QStringList)));
    connect(siteroute,SIGNAL(signal_listadoRuta(QStringList)),this,SLOT(slot_recivRuta(QStringList)));
    connect(infolugar,SIGNAL(signal_listadoInfo(QStringList)),this,SLOT(slot_ListadoInfo(QStringList)));
    connect(ui->pb_update,SIGNAL(pressed()),this,SLOT(slot_ActualizaPos()));
    connect(ui->pb_search,SIGNAL(pressed()),this,SLOT(slot_Busca()));
    connect(ui->pb_back,SIGNAL(pressed()),this,SLOT(slot_backStart()));
    connect(ui->spinBox,SIGNAL(valueChanged(QString)),this,SLOT(slot_ActualizaMapaSpinBox(QString)));
    connect(ui->spinBox_2,SIGNAL(valueChanged(QString)),this,SLOT(slot_ActualizaPosMapRuta(QString)));
    connect(ui->cb_categories,SIGNAL(activated(int)),this,SLOT(slot_comboBox(int)));
    connect(ui->lw_listplaces,SIGNAL(activated(QModelIndex)),this,SLOT(slot_ActivaListado(QModelIndex)));



}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0,0,im_fondoven);
}

void Ventana::slot_comboBox(int i)
{
    ui->lw_listcharac->hide();
    tipo=i;
}

void Ventana::slot_ActualizaPos()
{
    ui->spinBox_2->hide();

    ui->spinBox->show();

    ui->lw_listcharac->hide();

    ui->le_search->clear();

    if(tipo == 1)
    {
        sites->getSites("-31.4197583","-64.1890037","bar");

        ui->lw_listplaces->setVisible(true);
    }
    if(tipo == 2)
    {
        sites->getSites("-31.4197583","-64.1890037","night_club");

        ui->lw_listplaces->setVisible(true);
    }
    if(tipo == 3)
    {
        sites->getSites("-31.4197583","-64.1890037","restaurant");

        ui->lw_listplaces->setVisible(true);
    }
    if(tipo == 4)
    {
        sites->getSites("-31.4197583","-64.1890037","casino");

        ui->lw_listplaces->setVisible(true);
    }
    if(tipo == 5)
    {
        sites->getSites("-31.4197583","-64.1890037","museum");

        ui->lw_listplaces->setVisible(true);
    }

    if(tipo == 6)
    {
        sites->getSites("-31.4197583","-64.1890037","movie_theater");

        ui->lw_listplaces->setVisible(true);
    }




}

void Ventana::slot_ListadoInfo(QStringList list)
{ 
    //qDebug()<<loc->getLatLongGPS().at(0);
    //qDebug()<<loc->getLatLongGPS().at(1);
   // map->getRuta(loc->getLatLongGPS().at(0),loc->getLatLongGPS().at(1),list.at(6),list.at(7));
    //siteroute->getRuta("-31.4235503","-64.186766",list.at(6),list.at(7));

    ui->map1->hide();
    ui->map2->show();

    siteroute->getRuta("-31.4197583","-64.1890037",list.at(6),list.at(7));

    ui->lw_listcharac->clear();

    list.removeAt(6);
    list.removeAt(6);

    ui->datos_Lugar->show();
    ui->lw_listcharac->addItems(list);
    ui->lw_listcharac->show();



}

void Ventana::slot_Busca()
{
    if(tipo == 1)
    {
        ui->lw_listcharac->hide();

        BNombre->getBusquedaNombre("-31.4197583","-64.1890037","bar",ui->le_search->text());
    }
    if(tipo == 2)
    {
        ui->lw_listcharac->hide();

        BNombre->getBusquedaNombre("-31.4197583","-64.1890037","night_club",ui->le_search->text());
    }
    if(tipo == 3)
    {
        ui->lw_listcharac->hide();

        BNombre->getBusquedaNombre("-31.4197583","-64.1890037","restaurant",ui->le_search->text());
    }
    if(tipo == 4)
    {
        ui->lw_listcharac->hide();

        BNombre->getBusquedaNombre("-31.4197583","-64.1890037","casino",ui->le_search->text());
    }
    if(tipo == 5)
    {
        ui->lw_listcharac->hide();

        BNombre->getBusquedaNombre("-31.4197583","-64.1890037","museum",ui->le_search->text());
    }

    if(tipo == 6)
    {
        ui->lw_listcharac->hide();

        BNombre->getBusquedaNombre("-31.4197583","-64.1890037","movie_theater",ui->le_search->text());
    }

}

void Ventana::slot_recivBusqueda(QStringList listNombre, QStringList listLocalizacion, QStringList listPlaceId)
{
    ui->lw_listplaces->clear();
    ui->lw_listplaces->addItems(listNombre);

    listRecibidaLatLon=listLocalizacion;
    listPlaceIdLugares=listPlaceId;

}

void Ventana::slot_ActualizaMapaSpinBox(QString i)
{
    ui->sw_page2->hide();
    ui->sw_page1->show();
    ui->map1->show();

    loc->pedirDomicilio(-31.4235503,-64.186766);

    ui->map1->getMapa("-31.4197583","-64.1890037",i,listRecibidaLatLon);
}

void Ventana::slot_recivRuta(QStringList list)
{
    QString Distancia;

    ui->spinBox->hide();
    ui->spinBox_2->show();

    listRecibidaLatLon.clear();

    ui->le_dTime->clear();

    Distancia=list.at(0);
    Distancia+=" - ";
    Distancia+=list.at(1);

    ui->le_dTime->setText(Distancia);

    list.removeAt(0);
    list.removeAt(0);

    listRecibidaLatLon = list;

    ui->sw_page1->hide();
    ui->sw_page2->show();

    ui->map2->show();

    ui->map2->getMapaRuta(list,"10");

}

void Ventana::slot_ActivaListado(QModelIndex index)
{
    infolugar->getInfoLugar(listPlaceIdLugares.at(index.row()));

}

void Ventana::slot_recivListado(QStringList listNombre, QStringList listLocalizacion, QStringList listPlaceId)
{

   ui->lw_listplaces->clear();
   ui->lw_listplaces->addItems(listNombre);

   listRecibidaLatLon=listLocalizacion;
   listPlaceIdLugares=listPlaceId;

   ui->sw_page2->hide();
   ui->sw_page1->show();

   ui->map1->show();

   ui->map1->getMapa("-31.4197583","-64.1890037","10",listLocalizacion);


}

void Ventana::slot_backStart()
{

    this->close();

    emit signal_ShowLogin(true);
}

void Ventana::slot_ObtieneDom(QString dom)
{
    //qDebug()<<dom;
}

void Ventana::slot_ActualizaPosMapRuta(QString num)
{
    ui->map2->getMapaRuta(listRecibidaLatLon,num);

}
