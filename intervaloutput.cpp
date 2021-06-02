#include "intervaloutput.h"
#include "ui_intervaloutput.h"

IntervalOutput::IntervalOutput(QWidget *parent,std::vector<std::vector<interval_arithmetic::Interval<long double>>> Int_out) :
    QDialog(parent),
    ui(new Ui::IntervalOutput)
{

    this->Int_out = Int_out;
    ui->setupUi(this);
    if((int)Int_out[Int_out.size()-1][1].a==0){
    QStandardItemModel * roots_model = new QStandardItemModel(0, 8, this);
    roots_model->setHeaderData(0,Qt::Horizontal, QObject::tr("RealL"));
    roots_model->setHeaderData(1,Qt::Horizontal, QObject::tr("RealR"));
    roots_model->setHeaderData(2, Qt::Horizontal, QObject::tr("ImaginaryL"));
    roots_model->setHeaderData(3, Qt::Horizontal, QObject::tr("ImaginaryR"));
    roots_model->setHeaderData(4, Qt::Horizontal, QObject::tr("Real Mid"));
    roots_model->setHeaderData(5, Qt::Horizontal, QObject::tr("Imaginary Mid"));
    roots_model->setHeaderData(6, Qt::Horizontal, QObject::tr("Real Width"));
    roots_model->setHeaderData(7, Qt::Horizontal, QObject::tr("Imaginary Width"));
    for(int i = 0; i< ((int)Int_out.size()-1)/2;i++){
        std::ostringstream streamObjRealL;
        streamObjRealL << Int_out[i][0].a;
        std::string strObjRealL = streamObjRealL.str();

        std::ostringstream streamObjRealR;
        streamObjRealR << Int_out[i][0].b;
        std::string strObjRealR = streamObjRealR.str();

        std::ostringstream streamObjImL;
        streamObjImL << Int_out[i][1].a;
        std::string strObjImL = streamObjImL.str();

        std::ostringstream streamObjImR;
        streamObjImR << Int_out[i][1].b;
        std::string strObjImR = streamObjImR.str();

        std::ostringstream streamObjRealMid;
        streamObjRealMid << Int_out[i][0].Mid();
        std::string strObjRealMid = streamObjRealMid.str();

        std::ostringstream streamObjImMid;
        streamObjImMid << Int_out[i][1].Mid();
        std::string strObjImMid = streamObjImMid.str();

        std::ostringstream streamObjRealW;
        streamObjRealW << Int_out[i][0].GetWidth();
        std::string strObjRealW = streamObjRealW.str();

        std::ostringstream streamObjImW;
        streamObjImW << Int_out[i][1].GetWidth();
        std::string strObjImW = streamObjImW.str();

        QList<QStandardItem *> row = QList<QStandardItem *>();
        row.append(new QStandardItem(QString::fromStdString(strObjRealL)));
        row.append(new QStandardItem(QString::fromStdString(strObjRealR)));
        row.append(new QStandardItem(QString::fromStdString(strObjImL)));
        row.append(new QStandardItem(QString::fromStdString(strObjImR)));
        row.append(new QStandardItem(QString::fromStdString(strObjRealMid)));
        row.append(new QStandardItem(QString::fromStdString(strObjImMid)));
        row.append(new QStandardItem(QString::fromStdString(strObjRealW)));
        row.append(new QStandardItem(QString::fromStdString(strObjImW)));
        roots_model->appendRow(row);
    }
    ui->roots_tableView->setModel(roots_model);

    QStandardItemModel * values_model = new QStandardItemModel(0, 8, this);
    values_model->setHeaderData(0,Qt::Horizontal, QObject::tr("RealL"));
    values_model->setHeaderData(1,Qt::Horizontal, QObject::tr("RealR"));
    values_model->setHeaderData(2, Qt::Horizontal, QObject::tr("ImaginaryL"));
    values_model->setHeaderData(3, Qt::Horizontal, QObject::tr("ImaginaryR"));
    values_model->setHeaderData(4, Qt::Horizontal, QObject::tr("Real Mid"));
    values_model->setHeaderData(5, Qt::Horizontal, QObject::tr("Imaginary Mid"));
    values_model->setHeaderData(6, Qt::Horizontal, QObject::tr("Real Width"));
    values_model->setHeaderData(7, Qt::Horizontal, QObject::tr("Imaginary Width"));
    for(int i = ((int)Int_out.size()-1)/2; i< ((int)Int_out.size()-1);i++){
        std::ostringstream streamObjRealL;
        streamObjRealL << Int_out[i][0].a;
        std::string strObjRealL = streamObjRealL.str();

        std::ostringstream streamObjRealR;
        streamObjRealR << Int_out[i][0].b;
        std::string strObjRealR = streamObjRealR.str();

        std::ostringstream streamObjImL;
        streamObjImL << Int_out[i][1].a;
        std::string strObjImL = streamObjImL.str();

        std::ostringstream streamObjImR;
        streamObjImR << Int_out[i][1].b;
        std::string strObjImR = streamObjImR.str();

        std::ostringstream streamObjRealMid;
        streamObjRealMid << Int_out[i][0].Mid();
        std::string strObjRealMid = streamObjRealMid.str();

        std::ostringstream streamObjImMid;
        streamObjImMid << Int_out[i][1].Mid();
        std::string strObjImMid = streamObjImMid.str();

        std::ostringstream streamObjRealW;
        streamObjRealW << Int_out[i][0].GetWidth();
        std::string strObjRealW = streamObjRealW.str();

        std::ostringstream streamObjImW;
        streamObjImW << Int_out[i][1].GetWidth();
        std::string strObjImW = streamObjImW.str();

        QList<QStandardItem *> row = QList<QStandardItem *>();
        row.append(new QStandardItem(QString::fromStdString(strObjRealL)));
        row.append(new QStandardItem(QString::fromStdString(strObjRealR)));
        row.append(new QStandardItem(QString::fromStdString(strObjImL)));
        row.append(new QStandardItem(QString::fromStdString(strObjImR)));
        row.append(new QStandardItem(QString::fromStdString(strObjRealMid)));
        row.append(new QStandardItem(QString::fromStdString(strObjImMid)));
        row.append(new QStandardItem(QString::fromStdString(strObjRealW)));
        row.append(new QStandardItem(QString::fromStdString(strObjImW)));
        values_model->appendRow(row);
    }
    ui->values_tableView->setModel(values_model);
    ui->it_label->setText(QString::fromStdString("Number of iterations: "+std::to_string((int)Int_out[Int_out.size()-1][0].a)));
    }else if((int)Int_out[Int_out.size()-1][1].a==1){
        QMessageBox err_dialog(QMessageBox::Critical,"Error!", "Wrong n, max_it, mincorr or zerodet!");
        err_dialog.exec();
    }else if((int)Int_out[Int_out.size()-1][1].a==2){
        QMessageBox err_dialog(QMessageBox::Critical,"Error!", "Singular or almost singular system of equations encountered!");
        err_dialog.exec();
    }else if((int)Int_out[Int_out.size()-1][1].a==3){
        QMessageBox err_dialog(QMessageBox::Critical,"Error!", "Not enough iterations to achieve desired precision!");
        err_dialog.exec();
    }
}

IntervalOutput::~IntervalOutput()
{
    delete ui;
}
