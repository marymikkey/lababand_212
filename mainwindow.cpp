#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "manager.h"

#include "visualmodel.h"
#include "namingmodel.h"
#include "datamodel.h"
#include "errormodel.h"

#include "colordelegate.h"
#include "comboboxdelegate.h"

#include "plots/plot.h"
#include "plots/plotChoice.h"
#include "plots/plotScatter.h"
#include "plots/plot2d.h"
#include "plots/plotHist.h"

#include <QDebug>

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Table");
    Manager::instance()->addVariable(VariableData());
    Manager::instance()->addVariable(VariableData());
    Manager::instance()->addVariable(VariableData());
    //Manager::instance()->addVariable(VariableData(5));
    //Manager::instance()->addVariable(VariableData(5));
    //Manager::instance()->addVariable(VariableData(5));

    Manager::instance()->addMeasurement();
    Manager::instance()->addMeasurement();
    Manager::instance()->addMeasurement();
    Manager::instance()->addMeasurement();
    Manager::instance()->addMeasurement();

    ui->visual_tableView->setModel(new VisualModel());
    ui->visual_tableView->setItemDelegateForColumn(4, new ColorDelegate());
    ui->visual_tableView->setItemDelegateForColumn(3, new ComboBoxDelegate(VariableData::VisualOptions::point_types.values()));
    ui->visual_tableView->setItemDelegateForColumn(2, new ComboBoxDelegate(VariableData::VisualOptions::line_types.values()));

    ui->naming_tableView->setModel(new NamingModel());

    ui->variable_tableView->setModel(new DataModel());

    ui->errors_tableView->setModel(new ErrorModel());
    ui->errors_tableView->setItemDelegateForColumn(0, new ComboBoxDelegate(VariableData::Error::error_types.values()));

//    Manager::instance()->plot = new PlotScatter;//PlotChoice();//PlotHistogramm();//PlotScatter;
    Manager::instance()->plot = new PlotChoice({
        {"Scatter plot", new PlotScatter},
        {"Histogram plot", new PlotHist},
        {"2d scatter plot", new Plot2d("",
                                       "")}});
    Manager::instance()->plot->draw(ui->plot);

    connect(ui->actionReplot, SIGNAL(triggered()), this, SLOT(draw()));
    connect(ui->actionOptions, SIGNAL(triggered()), this, SLOT(plotOptions()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    //connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    //connect(ui->actionLoad, SIGNAL(triggered()), this, SLOT(load()));
    //connect(ui->pushButtonColumnAdd, SIGNAL(clicked()), this, SLOT(addVariable()));
    //connect(ui->pushButtonRowAdd, SIGNAL(clicked()), this, SLOT(addRow()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

/*void MainWindow::createUI(const QStringList &headers)
{
    ui->tabWidget_0->setColumnCount(5);
    ui->tabWidget_0->setShowGrid(true);
}*/

void MainWindow::draw()
{
    Manager::instance()->plot->draw(ui->plot);
}

void MainWindow::save()
{
    Manager::instance()->variables.clear();
    QString fname = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                 "data.json",
                                                 tr("JSON data file (*.json)"));
    //tr("CSV data file (*.csv)"));
    QFile f(fname);
    f.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text);
    QTextStream out(&f);
    //out<<IOJson().save();
}

void MainWindow::load()
{
    Manager::instance()->variables.clear();
    QString fname = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                 "data.json",
                                                 tr("JSON data file (*.json)"));
    //tr("CSV data file (*.csv)"));
    QFile f(fname);
    f.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&f);
    //IOJson().load(in.readAll());
}

void MainWindow::plotOptions()
{
    Manager::instance()->plot->options();
}

void MainWindow::addVariable()
{
    auto m = Manager::instance();
    //m->addVariable(VariableData{m->getMeasurementsCount()});
    //static_cast<MeasurementModel*>(ui->variable_tableView->model())->insertColumn(m->getCalculatedCount());
    //static_cast<VisualModel*>(ui->visual_tableView->model())->insertRow(m->getCalculatedCount());
    //static_cast<InstrumentModel*>(ui->instruments_tableView->model())->insertRow(m->getCalculatedCount());
    //static_cast<NamingModel*>(ui->naming_tableView->model())->insertRow(m->getCalculatedCount());
}

void MainWindow::addRow()
{
    auto m = Manager::instance();
    //static_cast<MeasurementModel*>(ui->variable_tableView->model())->insertRow(m->getMeasurementsCount());
}

/*#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "manager.h"
#include "plots/plot2d.h"
#include "plots/plotScatter.h"
#include "plots/plotHist.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Manager::instance()->plot = new PlotHist;
    Manager::instance()->plot->draw(ui->plot);

    connect(ui->actionReplot, SIGNAL(triggered()), this, SLOT(draw()));
    connect(ui->actionOptions, SIGNAL(triggered()), this, SLOT(plotOptions()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw()
{
    Manager::instance()->plot->draw(ui->plot);
}

void MainWindow::plotOptions()
{
    Manager::instance()->plot->options();
}*/
