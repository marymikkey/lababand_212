#include "plot_scatter.h"

void PlotScatter::draw(QCustomPlot *plot)
{

    for (int i = 0; i < 2; ++i)
    {

        auto graph = plot->addGraph();
        QPen pen;

        graph->setPen(pen);

        QVector<double> x,y;

        for (int j=0; j<101; ++j)
        {
            x.append(j/50.0 -1);
            y.append(0.2 * i + x[j]*x[j]);
        }
        graph->setData(x,y);
    }

    plot->rescaleAxes();
    plot->replot();
}
