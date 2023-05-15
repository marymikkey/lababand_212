#include "plotHist.h"
#include <iostream>

void PlotHist::draw(QCustomPlot *plot)
{
    plot->clearGraphs();
    plot->legend->clear();
    for (int i = 0; i < 3; ++i)
    {
        auto graph = plot->addGraph();
        QPen pen;
        pen.setColor(QColor(i*100, i*100, i*100));
        pen.setStyle(Qt::DashDotLine);
        pen.setWidth(3);
        graph->setPen(pen);
        graph->setLineStyle(QCPGraph::LineStyle::lsStepCenter);

        graph->setName(QString::number(i));

        QVector<double> x, y;
        for (int j=0; j<101; ++j)
        {
            x.append(j/50.0 -1);
            y.append(i + x[j]*x[j]);
        }

        double min = y[0], max = y[0];
        for (double _y : y)
        {
            min = std::min(_y, min);
            max = std::max(_y, max);
        }

        int histArray [bins];
        for (int j=0; j<bins; j++)
        {
            histArray[j] = 0;
        }

        int _bin = 0;
        for (int j=0; j<101; ++j)
        {
            _bin = (int)floor((y[j] - min) / ((max - min) / bins));
            histArray[_bin]++;
        }

        QVector<double> elem_amount, bin_num;
        for (int j=0; j<bins; j++)
        {
            elem_amount.append(histArray[j]);
            bin_num.append(j+i+3);
        }

        graph->setData(elem_amount, bin_num);
    }
    if (plot->plotLayout()->children().size() <= 1)
    {
        plot->plotLayout()->insertRow(0);
        plot->plotLayout()->addElement(0, 0, new QCPTextElement(plot, title));
    }
    static_cast<QCPTextElement* >(plot->plotLayout()->element(0,0))->setText(title);
    plot->xAxis->setLabel(xlabel);
    plot->yAxis->setLabel(ylabel);
    plot->legend->setVisible(true);
    plot->legend->setBrush(QColor(255, 255, 0, 100));
    plot->rescaleAxes();
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plot->replot();
}

void PlotHist::options()
{
    PlotHistDialog optionDialog{xlabel, ylabel, title, bins, this};
    optionDialog.show();
    optionDialog.exec();
    xlabel = optionDialog.xlabel.text();
    ylabel = optionDialog.ylabel.text();
    title = optionDialog.title.text();
    bins = optionDialog.bins.value();
}

PlotHistDialog::PlotHistDialog(QString xlabel, QString ylabel, QString title, int bins, QWidget *parent)
    : xlabel(xlabel), ylabel(ylabel), title(title),  QDialog{parent}
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

    QLabel *binsWidget = new QLabel(tr("Bin count:"));
    mainlayout->addWidget(binsWidget);
    this->bins.setValue(bins);
    mainlayout->addWidget(&this->bins);

    setLayout(mainlayout);
}
