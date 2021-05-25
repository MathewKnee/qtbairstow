#ifndef INTERVALINSERTWINDOW_H
#define INTERVALINSERTWINDOW_H

#include <QDialog>
namespace Ui {
class IntervalInsertWindow;
}

class IntervalInsertWindow : public QDialog
{
    Q_OBJECT

public:
    explicit IntervalInsertWindow(QWidget * parent=nullptr);
    ~IntervalInsertWindow();

private:
    Ui::IntervalInsertWindow *ui;
};

#endif // INTERVALINSERTWINDOW_H
