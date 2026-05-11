#ifndef ERROR_H
#define ERROR_H

#include <QDialog>
#include <QString>

namespace Ui {
class Error;
}

class Error : public QDialog
{
    Q_OBJECT

public:
    explicit Error(QWidget *parent = nullptr);
    ~Error();

    void setLabel(QString label);   //设置错误提示

private slots:
    void on_button_clicked();

private:
    Ui::Error *ui;
};

#endif // ERROR_H
