#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_insertar_clicked();

    void on_eliminar_clicked();

    void on_buscar_clicked();

    void on_ver_registros_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
