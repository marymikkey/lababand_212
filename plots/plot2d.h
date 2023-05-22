#ifndef PLOT2D_H
#define PLOT2D_H

#include "plot.h"

class Plot2dOptionsDialog : public QDialog
{
    Q_OBJECT
public:
    explicit Plot2dOptionsDialog(QString xlabel, QString ylabel, QString title, QWidget *parent = nullptr);
    QLineEdit title;
    QComboBox xLabel, yLabel;
};

class Plot2d : public Plot
{
    Q_OBJECT
public:
    Plot2d(QString xlabel, QString ylabel, QWidget *parent = nullptr);;
    ~Plot2d() {};

    void draw(QCustomPlot *plot) override;
    void options() override;
    QString xLabel, yLabel, title = "";
};

#endif // PLOT2D_H
