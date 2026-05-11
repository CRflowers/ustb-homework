#include "error.h"
#include "ui_error.h"

Error::Error(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Error)
{
    ui->setupUi(this);
}

Error::~Error()
{
    delete ui;
}

void Error::on_button_clicked()
{
    this->close();
}

void Error::setLabel(QString label){
    ui->label->setText(label);
}
