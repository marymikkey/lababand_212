#ifndef PLOT_H
#define PLOT_H

#include <QWidget>
#include"qcustomplot.h"

class Plot : public QWidget {
    Q_OBJECT
public:
    Plot(QWidget* parent = nullptr);
    ~Plot();

    virtual void draw(QCustomPlot *plot) = 0;
    virtual void options() = 0;
private:
};

#endif // PLOT_H
