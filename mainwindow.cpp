#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "manager.h"
#include "plots/plotscatter.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Manager::instance()->plot = new PlotScatter;
    Manager::instance()->plot->draw(ui->plot);

    connect(ui->actionReplot, SIGNAL(triggered()), this, SLOT(draw()));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw()
{
    Manager::instance()->plot->draw(ui->plot);
}

