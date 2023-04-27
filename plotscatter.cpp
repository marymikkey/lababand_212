#include "plotscatter.h"

PlotScatter::PlotScatter(QWidget* parent) : Plot(parent){}

PlotScatter::~PlotScatter() {}

void PlotScatter::draw(QCustomPlot *plot)
{
    auto m = Manager::instance();
    for (int i = 0; i < m->variables.size(); i++) {
        auto& v = m-> variables[i];

        QVector<double> x(101), y(101);
        for (int j=0; j<101; ++j)
        {
            x[j] = j/50.0 -1;
            y[j] = 0.2 * i + x[j]*x[j];
        }

        plot->addGraph();
        if (!v.visual.visible) continue;
        QPen pen;
        pen.setColor(v.visual.color);
        pen.setStyle(v.visual.line_type);
        pen.setWidthF(v.visual.width);
        plot->graph(i)->setData(x, y);

        plot->graph(i)->setScatterStyle(v.visual.point_type);
    }

    plot->xAxis->setLabel("x");
    plot->yAxis->setLabel("y");

    plot->xAxis->setRange(-1, 1);
    plot->yAxis->setRange(0, 1);
    plot->replot();
}

void PlotScatter::options()
{

}
