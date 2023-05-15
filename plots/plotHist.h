#ifndef PLOT_HIST_H
#define PLOT_HIST_H

#include "plot.h"

class PlotHistDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PlotHistDialog(QString xlabel, QString ylabel, QString title, int bins, QWidget *parent = nullptr);
    QLineEdit xlabel, ylabel, title;
    QSpinBox bins;
};

class PlotHist : public Plot
{
    Q_OBJECT
public:
   PlotHist(QWidget *parent = nullptr) : Plot(parent) {};
   ~PlotHist() {};

    void draw(QCustomPlot *plot) override;
    void options() override;
    QString xlabel, ylabel, title = "";
    int bins = 10;
};

#endif // PLOT_HIST_H
