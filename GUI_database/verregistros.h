#ifndef VERREGISTROS_H
#define VERREGISTROS_H

#include <QMainWindow>

namespace Ui {
class VerRegistros;
}

class VerRegistros : public QMainWindow
{
    Q_OBJECT

public:
    explicit VerRegistros(QWidget *parent = nullptr);
    ~VerRegistros();

private slots:
    void on_inicio_clicked();
    void on_insertar_clicked();
    void on_eliminar_clicked();
    void on_buscar_clicked();

private:
    Ui::VerRegistros *ui;
};

#endif // VERREGISTROS_H
