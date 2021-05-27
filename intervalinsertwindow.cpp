#include "intervalinsertwindow.h"
#include "ui_intervalinsertwindow.h"

IntervalInsertWindow::IntervalInsertWindow(QWidget *parent,std::shared_ptr<std::vector<interval_arithmetic::Interval<long double>>> Int_in ,std::shared_ptr<bool> Int_in_finished ,std::shared_ptr<int> max_it) :
    QDialog(parent),
    ui(new Ui::IntervalInsertWindow)
{
    ui->setupUi(this);
    this->Int_in=Int_in;
    this->Int_in_finished = Int_in_finished;
    this->max_it = max_it;
    this->data_inserted = false;
    (*this->max_it) = 0;
    connect(ui->it_confirm, SIGNAL(released()), this, SLOT(it_confirm_pressed()));
    connect(ui->deg_confirm, SIGNAL(released()), this, SLOT(deg_confirm_pressed()));
    connect(ui->next_pushButton, SIGNAL(released()), this, SLOT(next_pressed()));
    connect(ui->prev_pushButton, SIGNAL(released()), this, SLOT(prev_pressed()));
    connect(ui->insert_pushButton, SIGNAL(released()), this, SLOT(insert_data_pressed()));
    connect(ui->cancel_pushButton, SIGNAL(released()), this, SLOT(cancel_pressed()));
    ui->deg_spinBox->setDisabled(true);
    ui->deg_confirm->setDisabled(true);
    ui->next_pushButton->setDisabled(true);
    ui->prev_pushButton->setDisabled(true);
    ui->coef_lineEditL->setDisabled(true);
    ui->coef_lineEditR->setDisabled(true);
}

