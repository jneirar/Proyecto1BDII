#ifndef ELIMINAR_H
#define ELIMINAR_H

#include <QMainWindow>

namespace Ui {
class eliminar;
}

class eliminar : public QMainWindow
{
    Q_OBJECT

public:
    explicit eliminar(QWidget *parent = nullptr);
    ~eliminar();

private slots:
    void on_inicio_clicked();
    void on_insertar_clicked();
    void on_ver_registros_clicked();
    void on_buscar_clicked();

private:
    Ui::eliminar *ui;
};

#endif // ELIMINAR_H
