#include "fpoutput.h"
#include "ui_fpoutput.h"

fpoutput::fpoutput(QWidget *parent,std::vector<std::vector<long double>> FP_out) :
    QDialog(parent),
    ui(new Ui::fpoutput)
{


    this->FP_out = FP_out;
    ui->setupUi(this);
    if(FP_out[FP_out.size()-1][1]==0){
        QStandardItemModel * roots_model = new QStandardItemModel(0, 2, this);
        roots_model->setHeaderData(0,Qt::Horizontal, QObject::tr("Real"));
        roots_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Imaginary"));

        for(int i = 0; i< ((int)FP_out.size()-1)/2;i++){
            std::ostringstream streamObjReal;
            streamObjReal << FP_out[i][0];
            std::string strObjReal = streamObjReal.str();
            std::ostringstream streamObjIm;
            streamObjIm << FP_out[i][1];
            std::string strObjIm = streamObjIm.str();

            QList<QStandardItem *> row = QList<QStandardItem *>();
            row.append(new QStandardItem(QString::fromStdString(strObjReal)));
            row.append(new QStandardItem(QString::fromStdString(strObjIm)));
            roots_model->appendRow(row);
        }
        ui->roots_tableView->setModel(roots_model);

        QStandardItemModel * values_model = new QStandardItemModel(0, 2, this);
        values_model->setHeaderData(0,Qt::Horizontal, QObject::tr("Real"));
        values_model->setHeaderData(1, Qt::Horizontal, QObject::tr("Imaginary"));
        for(int i = ((int)FP_out.size()-1)/2; i< (int)FP_out.size()-1;i++){
            std::ostringstream streamObjReal;
            streamObjReal << FP_out[i][0];
            std::string strObjReal = streamObjReal.str();
            std::ostringstream streamObjIm;
            streamObjIm << FP_out[i][1];
            std::string strObjIm = streamObjIm.str();

            QList<QStandardItem *> row = QList<QStandardItem *>();
            row.append(new QStandardItem(QString::fromStdString(strObjReal)));
            row.append(new QStandardItem(QString::fromStdString(strObjIm)));
            values_model->appendRow(row);
        }
        ui->values_tableView->setModel(values_model);
        ui->it_label->setText(QString::fromStdString("Number of iterations: "+std::to_string((int)FP_out[FP_out.size()-1][0])));
    }else if(FP_out[FP_out.size()-1][1]==1){
        QMessageBox err_dialog(QMessageBox::Critical,"Error!", "Wrong n, max_it, mincorr or zerodet!");
        err_dialog.exec();
    }else if(FP_out[FP_out.size()-1][1]==2){
        QMessageBox err_dialog(QMessageBox::Critical,"Error!", "Singular or almost singular system of equations encountered!");
        err_dialog.exec();
    }else if(FP_out[FP_out.size()-1][1]==3){
        QMessageBox err_dialog(QMessageBox::Critical,"Error!", "Not enough iterations to achieve desired precision!");
        err_dialog.exec();
    }

}

fpoutput::~fpoutput()
{
    delete ui;
}
