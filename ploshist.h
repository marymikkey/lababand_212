#ifndef PLOSHIST_H
#define PLOSHIST_H

#include "plot.h"

#include <QDialog>
#include <QSpinBox>


class PlotHistogramDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlotHistogramDialog(QString xLabel, QString yLabel, QString title, QWidget *parent = nullptr);
    QLineEdit xLabel, yLabel, title;
    QSpinBox bins;
};

class PlotHistogram : public Plot
{
    Q_OBJECT
public:
    PlotHistogram(QWidget* parent = nullptr);
    ~PlotHistogram();

    virtual void draw(QCustomPlot *plot) override;
    virtual void options() override;
private:
    QString title = "".xLabel = "Measurement number", yLabel ="Measurement value";
    int bins = 10;
};
#endif // PLOSHIST_H
