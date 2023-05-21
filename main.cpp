#include "mainwindow.h"

#include<QTranslator>
#include <QApplication>
#include "Parser.h"


std::map<std::string, QVariant> variable_map;


void test1(QString input){
    try {
        ASTNPtr out_node;
        ParseOrDie(input.toStdString(), ArithmeticGrammar1(), qi::space, out_node);
        qInfo() << "evaluate() = " << out_node->evaluate();
        delete out_node;
    } catch (std::exception& e){
        qInfo() << "EXCEPTION: " << e.what();
    }
}


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

    test1("d = 22 + 44*x * square(3333) + min(1,-1,-3333) + one() + sqrt(225, 1, 2)");
    test1("y = 22*x");
    test1("z = x + x");
    test1("w = 11 + 10");
    qInfo() << Qt::endl << "dkdkd" << Qt::endl;
    qInfo() << variable_map["x"];
    qInfo() << variable_map["y"];
    qInfo() << variable_map["z"];
    qInfo() << variable_map["w"];
    qInfo() << variable_map["d"];
    qInfo() << variable_map["sqrt"];

    return a.exec();
}

//заменить qvariant на структуры с 2мя полями value и error (можно еще собс операторы сложения умножения величин с ошибкой)

//1: переписывать variable node и assignment node таким образом, чтобы они работали с менеджером
//2: чтобы в test1 до парсера зачистить variable map от того что там было, захерачить туда данные из менеджера и затем после парса залить все обратно
//3 оператор индексации, динамическая подгр
