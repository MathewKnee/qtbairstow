#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->arithmetic_Inter_radioButton,SIGNAL(toggled(bool)),this,SLOT(intervalSelected()));
    connect(ui->arithmetic_FP_radioButton,SIGNAL(toggled(bool)),this,SLOT(fpSelected()));
    connect(ui->insert_pushButton, SIGNAL(released()),this, SLOT(insertPressed()));
    connect(ui->solve_pushButton,SIGNAL(released()),this,SLOT(solvePressed()));
    ui->input_groupBox->setDisabled(true);
    max_iterations = std::shared_ptr<int>(new int(1));
    FP_in = std::shared_ptr<std::vector<long double>>(new std::vector<long double>());
    FP_in_finished = std::shared_ptr<bool>(new bool(false));
    Int_in = std::shared_ptr<std::vector<interval_arithmetic::Interval<long double>>>(new std::vector<interval_arithmetic::Interval<long double>>);
    Int_in_finished = std::shared_ptr<bool>(new bool(false));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::intervalSelected(){
    ui->input_groupBox->setDisabled(false);
    ui->input_Inter_radioButton->setEnabled(true);
}
void MainWindow::fpSelected(){
    ui->input_groupBox->setDisabled(false);
    ui->input_Inter_radioButton->setChecked(false);
    ui->input_Inter_radioButton->setEnabled(false);
    ui->input_FP_radioButton->setChecked(true);
}
void MainWindow::insertPressed(){
    if(*FP_in_finished){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Inserted data", "Floating point data has already been entered! Do you wish to delete it?",QMessageBox::Yes|QMessageBox::No);
        if(reply==QMessageBox::Yes){
            (*FP_in).clear();
            (*FP_in_finished) = false;
        }else{
            return;
        }
    }
    if(*Int_in_finished){
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Inserted data", "Interval data has already been entered! Do you wish to delete it?",QMessageBox::Yes|QMessageBox::No);
        if(reply==QMessageBox::Yes){
            (*Int_in).clear();
            (*Int_in_finished) = false;
        }else{
            return;
        }
    }
    QButtonGroup group;
    QList<QRadioButton *> allButtons = ui->input_groupBox->findChildren<QRadioButton *>();
    for(int i = 0; i < allButtons.size(); ++i)
    {
        group.addButton(allButtons[i],i);
    }
    if(group.checkedId()==1){
        IntervalInsertWindow * interval_window = new IntervalInsertWindow(this,this->Int_in,this->Int_in_finished,this->max_iterations);
        interval_window->exec();

    }else if(group.checkedId()==0){
        FPInsertWindow * fp_window = new FPInsertWindow(this,this->FP_in,this->FP_in_finished,this->max_iterations);
        fp_window->exec();

    }else{
        QMessageBox err_dialog(QMessageBox::Critical,"Input selection Error", "No input method selected!");
        err_dialog.exec();
    }

}
void MainWindow::enableWindow(){
    this->setDisabled(false);
}
void MainWindow::solvePressed(){
    QButtonGroup input_group;
    QList<QRadioButton *> input_allButtons = ui->input_groupBox->findChildren<QRadioButton *>();
    for(int i = 0; i < input_allButtons.size(); ++i)
    {
        input_group.addButton(input_allButtons[i],i);
    }

    QButtonGroup arithmetic_group;
    QList<QRadioButton *> arithmetic_allButtons = ui->arithmeticGroupBox->findChildren<QRadioButton *>();
    for(int i = 0; i < arithmetic_allButtons.size(); ++i)
    {
        arithmetic_group.addButton(arithmetic_allButtons[i],i);
    }
    qDebug() << arithmetic_group.checkedId() << " " <<input_group.checkedId()<<" "<<(*FP_in_finished);
    if(arithmetic_group.checkedId()==0 && input_group.checkedId()==0 && (*FP_in_finished)){
        //std::vector<long double> result = floatingBairstow((*this->FP_in).size()-1,*this->FP_in,*max_iterations,mincorr,zerodet);
        std::vector<std::vector<long double>> result = floatingPointBairstow((*this->FP_in).size()-1,*this->FP_in,*max_iterations,mincorr,zerodet);
        fpoutput * fpoutput_window = new fpoutput(this,result);
        fpoutput_window->exec();
        FP_in->clear();
        *FP_in_finished = false;
    }else if(arithmetic_group.checkedId()==1 && input_group.checkedId()==0 && (*FP_in_finished)){
        std::vector<interval_arithmetic::Interval<long double>> FP_to_Int_in = std::vector<interval_arithmetic::Interval<long double>>();
        for(int i = 0; i<(int)(*this->FP_in).size();i++){
            FP_to_Int_in.push_back(interval_arithmetic::Interval<long double>((*this->FP_in)[i],(*this->FP_in)[i]));
        }
        std::vector<std::vector<interval_arithmetic::Interval<long double>>> result = intervalABairstow(FP_to_Int_in.size()-1,FP_to_Int_in,*max_iterations,mincorr,zerodet);
        IntervalOutput * intervaloutput_window = new IntervalOutput(this,result);
        intervaloutput_window->exec();
        Int_in->clear();
        *Int_in_finished = false;
    }else if(arithmetic_group.checkedId()==1 && input_group.checkedId()==1 && (*Int_in_finished)){
        std::vector<std::vector<interval_arithmetic::Interval<long double>>> result = intervalABairstow((*this->Int_in).size()-1,*this->Int_in,*max_iterations,mincorr,zerodet);
        IntervalOutput * intervaloutput_window = new IntervalOutput(this,result);
        intervaloutput_window->exec();
        Int_in->clear();
        *Int_in_finished = false;
    }else{
        QMessageBox err_dialog(QMessageBox::Critical,"Input Error", "No data for selected arithmetic and input method!");
        err_dialog.exec();
    }
}
