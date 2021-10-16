#ifndef SIGUIENTE_H
#define SIGUIENTE_H

#include <QMainWindow>

namespace Ui {
class siguiente;
}

class siguiente : public QMainWindow
{
    Q_OBJECT

public:
    explicit siguiente(QWidget *parent = nullptr);
    ~siguiente();

private slots:
    void on_inicio_clicked();
    void on_eliminar_clicked();
    void on_buscar_clicked();
    void on_ver_registros_clicked();

private:
    Ui::siguiente *ui;
};

#endif // SIGUIENTE_H
