#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "siguiente.h"
#include "eliminar.h"
#include "buscar.h"
#include "verregistros.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_insertar_clicked()
{
    siguiente* insertar = new siguiente();
    insertar->show();
    close();
}


void MainWindow::on_eliminar_clicked()
{
    eliminar* eliminar_v = new eliminar();
    eliminar_v->show();
    close();
}

void MainWindow::on_buscar_clicked()
{
    Buscar* buscar_v = new Buscar();
    buscar_v->show();
    close();
}

void MainWindow::on_ver_registros_clicked()
{
    VerRegistros* registros_v = new VerRegistros();
    registros_v->show();
    close();
}

