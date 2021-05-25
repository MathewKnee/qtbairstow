#include "fpoutput.h"
#include "ui_fpoutput.h"

fpoutput::fpoutput(QWidget *parent,std::vector<long double> FP_out) :
    QDialog(parent),
    ui(new Ui::fpoutput)
{


    this->FP_out = FP_out;
    ui->setupUi(this);
    //QTableView * view = ui->findChild<QTableView *>("result_tableView");
    QStandardItemModel * model = new QStandardItemModel(0, 2, this);
    model->setHeaderData(0,Qt::Horizontal, QObject::tr("Real"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Imaginary"));
    qDebug() << ui->result_tableView;
    for(int i = 0; i< (int)FP_out.size()-1;i+=2){
        std::ostringstream streamObjReal;
        streamObjReal << FP_out[i];
        std::string strObjReal = streamObjReal.str();
        std::ostringstream streamObjIm;
        streamObjIm << FP_out[i+1];
        std::string strObjIm = streamObjIm.str();

        QList<QStandardItem *> row = QList<QStandardItem *>();
        row.append(new QStandardItem(QString::fromStdString(strObjReal)));
        row.append(new QStandardItem(QString::fromStdString(strObjIm)));
        model->appendRow(row);
    }
    ui->result_tableView->setModel(model);
}

fpoutput::~fpoutput()
{
    delete ui;
}
