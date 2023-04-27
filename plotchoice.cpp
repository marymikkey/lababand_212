#include "PlotChoice.h"
#include "Manager.h"

PlotChoice::PlotChoice(QWidget* parent) : Plot(parent){}

PlotChoice::PlotChoice() {}

void PlotChoice::draw(QCustomPlot *plot)
{
    switch(current){
    case PlotOptions::HISTOGRAM:
        return histPlot.draw(plot);
    case PlotOptions::SCATTER:
        return scatterPlot.draw(plot);
    }
}

void PlotChoice::options()
{
    PlotChoiceDialog dialog(current,this);
    dialog.show();
    dialog.exec();
    current = static_cast<PlotOptions>(dialog.choice.currentindex());
}

void PlotChoice::optionsSpecific()
{
    switch(current){
    case PlotOptions::HISTOGRAM:
        return histPlot.options();
    case PlotOptions::SCATTER:
        return scatterPlot.options();
    }
}


PlotChoiceDialog::PlotChoiceDialog(PlotOptions current, QWidget *parent)
    : QDialog(parent)

{
    QVBoxLayout *mainLayout = new QVBoxLayout;


    QLabel *titleLable = new QLabel(tr("Dialog type:"));
    mainLayout->addWidget(choiceLabel);
    choice.clear();
    choice.insertitem(0, "Scatter")
    choice.insertitem(1, "Histogram")
    choice.setCurrentIndex(current);
    mainLayout->addWidget(&choice);

    QLabel *optionsLabel = new QLabel(tr("More options:"));
    QPushButton *options = new QPushButton(tr("Plot-specific options"));
    connect(options, SIGNAL(clicked()), parent, SLOT(optionsSpecific()));
    mainLayout->addWidget(optionsLabel);
    mainLayout->addWidget(options);

    setLayout(mainLayout);
    setWindowtitle(tr("Choice current plot type"));
}

}
