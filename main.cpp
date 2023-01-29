#include "./MainWindow/mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <iostream>
#include <cstring>

#include "./PythonModule/pythonmodule.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //在软件启动的时候加入nogui的argument就会进入无界面窗口
    if (argc == 2 && !strcmp(argv[1], "nogui"))
    {
        PythonModule::pythonInit();
        return 0;
    }

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "MCRCON_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return a.exec();
}
