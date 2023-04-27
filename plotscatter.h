#ifndef PLOTSCATTER_H
#define PLOTSCATTER_H

#include "plot.h"

#include <QDialog>

class PlotScatterDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlotScatterDialog(QString xLabel, QString yLabel, QString title, QWidget *parent = nullptr);
    QLineEdit xLabel, yLabel, title;
};

class PlotScatter : public Plot {
    Q_OBJECT
public:
    PlotScatter(QWidget* parent = nullptr);
    ~PlotScatter();

    virtual void draw(QCustomPlot *plot) override;
    virtual void options() override;
private:
    QString title = "", xLabel = "Measurement number", yLabel = "Measurement value";
};




#endif // PLOTSCATTER_H
