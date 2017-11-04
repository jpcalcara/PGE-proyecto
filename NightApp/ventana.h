#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>
#include <QImage>
#include <QModelIndex>
#include <QStringList>
#include <QTimer>
#include <QVector>
#include <QHeaderView>
#include <QObject>
#include <QEvent>
#include <QDebug>
#include <QLabel>

#include "localizacion.h"
#include "mapa.h"
#include "lineadetexto.h"
#include "busquedanombre.h"
#include "infolugar.h"
#include "sites.h"
#include "sitesroute.h"


class Mapa;
class Sites;
class SitesRoute;
class InfoLugar;
class BusquedaNombre;
class Localizacion;


namespace Ui {
class Ventana;
}

class Ventana : public QWidget
{
    Q_OBJECT

public:
    explicit Ventana(QWidget *parent = 0);
    ~Ventana();
    void paintEvent(QPaintEvent *);


signals:
    void signal_ShowLogin(bool);


private:
    Ui::Ventana *ui;
    Mapa *map;
    Localizacion *loc;
    Sites *sites;
    SitesRoute *siteroute;
    InfoLugar *infolugar;
    BusquedaNombre *BNombre;
    int valor=0;
    QImage im_fondoven;
    QStringList listRecibidaLatLon,listPlaceIdLugares;
    int tipo;
    QTimer *timer;
    QStringList *lista;

private slots:

    /**
     * @brief slot_comboBox
     */
    void slot_comboBox(int i);

    /**
     * @brief slot_ActualizaPos
     */
    void slot_ActualizaPos();//filtro de venta tipo de categoria

    /**
     * @brief slot_ListadoInfo  muestra listado de los sitios al rededor de la posicion actual
     */
    void slot_ListadoInfo(QStringList list);

    /**
     * @brief slot_Busca
     */
    void slot_Busca(); // le busca un domicilio

    /**
     * @brief slot_recivBusqueda
     */
    void slot_recivBusqueda(QStringList listNombre,QStringList listLocalizacion,QStringList listPlaceId);

    /**
     * @brief slot_ActualizaMapaSpinBox
     */
    void slot_ActualizaMapaSpinBox(QString i);

    /**
     * @brief slot_recivRuta
     */
    void slot_recivRuta(QStringList list);

    /**
     * @brief slot_ActivaListado  obtiene el listado de los sitios
     */
    void slot_ActivaListado(QModelIndex index);

    /**
     * @brief slot_recivListado  habilita los parametros de distancia y tiempo del viaje en el mapa
     */
    void slot_recivListado(QStringList listNombre,QStringList listLocalizacion,QStringList listPlaceId);

    /**
     * @brief slot_backStart  permite regresar a la ventana principal
     */
    void slot_backStart();

    /**
     * @brief slot_ObtieneDom  muestra el domicilio por consola para realizar pruebas
     */
    void slot_ObtieneDom(QString dom);

    /**
     * @brief slot_ActualizaPosMapRuta  actualiza la posicion obteniendo un listado con las coordenadas
     */
    void slot_ActualizaPosMapRuta(QString num);
};

#endif // VENTANA_H
