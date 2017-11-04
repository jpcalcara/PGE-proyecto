#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QStringList>
#include <QDebug>
#include <QVector>

#include "login.h"
#include "ventana.h"
#include "formulario.h"
#include "start.h"

class Manager : public QObject
{
    Q_OBJECT

public:
    void Iniciar();
    static Manager *getInstancia();
    ~Manager();

private slots:
    void slot_ShowLogin(bool estado);
    void slot_ShowFormulario(bool estado);
    void slot_ShowVentana(bool estado);

private:
    Login *login;
    Ventana *ventana;
    Formulario *formulario;
    Start *start;
    static Manager *instancia;

    //Se lo pone como privado al constructor para que nadie pueda acceder
    explicit Manager(QObject *parent = 0);

};

#endif // MANAGER_H
