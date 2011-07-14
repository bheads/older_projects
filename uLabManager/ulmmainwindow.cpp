#include "ulmmainwindow.hpp"
#include "ui_ulmmainwindow.h"

ulmMainWindow::ulmMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ulmMainWindow)
{
    ui->setupUi(this);
}

ulmMainWindow::~ulmMainWindow()
{
    delete ui;
}

void ulmMainWindow::on_ClientAddButton_clicked()
{

}
