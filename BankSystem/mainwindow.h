#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include "error.h"
#include <vector>
#include <fstream>
#include "account.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void showLogInWidget();         //显示登录窗口
    void operate(QString op);       //处理QString操作的函数
    void preOperate();              //预处理
    bool searchAccountNumber(QString accountNumber);//搜索是否已有帐号

private:
    Ui::MainWindow *ui;
    LogIn loginWidget;              //登录类控件，管理注册与登录
    QString bankAccountNumber;      //当前登录的账户名
    Error errorDialog;              //错误弹窗
    Date date{2008,11,1};                      //用户账户的当前时间
    std::vector<Account*> accounts; //用户的账户数组，初始个数为0
    std::fstream commands;          //用户操作/命令储存的文件


private slots:
    void showWithAccount(QString accountNumber);

    void on_exit_clicked();
    void on_accountForm_currentTextChanged(const QString &arg1);
    void on_createAccountButton_clicked();
    void on_searchAccountNumberButton_clicked();
    void on_depositButton_clicked();
    void on_withdrawButton_clicked();
    void on_changeDayButton_clicked();
    void on_nextDay_clicked();
    void on_nextMonth_clicked();
    void on_changeDateButton_clicked();

    //用于显示账户信息的槽函数
    void accountRecordSlot(Date _date,QString _id,double _amount,double _balance,QString _desc);
};
#endif // MAINWINDOW_H
