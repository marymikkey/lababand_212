#include "IMPCSV.h"
#include "Manager.h"

#include <QDebug>

IMPCSV::IMPCSV(QWidget* parent) :IO(parent){}

IMPCSV::~IMPCSV() {}

QString getCSV(){
    QString res;
    auto m = Manager::instance();
    for (auto& v: m->variables){
        res.append(v.naming.alias + ",");
    }
    res[res.size() - 1] = '\n';
    for (int i = 0; i < m->getMeasurementCount(); i++){
        for (auto& v: m->variables){
            res.append(QString::number(v.values[i]) + ",");
        }
        res[res.size() - 1] = '\n';
    }
    return res;

}

void IMPCSV::save()
{
    qInfo() << getCSV();
}

void IMPCSV::load()
{

}
