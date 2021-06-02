#include "fpinsertwindow.h"
#include "ui_fpinsertwindow.h"

FPInsertWindow::FPInsertWindow(QWidget *parent,std::shared_ptr<std::vector<long double>> FP_in, std::shared_ptr<bool> FP_in_finished, std::shared_ptr<int> max_it) :
    QDialog(parent),
    ui(new Ui::FPInsertWindow)
{
    this->FP_in=FP_in;
    this->FP_in_finished = FP_in_finished;
    this->max_it = max_it;
    this->data_inserted = false;
    (*this->max_it) = 0;
    ui->setupUi(this);
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
    ui->coef_lineEdit->setDisabled(true);
}

FPInsertWindow::~FPInsertWindow()
{
    delete ui;
}
void FPInsertWindow::it_confirm_pressed(){
    *max_it = (ui->it_spinBox->value());
    ui->deg_spinBox->setDisabled(false);
    ui->deg_confirm->setDisabled(false);
    ui->it_spinBox->setDisabled(true);
    ui->it_confirm->setDisabled(true);
}
void FPInsertWindow::deg_confirm_pressed(){
    max_coeff = ui->deg_spinBox->value();
    for(int i =0; i<=max_coeff;i++){
        FP_in->push_back(0.0);
    }
    entered = std::vector<bool>(max_coeff+1,false);
    entered_values_str = std::vector<std::string>(max_coeff+1,"");
    ui->deg_spinBox->setDisabled(true);
    ui->deg_confirm->setDisabled(true);
    ui->next_pushButton->setDisabled(false);
    ui->coef_lineEdit->setDisabled(false);
}
void FPInsertWindow::next_pressed(){
    std::string line = ui->coef_lineEdit->text().toStdString();
    trim(line);
    if(line.compare("")==0){
        QMessageBox err_dialog(QMessageBox::Critical,"Input Error", "Nothing inserted!");
        err_dialog.exec();
    }else{
        long double coef;
        bool correct_input = false;
        try{
            coef = std::stold(line,nullptr);
            if(next_button_mode==1){
                if(abs(coef)<=1e-16){
                    correct_input=false;
                    QMessageBox err_dialog(QMessageBox::Critical,"Input Error", "a[n] can not be equal to 0!");
                    entered[current_coeff]=false;
                    err_dialog.exec();
                }else{
                    correct_input=true;
                }
            }else{
               correct_input = true;
            }

        }catch(std::exception &e){
            QMessageBox err_dialog(QMessageBox::Critical,"Input Error", "Invalid input!");
            entered[current_coeff]=false;
            err_dialog.exec();
        }
        if(correct_input){
            (*FP_in)[current_coeff] = coef;
            entered[current_coeff]=true;
            entered_values_str[current_coeff]=line;
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
                    ui->coef_lineEdit->setText(QString::fromStdString(entered_values_str[current_coeff]));
                }else{
                    ui->coef_lineEdit->clear();
                }
            }else if(next_button_mode == 1){
                ui->coef_lineEdit->setDisabled(true);
                ui->prev_pushButton->setDisabled(true);
                ui->next_pushButton->setDisabled(true);
            }

        }
    }

}
void FPInsertWindow::prev_pressed(){
    std::string line = ui->coef_lineEdit->text().toStdString();
    trim(line);
    if(line.compare("")==0){
        QMessageBox err_dialog(QMessageBox::Critical,"Input Error", "Nothing inserted!");
        err_dialog.exec();
    }else{
        long double coef;
        bool correct_input = false;
        try{
            coef = std::stold(line,nullptr);
            correct_input = true;
        }catch(std::exception &e){
            QMessageBox err_dialog(QMessageBox::Critical,"Input Error", "Invalid input!");
            entered[current_coeff]=false;
            err_dialog.exec();
        }
        if(correct_input){
            (*FP_in)[current_coeff] = coef;
            entered[current_coeff]=true;
            entered_values_str[current_coeff]=line;
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

                ui->coef_lineEdit->setText(QString::fromStdString(entered_values_str[current_coeff]));
            }else{
                ui->coef_lineEdit->clear();
            }
        }
    }
}
void FPInsertWindow::insert_data_pressed(){

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
                (*FP_in_finished) = true;
                data_inserted=true;
                close();
            }else{
                QMessageBox err_dialog(QMessageBox::Critical,"Input Error", "Coefficent missing!");
                err_dialog.exec();
            }
        }
    }
}
void FPInsertWindow::cancel_pressed(){
    close();
}
void FPInsertWindow::closeEvent(QCloseEvent *event){
    if(data_inserted){
        event->accept();
    }else{
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"Close", "Do you wish to discard all the data?",QMessageBox::Yes|QMessageBox::No);
        if(reply==QMessageBox::Yes){
            (*FP_in).clear();
            (*FP_in_finished) = false;
            event->accept();
        }else{
            event->ignore();
        }
    }

}
