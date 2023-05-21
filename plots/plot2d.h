#ifndef PLOT2D_H
#define PLOT2D_H

#include "plot.h"

class Plot2dDialog : public QDialog
{
    Q_OBJECT
public:
    explicit Plot2dDialog(QString xlabel, QString ylabel, QString title, QWidget *parent = nullptr);
    QLineEdit xlabel, ylabel, title;

};

class Plot2d : public Plot
{
    Q_OBJECT
public:
    Plot2d(QWidget *parent = nullptr) : Plot(parent) {};
    ~Plot2d() {};

    void draw(QCustomPlot *plot) override;
    void options() override;
    QString xlabel, ylabel, title = "";
};

#endif // PLOT2D_H
