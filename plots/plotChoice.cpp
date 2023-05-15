#include "plotChoice.h"
#include "manager.h"

void PlotChoice::draw(QCustomPlot *plot)
{
    plots[choice]->draw(plot);
}

void PlotChoice::options()
{
    PlotChoiceDialog optionDialog{choice, plots.keys(), this};
    optionDialog.show();
    optionDialog.exec();
    choice = optionDialog.choice.currentText();
}

void PlotChoice::optionsChoice(QString choice)
{
    plots[choice]->options();
}

PlotChoiceDialog::PlotChoiceDialog(QString choice, QStringList plots, QWidget *parent)
    :  QDialog{parent}
{
    QVBoxLayout *mainlayout = new QVBoxLayout;

    QLabel *chooseLable = new QLabel(tr("Chosen plot:"));
    mainlayout->addWidget(chooseLable);
    this->choice.insertItems(0, plots);
    this->choice.setCurrentText(choice);
    mainlayout->addWidget(&this->choice);

    QLabel *optionsLable = new QLabel(tr("Options of current plot"));
    mainlayout->addWidget(optionsLable);
    QPushButton *currentPlotOptions = new QPushButton("Options");
    mainlayout->addWidget(currentPlotOptions);
    connect(currentPlotOptions, SIGNAL(clicked()), this, SLOT(options()));

    setLayout(mainlayout);
}

void PlotChoiceDialog::options()
{
    static_cast<PlotChoice*>(parent())->optionsChoice(choice.currentText());
}
