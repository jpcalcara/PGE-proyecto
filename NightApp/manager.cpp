#include "manager.h"

Manager* Manager::instancia = NULL;

Manager::Manager(QObject *parent) : QObject(parent),login(new Login), ventana(new Ventana) , formulario(new Formulario)
  , start(new Start)
{

    connect(start,SIGNAL(signal_ready(bool)),this,SLOT(slot_ShowLogin(bool)));

    connect(login,SIGNAL(signal_ShowFormulario(bool)),this,SLOT(slot_ShowFormulario(bool)));

    connect(login,SIGNAL(signal_ShowVentana(bool)),this,SLOT(slot_ShowVentana(bool)));

    connect(formulario,SIGNAL(signal_ShowLogin(bool)),this,SLOT(slot_ShowLogin(bool)));

    connect(ventana,SIGNAL(signal_ShowLogin(bool)),this,SLOT(slot_ShowLogin(bool)));

}

void Manager::Iniciar()
{
    start->show();
}

Manager *Manager::getInstancia()
{


    if(instancia == NULL )
    {
        instancia = new Manager();
    }

    return instancia;
}

Manager::~Manager()
{
    if(instancia != NULL )
    {
        delete instancia;
    }
}


void Manager::slot_ShowLogin(bool estado)
{
    if(estado)
    {
        login->show();
    }
}

void Manager::slot_ShowFormulario(bool estado)
{

    if(estado)
    {
        formulario->show();
    }
}

void Manager::slot_ShowVentana(bool estado)
{
    if(estado)
    {
        ventana->show();
    }
}

