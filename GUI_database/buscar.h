#ifndef BUSCAR_H
#define BUSCAR_H

#include <QMainWindow>

namespace Ui {
class Buscar;
}

class Buscar : public QMainWindow
{
    Q_OBJECT

public:
    explicit Buscar(QWidget *parent = nullptr);
    ~Buscar();

private slots:
    void on_inicio_clicked();
    void on_insertar_clicked();
    void on_eliminar_clicked();
    void on_ver_registros_clicked();

private:
    Ui::Buscar *ui;
};

#endif // BUSCAR_H
