#include "intervaloutput.h"
#include "ui_intervaloutput.h"

IntervalOutput::IntervalOutput(QWidget *parent,std::vector<interval_arithmetic::Interval<long double>> Int_out) :
    QDialog(parent),
    ui(new Ui::IntervalOutput)
{

    this->Int_out = Int_out;
    ui->setupUi(this);

    QStandardItemModel * model = new QStandardItemModel(0, 8, this);
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("RealL"));
    model->setHeaderData(1,Qt::Horizontal, QObject::tr("RealR"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("ImaginaryL"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("ImaginaryR"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Real Mid"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Imaginary Mid"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Real Width"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Imaginary Width"));
    qDebug() << ui->result_tableView;
    for(int i = 0; i< (int)Int_out.size()-1;i+=2){
        std::ostringstream streamObjRealL;
        streamObjRealL << Int_out[i].a;
        std::string strObjRealL = streamObjRealL.str();

        std::ostringstream streamObjRealR;
        streamObjRealR << Int_out[i].b;
        std::string strObjRealR = streamObjRealR.str();

        std::ostringstream streamObjImL;
        streamObjImL << Int_out[i+1].a;
        std::string strObjImL = streamObjImL.str();

        std::ostringstream streamObjImR;
        streamObjImR << Int_out[i+1].b;
        std::string strObjImR = streamObjImR.str();

        std::ostringstream streamObjRealMid;
        streamObjRealMid << Int_out[i].Mid();
        std::string strObjRealMid = streamObjRealMid.str();

        std::ostringstream streamObjImMid;
        streamObjRealMid << Int_out[i+1].Mid();
        std::string strObjImMid = streamObjImMid.str();

        std::ostringstream streamObjRealW;
        streamObjRealW << Int_out[i+1].GetWidth();
        std::string strObjRealW = streamObjRealW.str();

        std::ostringstream streamObjImW;
        streamObjImW << Int_out[i+1].GetWidth();
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
        model->appendRow(row);
    }
    ui->result_tableView->setModel(model);
}

IntervalOutput::~IntervalOutput()
{
    delete ui;
}
