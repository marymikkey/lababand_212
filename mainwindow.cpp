#include<iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "VisualModel.h"
#include "Manager.h"
#include "VariableData.h"
#include "colordelegate.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Manager::instance()->addVariable(VariableData());
    Manager::instance()->addVariable(VariableData());
    Manager::instance()->addVariable(VariableData());
    ui->visualView->setModel(new VisualModel());
    //ui -> visualView->setItemDelegateForColumn(4,)
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    std::cout << "babbab";
}