IntervalInsertWindow::~IntervalInsertWindow()
{
    delete ui;
}
void IntervalInsertWindow::it_confirm_pressed(){
    *max_it = (ui->it_spinBox->value());
    ui->deg_spinBox->setDisabled(false);
    ui->deg_confirm->setDisabled(false);
    ui->it_spinBox->setDisabled(true);
    ui->it_confirm->setDisabled(true);
}
void IntervalInsertWindow::deg_confirm_pressed(){
    max_coeff = ui->deg_spinBox->value();
    for(int i =0; i<=max_coeff;i++){
        Int_in->push_back(interval_arithmetic::Interval<long double>(0.0,0.0));
    }
    entered = std::vector<bool>(max_coeff+1,false);
    entered_values_strL = std::vector<std::string>(max_coeff+1,"");
    entered_values_strR = std::vector<std::string>(max_coeff+1,"");
    ui->deg_spinBox->setDisabled(true);
    ui->deg_confirm->setDisabled(true);
    ui->next_pushButton->setDisabled(false);
    ui->coef_lineEditL->setDisabled(false);
    ui->coef_lineEditR->setDisabled(false);
}
void IntervalInsertWindow::next_pressed(){
    std::string lineL = ui->coef_lineEditL->text().toStdString();
    std::string lineR = ui->coef_lineEditR->text().toStdString();
    trim(lineL);
    trim(lineR);
    if(lineL.compare("")==0 || lineR.compare("")==0){
        QMessageBox err_dialog(QMessageBox::Critical,"Input Error", "Nothing inserted!");
        err_dialog.exec();
    }else{
        long double coefL;
        long double coefR;
        bool correct_input = false;
        try{
            coefL = std::stold(lineL,nullptr);
            coefR = std::stold(lineR,nullptr);
            if(coefL > coefR){
                QMessageBox err_dialog(QMessageBox::Critical,"Input Error", "Invalid input! Left boundary larger than right boundary");
                entered[current_coeff]=false;
                err_dialog.exec();
            }else{
                correct_input = true;
            }

        }catch(std::exception &e){
            QMessageBox err_dialog(QMessageBox::Critical,"Input Error", "Invalid input!");
            entered[current_coeff]=false;
            err_dialog.exec();
        }
        if(correct_input){
            (*Int_in)[current_coeff] = interval_arithmetic::Interval<long double>(coefL,coefR);
            entered[current_coeff]=true;
            entered_values_strL[current_coeff]=lineL;
            entered_values_strR[current_coeff]=lineR;
            if(next_button_mode == 0){
                current_coeff++;
                if(current_coeff==max_coeff){
                    ui->next_pushButton->setText("Confirm");
                    next_button_mode = 1;
                }
                if(current_coeff!=min_coeff){
                    ui->prev_pushButton->setDisabled(false);
                }
                std::string new_label = "Coefficient a["+std::to_string(current_coeff) + "]";
                ui->coef_label->setText(QString::fromStdString(new_label));
                if(entered[current_coeff]){
                    ui->coef_lineEditL->setText(QString::fromStdString(entered_values_strL[current_coeff]));
                    ui->coef_lineEditR->setText(QString::fromStdString(entered_values_strR[current_coeff]));
                }else{
                    ui->coef_lineEditL->clear();
                    ui->coef_lineEditR->clear();
                }
            }else if(next_button_mode == 1){
                ui->coef_lineEditL->setDisabled(true);
                ui->coef_lineEditR->setDisabled(true);
                ui->prev_pushButton->setDisabled(true);
                ui->next_pushButton->setDisabled(true);
            }

        }
    }

}
void IntervalInsertWindow::prev_pressed(){
    std::string lineL = ui->coef_lineEditL->text().toStdString();
    std::string lineR = ui->coef_lineEditR->text().toStdString();
    trim(lineL);
    trim(lineR);
    if(lineL.compare("")==0 || lineR.compare("")==0){
        QMessageBox err_dialog(QMessageBox::Critical,"Input Error", "Nothing inserted!");
        err_dialog.exec();
    }else{
        long double coefL;
        long double coefR;
        bool correct_input = false;
        try{
            coefL = std::stold(lineL,nullptr);
            coefR = std::stold(lineR,nullptr);
            if(coefL > coefR){
                QMessageBox err_dialog(QMessageBox::Critical,"Input Error", "Invalid input! Left boundary larger than right boundary");
                entered[current_coeff]=false;
                err_dialog.exec();
            }else{
                correct_input = true;
            }

        }catch(std::exception &e){
            QMessageBox err_dialog(QMessageBox::Critical,"Input Error", "Invalid input!");
            entered[current_coeff]=false;
            err_dialog.exec();
        }
        if(correct_input){
            (*Int_in)[current_coeff] = interval_arithmetic::Interval<long double>(coefL,coefR);
            entered[current_coeff]=true;
            entered_values_strL[current_coeff]=lineL;
            entered_values_strR[current_coeff]=lineR;
            if(next_button_mode == 0){
                current_coeff--;
                if(current_coeff==min_coeff){
                    ui->prev_pushButton->setDisabled(true);
                }
                if(current_coeff!=max_coeff){
                    ui->next_pushButton->setDisabled(false);
                    ui->next_pushButton->setText("Next");
                    next_button_mode = 0;
                }
                std::string new_label = "Coefficient a["+std::to_string(current_coeff) + "]";
                ui->coef_label->setText(QString::fromStdString(new_label));
                if(entered[current_coeff]){
                    ui->coef_lineEditL->setText(QString::fromStdString(entered_values_strL[current_coeff]));
                    ui->coef_lineEditR->setText(QString::fromStdString(entered_values_strR[current_coeff]));
                }else{
                    ui->coef_lineEditL->clear();
                    ui->coef_lineEditR->clear();
                }
            }

        }
    }

}
void IntervalInsertWindow::insert_data_pressed(){

    if(*max_it == 0){
        QMessageBox err_dialog(QMessageBox::Critical,"Input Error", "Max iterations was not entered");
        err_dialog.exec();
    }else{
        if(max_coeff ==0){
            QMessageBox err_dialog(QMessageBox::Critical,"Input Error", "Polynomial degree was not entered");
            err_dialog.exec();
        }else{
            bool check = true;
            for(int i =0;i<=max_coeff;i++){
                check &= entered[i];
            }
            if(check){
                (*Int_in_finished) = true;
                data_inserted=true;
                close();
            }else{
                QMessageBox err_dialog(QMessageBox::Critical,"Input Error", "Coefficent missing!");
                err_dialog.exec();
            }
        }
    }
}
void IntervalInsertWindow::cancel_pressed(){
    close();
}
void IntervalInsertWindow::closeEvent(QCloseEvent *event){
    if(data_inserted){
        event->accept();
    }else{
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Close", "Do you wish to discard all the data?",QMessageBox::Yes|QMessageBox::No);
        if(reply==QMessageBox::Yes){
            (*Int_in).clear();
            (*Int_in_finished) = false;
            event->accept();
        }else{
            event->ignore();
        }
    }

}
