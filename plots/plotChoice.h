#ifndef PLOTCHOICE_H
#define PLOTCHOICE_H

#include "plot.h"

class PlotChoiceDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PlotChoiceDialog(QString choice, QStringList plots, QWidget *parent = nullptr);
    QComboBox choice;
private slots:
    void options();
};

class PlotChoice : public Plot
{
    Q_OBJECT
public:
    PlotChoice (QMap<QString, Plot*> plots, QWidget *parent = nullptr) :  Plot(parent), plots{plots}, choice{plots.keys()[2]} { }
    ~PlotChoice() {};

    void draw(QCustomPlot *plot) override;
    void options() override;
    QMap<QString, Plot*> plots;
    QString choice;
    void optionsChoice(QString choice);
};

#endif // PLOTCHOICE_H
