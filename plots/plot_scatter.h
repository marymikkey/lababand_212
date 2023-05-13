#ifndef PLOT_SCATTER_H
#define PLOT_SCATTER_H

#include "plot.h"

class PlotScatterOptionsDialog : public QDialog
{
    Q_OBJECT
public:
    QLineEdit xlabel, ylabel, title;
};

class PlotScatter : public Plot
{
    Q_OBJECT
public:
   PlotScatter(QWidget *parent = nullptr) : Plot(parent) {};
   ~PlotScatter() {};

    void draw(QCustomPlot *plot) override;
    QString xlabel = "Measurement count", ylabel = "Measurement value", title = "";
};
#endif // PLOT_SCATTER_H
