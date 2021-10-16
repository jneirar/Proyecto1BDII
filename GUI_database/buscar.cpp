#include "buscar.h"
#include "ui_buscar.h"
#include "mainwindow.h"
#include "siguiente.h"
#include "eliminar.h"
#include "verregistros.h"

Buscar::Buscar(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Buscar)
{
    ui->setupUi(this);
}

Buscar::~Buscar()
{
    delete ui;
}

void Buscar::on_inicio_clicked()
{
    MainWindow* ventana_principal = new MainWindow();
    ventana_principal->show();
    close();
}

void Buscar::on_insertar_clicked()
{
    siguiente* insertar = new siguiente();
    insertar->show();
    close();
}

void Buscar::on_eliminar_clicked()
{
    eliminar* eliminar_v = new eliminar();
    eliminar_v->show();
    close();
}

void Buscar::on_ver_registros_clicked()
{
    VerRegistros* registros_v = new VerRegistros();
    registros_v->show();
    close();
}

