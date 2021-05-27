#ifndef INTERVALINSERTWINDOW_H
#define INTERVALINSERTWINDOW_H

#include <QDialog>
#include <Interval.h>
#include <QMessageBox>
#include <string>
#include <QDebug>
#include <QString>
#include <string_utils.h>
#include <QCloseEvent>
namespace Ui {
class IntervalInsertWindow;
}

class IntervalInsertWindow : public QDialog
{
    Q_OBJECT
protected:
    void closeEvent(QCloseEvent *event);
public:
    explicit IntervalInsertWindow(QWidget * parent=nullptr,std::shared_ptr<std::vector<interval_arithmetic::Interval<long double>>> Int_in = nullptr,std::shared_ptr<bool> Int_in_finished = nullptr,std::shared_ptr<int> max_it=nullptr);
    ~IntervalInsertWindow();
    std::shared_ptr<std::vector<interval_arithmetic::Interval<long double>>> Int_in;
    std::shared_ptr<bool> Int_in_finished;
    std::shared_ptr<int> max_it;
private:
    Ui::IntervalInsertWindow *ui;
    bool it_confirmed;
    bool deg_confirmed;
    bool data_inserted;
    std::vector<bool> entered;
    std::vector<std::string> entered_values_strL;
    std::vector<std::string> entered_values_strR;
    int min_coeff = 0;
    int max_coeff = 0;
    int current_coeff = 0;
    int next_button_mode = 0;
private slots:
    void it_confirm_pressed();
    void deg_confirm_pressed();
    void next_pressed();
    void prev_pressed();
    void insert_data_pressed();
    void cancel_pressed();
};

#endif // INTERVALINSERTWINDOW_H
