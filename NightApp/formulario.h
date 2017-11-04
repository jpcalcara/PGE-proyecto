#ifndef FORMULARIO_H
#define FORMULARIO_H

#include <QWidget>
#include <QImage>
#include <QDebug>
#include <QMessageBox>
#include <QPainter>


#include "admindb.h"


namespace Ui {
class Formulario;
}

class Formulario : public QWidget
{
    Q_OBJECT

public:
    explicit Formulario(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    ~Formulario();

signals:
    void signal_ShowLogin(bool);

private:
    Ui::Formulario *ui;
    AdminDB *admin;
    QImage im_fondoform;

private slots:

    /**
     * @brief slot_backlogin regresa al login por medio del boton volver
     */
    void slot_backlogin();

    /**
     * @brief slot_register regresa a la ventana de login una vez completo el registro
     */
    void slot_register();

    /**
     * @brief slot_verPass muestra el string correspondiente al password ingresado por el user
     */
    void slot_verPass(bool a);

    /**
     * @brief slot_noverPass encripta el string correspondiente al password ingresado por el user
     */
    void slot_noverPass(bool a);
};

#endif // FORMULARIO_H
