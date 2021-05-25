#include "intervalinsertwindow.h"
#include "ui_intervalinsertwindow.h"

IntervalInsertWindow::IntervalInsertWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IntervalInsertWindow)
{
    ui->setupUi(this);
}

IntervalInsertWindow::~IntervalInsertWindow()
{
    delete ui;
}

