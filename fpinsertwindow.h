#ifndef FPINSERTWINDOW_H
#define FPINSERTWINDOW_H

#include <QDialog>
#include <QMessageBox>
#include <string>
#include <QDebug>
#include <QString>
#include <string_utils.h>
#include <QCloseEvent>
namespace Ui {
class FPInsertWindow;
}

class FPInsertWindow : public QDialog
{
    Q_OBJECT

protected:
    void closeEvent(QCloseEvent *event);
public:
    explicit FPInsertWindow(QWidget *parent = nullptr,std::shared_ptr<std::vector<long double>> FP_in = nullptr,std::shared_ptr<bool> FP_in_finished = nullptr,std::shared_ptr<int> max_it=nullptr);
    ~FPInsertWindow();
    std::shared_ptr<std::vector<long double>> FP_in;
    std::shared_ptr<bool> FP_in_finished;
    std::shared_ptr<int> max_it;
private:
    Ui::FPInsertWindow *ui;
    bool it_confirmed;
    bool deg_confirmed;
    bool data_inserted;
    std::vector<bool> entered;
    std::vector<std::string> entered_values_str;
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

#endif // FPINSERTWINDOW_H
