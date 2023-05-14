#include "plotScatter.h"


void PlotScatter::draw(QCustomPlot *plot)
{
    plot->clearGraphs();
    plot->legend->setVisible(false);


    for (int i = 0; i < 3; ++i)
    {

        auto graph = plot->addGraph();
        QPen pen;
        pen.setColor(QColor(i*100, i*100, i*100));
        pen.setStyle(Qt::DashDotLine);
        pen.setWidth(8);
        graph->setPen(pen);
        graph->setScatterStyle(QCPScatterStyle::ssDot);
        graph->setLineStyle(QCPGraph::lsNone);
        graph->setName(QString::number(i));

        QCPErrorBars *errorBarsX = new QCPErrorBars(plot->xAxis, plot->yAxis);
        QCPErrorBars *errorBarsY = new QCPErrorBars(plot->yAxis, plot->xAxis);

        errorBarsX->removeFromLegend();
        errorBarsY->removeFromLegend();
        errorBarsX->setDataPlottable(graph);
        errorBarsY->setDataPlottable(graph);


        QVector<double> x, y, ex, ey;

        for (int j=0; j<5; ++j)
        {
            x.append(j - 2);
            y.append(i + x[j]*x[j]);
            ex.append(0.0005*x[j]);
            ey.append(0.02*y[j]);
        }
        graph->setData(x,y);

        errorBarsX->setData(ex);
        errorBarsY->setData(ey);
    }

    if (plot->plotLayout()->children().size() <= 1)
    {
        plot->plotLayout()->insertRow(0);
        plot->plotLayout()->addElement(0, 0, new QCPTextElement(plot, title));
    }

    static_cast<QCPTextElement* >(plot->plotLayout()->element(0, 0))->setText(title);
    plot->xAxis->setLabel(xlabel);
    plot->yAxis->setLabel(ylabel);
    plot->legend->setVisible(true);
    plot->legend->setBrush(QColor(255, 255, 0, 100));
    plot->rescaleAxes();
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plot->replot();
}

void PlotScatter::options()
{
    PlotScatterDialog optionDialog {xlabel, ylabel, title, this};
    optionDialog.show();
    optionDialog.exec();
    xlabel = optionDialog.xlabel.text();
    ylabel = optionDialog.ylabel.text();
    title = optionDialog.title.text();
}

PlotScatterDialog::PlotScatterDialog(QString xLabel, QString yLabel, QString title, QWidget *parent)
    : xlabel(xLabel), ylabel(yLabel), title(title),  QDialog{parent}
{
    QVBoxLayout *mainlayout = new QVBoxLayout;

    QLabel *titleWidget = new QLabel(tr("Plot title: "));
    mainlayout->addWidget(titleWidget);
    mainlayout->addWidget(&this->title);

    QLabel *xLabelWidget = new QLabel(tr("X axis label: "));
    mainlayout->addWidget(xLabelWidget);
    mainlayout->addWidget(&this->xlabel);

    QLabel *yLabelWidget = new QLabel(tr("Y axis label: "));
    mainlayout->addWidget(yLabelWidget);
    mainlayout->addWidget(&this->ylabel);

    setLayout(mainlayout);
}
