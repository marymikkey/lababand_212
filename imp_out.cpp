
#include "imp_out.h"

void ImpOut_CSV::save(const QString& output){
    QFile file(output);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            throw std::runtime_error("Couldn't open a file: " + file.error());
            return;
        }

    QTextStream outstream(&file);

    auto* manager = Manager::instance();
    if (manager->getVariablesSize() > 0){
        for (int i = 0; i < manager->getVariablesSize(); ++i)
        {
            if (i == 0)
                outstream << (*manager).variables[i].shortNaming;
            else
                outstream << "," << (*manager).variables[i].shortNaming;
        }
        outstream << Qt::endl;

        for (int i = 0; i < manager->getMeasurementAmount(); ++i) {
            for (int j = 0; j < manager->getVariablesSize(); ++j)
            {
                if (j == 0)
                    outstream << (*manager).variables[j].measurements.at(i);
                else
                    outstream << "," << (*manager).variables[j].measurements.at(i);
            }
            outstream << Qt::endl;
        }
    }
    file.close();
}

void ImpOut_CSV::load(const QString& input){
    QFile file(input);
    if(!file.open(QIODevice::ReadOnly)){
            throw std::runtime_error("Couldn't open a file: " + file.error());
            return;
        }
    QTextStream instream(&file);
    QString fullName;
    Manager::instance()->clear();
    QString str = instream.readLine();

    for (int i = 0; i < str.size(); ++i){
        if (str[i] == ','){
            Manager::instance()->addVariable(VariableData (fullName));
            fullName.clear();
            continue;
        }
        fullName += str[i];
        if (i + 1 == str.size())
            Manager::instance()->addVariable(VariableData (fullName));
    }

    QList<double> data;
    while (!instream.atEnd()){
        QString str = instream.readLine();
        QStringList num_strings = str.split(u',');
        for (QString num_str : num_strings){
            bool flag;
            int num = num_str.toInt(&flag, 10);
            if (flag)
                data.append(num);
            else
                data.append(NAN);
        }
        for (int i = data.size(); i < Manager::instance()->getVariablesSize(); ++i)
            data.append(NAN);
        Manager::instance()->addMeasurementRow(data);
        data.clear();
    }
    file.close();
}


