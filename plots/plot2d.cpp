#include "plot2d.h"
#include "manager.h"

Plot2d::Plot2d(QString xLable, QString yLable, QWidget *parent) : Plot(parent), xLable{xLable}, yLable{yLable} {}

void Plot2d::draw(QCustomPlot *plot)
{
    auto m = Manager::instance();
    VariableData *xv = m->getChoiceVarCalc(xLable), *yv = m->getChoiceVarCalc(yLable);

    plot->clearGraphs();
    plot->legend->setVisible(false);
    if (!yv)
    {
        if (m->getVarCalcAmount() > 0)
        {
            xv = m->getChoiceVarCalc(0);
            yv = m->getChoiceVarCalc(0);
        } else return;
    }
    if (!xv) return;

    auto graph = plot->addGraph();
    QPen pen;
    pen.setWidth(8);
    graph->setPen(pen);
    graph->setScatterStyle(yv->visual.point_type);
    graph->setScatterStyle(QCPScatterStyle::ssDot);
    graph->setLineStyle(QCPGraph::lsNone);


    QCPErrorBars *errorBarsX = new QCPErrorBars(plot->xAxis, plot->yAxis);
    QCPErrorBars *errorBarsY = new QCPErrorBars(plot->yAxis, plot->xAxis);
    errorBarsX->setDataPlottable(graph);
    errorBarsY->setDataPlottable(graph);

    QVector<double> x,y,ex,ey;
    for (int j = 0; j < xv->getMeasurementsCount(); ++j)
    {
        x.append(xv->measurements[j]);
        y.append(yv->measurements[j]);
        ex.append(xv->getError(j));
        ey.append(yv->getError(j));
    }
    graph->setData(x,y);
    errorBarsX->setData(ex);
    errorBarsY->setData(ey);
    if (plot->plotLayout()->children().size() <= 1)
    {
        plot->plotLayout()->insertRow(0);
        plot->plotLayout()->addElement(0, 0, new QCPTextElement(plot, title));
    }
    static_cast<QCPTextElement* >(plot->plotLayout()->element(0,0))->setText(title);
    plot->xAxis->setLabel(xv->fullNaming);
    plot->yAxis->setLabel(yv->fullNaming);
    plot->rescaleAxes();
    plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    plot->replot();
}

void Plot2d::options()
{
    Plot2dOptionsDialog optionDialog{xLable, yLable, title, this};
    optionDialog.show();
    optionDialog.exec();
    xLable = Manager::instance()->getChoiceVarCalc(optionDialog.xLable.currentText())->shortNaming;
    yLable = Manager::instance()->getChoiceVarCalc(optionDialog.yLable.currentText())->shortNaming;
    title = optionDialog.title.text();
}

Plot2dOptionsDialog::Plot2dOptionsDialog(QString xLable, QString yLable, QString title, QWidget *parent)
    : title(title),  QDialog{parent}
{
    QVBoxLayout *mainlayout = new QVBoxLayout;

    QLabel *titleLable = new QLabel(tr("Plot title:"));
    mainlayout->addWidget(titleLable);
    mainlayout->addWidget(&this->title);

    QLabel *xLableWidget = new QLabel(tr("X axis label:"));
    mainlayout->addWidget(xLableWidget);
    this->xLable.clear();

    auto* m = Manager::instance();
    for (int i = 0; i < m->getVarCalcAmount(); ++i)
    {
        this->xLable.addItem(m->getChoiceVarCalc(i)->fullNaming);
        if (m->getChoiceVarCalc(i)->shortNaming == xLable)
            this->xLable.setCurrentIndex(this->xLable.count() - 1);
    }
    mainlayout->addWidget(&this->xLable);

    QLabel *yLableWidget = new QLabel(tr("Y axis label:"));
    mainlayout->addWidget(yLableWidget);
    this->yLable.clear();
    for (int i = 0; i < Manager::instance()->getVarCalcAmount(); ++i)
    {
        this->yLable.addItem(Manager::instance()->getChoiceVarCalc(i)->fullNaming);
        if (Manager::instance()->getChoiceVarCalc(i)->shortNaming == yLable)
            this->yLable.setCurrentIndex(this->yLable.count() - 1);
    }
    mainlayout->addWidget(&this->yLable);

    setLayout(mainlayout);
}
