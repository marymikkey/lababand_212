#include "mainwindow.h"

#include<QTranslator>
#include <QApplication>
#include "Parser.h"
#include "Grammar.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString & locale : uiLanguages){
        const QString baseName = "classroom_" + QLocale(locale).name();
        if (translator.load(":/il8n/" + baseName)){
            a.installTranslator(&translator);
            break;
        }
    }

    MainWindow w;
    w.setWindowState(Qt::WindowMaximized);
    w.show();


    variable_map["x"] = QList<QVariant>({11,22});

    //test1("y = 22 + 44*x * square(3333) + min(1,-1,-3333) + one() + sqrt(225, 1, 2)");
    test1("y = 22*x + 44");
    test1("z = x + x");
    qInfo() << Qt::endl << "dkdkd" << Qt::endl;
    qInfo() << variable_map["x"];
    qInfo() << variable_map["y"];
    qInfo() << variable_map["z"];
    qInfo() << variable_map["w"];
    qInfo() << variable_map["d"];
    qInfo() << variable_map["sqrt"];

    return a.exec();
}

