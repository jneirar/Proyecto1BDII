#include "mainwindow.h"
#include "C:\Users\usuario\OneDrive\Escritorio\UTEC\Semestre_5\BD2\Proyecto1BDII\Techniques\DynamicHash\extendibleHash.h"
#include "C:\Users\usuario\OneDrive\Escritorio\UTEC\Semestre_5\BD2\Proyecto1BDII\Techniques\Sequential\sequential.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "GUI_database_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
