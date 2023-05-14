#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "manager.h"
#include "plots/plot2d.h"
#include "plots/plotScatter.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Manager::instance()->plot = new PlotScatter;
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
}
