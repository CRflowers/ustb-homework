#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <fstream>

namespace Ui {
class LogIn;
}

class LogIn : public QDialog
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = nullptr);
    ~LogIn();

    bool searchAccount(QString accountNumber);                      //查询账户
    void createAccount(QString accountNumber,QString password);     //创建账户

    bool checkAccount(QString text);                //检查账号合法性（不得为空或含有空格）
    bool checkPassword(QString text);                //检查密码合法性（不得为空或含有空格）
    bool checkLogIn(QString accountNumber,QString password);   //检查登录是否成功

signals:
    void logInSuccess(QString accountNumber);

private slots:
    void on_signUpButton_clicked();

    void on_LogInButton_clicked();

private:
    Ui::LogIn *ui;

    std::fstream userInfo;
};

#endif // LOGIN_H
