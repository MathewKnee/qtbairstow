#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QMessageBox>
#include <QButtonGroup>
#include "intervalinsertwindow.h"
#include "fpinsertwindow.h"
#include "fpoutput.h"
#include <Interval.h>
#include "bairstowMethod.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    std::shared_ptr<std::vector<long double>> FP_in;
    std::shared_ptr<std::vector<long double>> FP_out;
    std::shared_ptr<bool> FP_in_finished, Int_in_finished;
    std::shared_ptr<std::vector<interval_arithmetic::Interval<long double>>> Int_in;
    std::shared_ptr<std::vector<interval_arithmetic::Interval<long double>>> Int_out;
    std::shared_ptr<int> max_iterations;
private:
    Ui::MainWindow *ui;
    long double mincorr = 1e-16;
    long double zerodet = 1e-16;
private slots:
    void solvePressed();
    void insertPressed();
    void fpSelected();
    void intervalSelected();
    void enableWindow();
};
#endif // MAINWINDOW_H
