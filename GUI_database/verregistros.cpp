#include "verregistros.h"
#include "ui_verregistros.h"
#include "mainwindow.h"
#include "eliminar.h"
#include "siguiente.h"
#include "buscar.h"

VerRegistros::VerRegistros(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VerRegistros)
{
    ui->setupUi(this);
}

VerRegistros::~VerRegistros()
{
    delete ui;
}

void VerRegistros::on_inicio_clicked()
{
    MainWindow* ventana_principal = new MainWindow();
    ventana_principal->show();
    close();
}

void VerRegistros::on_insertar_clicked()
{
    siguiente* insertar = new siguiente();
    insertar->show();
    close();
}


void VerRegistros::on_eliminar_clicked()
{
    eliminar* eliminar_v = new eliminar();
    eliminar_v->show();
    close();
}

void VerRegistros::on_buscar_clicked()
{
    Buscar* buscar_v = new Buscar();
    buscar_v->show();
    close();
}


