#include "eliminar.h"
#include "ui_eliminar.h"
#include "mainwindow.h"
#include "siguiente.h"
#include "buscar.h"
#include "verregistros.h"

eliminar::eliminar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::eliminar)
{
    ui->setupUi(this);
}

eliminar::~eliminar()
{
    delete ui;
}

void eliminar::on_inicio_clicked()
{
    MainWindow* ventana_principal = new MainWindow();
    ventana_principal->show();
    close();
}


void eliminar::on_insertar_clicked()
{
    siguiente* insertar = new siguiente();
    insertar->show();
    close();
}

void eliminar::on_buscar_clicked()
{
    Buscar* buscar_v = new Buscar();
    buscar_v->show();
    close();
}

void eliminar::on_ver_registros_clicked()
{
    VerRegistros* registros_v = new VerRegistros();
    registros_v->show();
    close();
}

