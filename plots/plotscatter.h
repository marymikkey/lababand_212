#ifndef PLOTSCATTER_H
#define PLOTSCATTER_H

#include "plot.h"

class PlotScatterDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PlotScatterDialog(QString xLabel, QString yLabel, QString title, QWidget *parent = nullptr);
    QLineEdit xlabel, ylabel, title;
};

class PlotScatter : public Plot
{
    Q_OBJECT
public:
   PlotScatter(QWidget *parent = nullptr) : Plot(parent) {};
   ~PlotScatter() {};

    void draw(QCustomPlot *plot) override;
private:
    QString xlabel = "Measurement count", ylabel = "Measurement value", title = "";
};
#endif // PLOTSCATTER_H
