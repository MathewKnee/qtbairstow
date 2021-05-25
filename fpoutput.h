#ifndef FPOUTPUT_H
#define FPOUTPUT_H

#include <QDialog>
#include <QTableView>
#include <QTableWidgetItem>
#include <sstream>
#include <QVariantList>
#include <QVariant>
#include <QDebug>
#include <QStandardItemModel>
namespace Ui {
class fpoutput;
}

class fpoutput : public QDialog
{
    Q_OBJECT

public:
    explicit fpoutput(QWidget *parent = nullptr,std::vector<long double> FP_out = std::vector<long double>());
    ~fpoutput();
    std::vector<long double> FP_out;

private:
    Ui::fpoutput *ui;
};

#endif // FPOUTPUT_H
