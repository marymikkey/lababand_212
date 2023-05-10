#ifndef PLOTCHOICE_H
#define PLOTCHOICE_H

#include "plot.h"
#include "plotscatter.h"
#include "ploshist.h"

#include <QDialog>

enum PlotOptions{
    SCATTER = 0,
    HISTOGRAM,
};

class PlotChoiceDialog: public QDialog
{
    Q_OBJECT

public:
    explicit PlotChoiceDialog(PlotOptions current, QWidget *parent = nullptr);
    QComboBox choice;
};

class PlotChoice : public Plot {
    Q_OBJECT
public:
    PlotChoice(QWidget* parent = nullptr);
    ~PlotChoice();

    virtual void draw(QCustomPlot *plot) override;
    virtual void options() override;
private:
    PlotScatter scatterPlot;
    PlotHistogram histPlot;
    PlotOptions current = SCATTER;
private slots:
    void optionsSpecific();
};
#endif // PLOTCHOICE_H
