#ifndef INTERVALOUTPUT_H
#define INTERVALOUTPUT_H

#include <QDialog>
#include <Interval.h>
#include <QTableView>
#include <QTableWidgetItem>
#include <sstream>
#include <QVariantList>
#include <QVariant>
#include <QDebug>
#include <QStandardItemModel>
namespace Ui {
class IntervalOutput;
}

class IntervalOutput : public QDialog
{
    Q_OBJECT

public:
    explicit IntervalOutput(QWidget *parent = nullptr,std::vector<interval_arithmetic::Interval<long double>> Int_out = std::vector<interval_arithmetic::Interval<long double>>());
    ~IntervalOutput();
    std::vector<interval_arithmetic::Interval<long double>> Int_out;
private:
    Ui::IntervalOutput *ui;
};

#endif // INTERVALOUTPUT_H
