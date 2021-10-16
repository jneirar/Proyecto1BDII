#include "siguiente.h"
#include "ui_siguiente.h"
#include "mainwindow.h"
#include "eliminar.h"
#include "buscar.h"
#include "verregistros.h"

siguiente::siguiente(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::siguiente)
{
    ui->setupUi(this);
}

siguiente::~siguiente()
{
    delete ui;
}

void siguiente::on_inicio_clicked()
{
    MainWindow* ventana_principal = new MainWindow();
    ventana_principal->show();
    close();
}

void siguiente::on_eliminar_clicked()
{
    eliminar* eliminar_v = new eliminar();
    eliminar_v->show();
    close();
}

void siguiente::on_buscar_clicked()
{
    Buscar* buscar_v = new Buscar();
    buscar_v->show();
    close();
}

void siguiente::on_ver_registros_clicked()
{
    VerRegistros* registros_v = new VerRegistros();
    registros_v->show();
    close();
}

