#include "login.h"
#include "ui_login.h"
#include <QDebug>

LogIn::LogIn(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LogIn)
{
    ui->setupUi(this);
    userInfo.open("userInfo.txt",std::ios::app);    //必须以追加模式打开，才能不损坏原数据创建文件
    userInfo.close();
}

LogIn::~LogIn()
{
    delete ui;
}

bool LogIn::checkAccount(QString text){     //检查账号
    if(text.indexOf(" ")!=-1){
        ui->info->setText("账号不得含有空格！");
        return false;
    }
    else if(text.isEmpty()){
        ui->info->setText("账号不得为空！");
        return false;
    }
    return true;
}

bool LogIn::checkPassword(QString text){    //检查密码
    if(text.indexOf(" ")!=-1){
        ui->info->setText("密码不得含有空格！");
        return false;
    }
    else if(text.isEmpty()){
        ui->info->setText("密码不得为空！");
        return false;
    }
    return true;
}

//创建新账户
void LogIn::createAccount(QString accountNumber,QString password){
    userInfo.open("userInfo.txt",std::ios::app);                    //追加模式
    userInfo << (accountNumber+" "+password+"\n").toStdString();    //写入文件
    userInfo.close();
}

//搜索是否已有帐号
bool LogIn::searchAccount(QString accountNumber){
    userInfo.open("userInfo.txt",std::ios::in);                    //只读模式
    userInfo.peek();                                            //检测文件是否为空
    if(userInfo.eof()){
        userInfo.close();
        return false;
    }

    std::string temp;
    while(!userInfo.eof()){
        std::getline(userInfo,temp);                        //读一行（账号 密码）
        QString accountNumberExist = QString::fromStdString(temp).split(" ")[0];    //截取账号
        //qDebug() << "读到了 " << temp;
        if(accountNumberExist == accountNumber){    //查询到重复的，返回true
            userInfo.close();
            return true;
        }
        //userInfo.ignore();    //很神奇，在Qt就不需要忽略换行
        userInfo.peek();        //检测eof
    }

    userInfo.close();
    return false;           //未查询到，返回false
}


//检查登录是否成功
bool LogIn::checkLogIn(QString accountNumber,QString password){
    userInfo.open("userInfo.txt",std::ios::in);                    //只读模式
    userInfo.peek();                                            //检测文件是否为空
    if(userInfo.eof()){
        ui->info->setText("账号不存在！");
        userInfo.close();
        return false;
    }

    std::string temp;
    while(!userInfo.eof()){
        std::getline(userInfo,temp);            //读一行（账号 密码）
        QString accountNumberExist = QString::fromStdString(temp).split(" ")[0];    //截取账号
        QString passwordExist = QString::fromStdString(temp).split(" ")[1];         //截取密码
        //qDebug() << "读到了 " << temp;
        if(accountNumberExist == accountNumber){    //检测账号是否匹配，如匹配再检测密码是否匹配
            if(passwordExist == password){
                userInfo.close();
                return true;
            }
            else{
                ui->info->setText("密码错误！");
                userInfo.close();
                return false;
            }
        }
        userInfo.peek();        //检测eof
    }

    ui->info->setText("账号不存在！");
    userInfo.close();
    return false;           //未查询到，显示账号不存在，返回false
}


//点击注册 槽函数
void LogIn::on_signUpButton_clicked()
{
    QString accountNumber = ui->accountInput->text();
    QString password = ui->passwordInput->text();

    //检查账号是否合法，是否有重复账号
    if(!checkAccount(accountNumber)){
        //ui->info->setText("账号不合法！");
        return ;
    }
    else if(!checkPassword(password)){
        //ui->info->setText("密码不合法！");
        return ;
    }
    else if(searchAccount(accountNumber)){
        ui->info->setText("账号已存在！");
        return ;
    }

    else{
        createAccount(accountNumber,password);
        ui->info->setText("注册成功！");
        ui->accountInput->clear();
        ui->passwordInput->clear();
    }

}

//点击登录 槽函数
void LogIn::on_LogInButton_clicked()
{
    QString accountNumber = ui->accountInput->text();
    QString password = ui->passwordInput->text();

    //检测能否成功登录，成功则发出信号，让主窗口显示，同时关闭自身
    if(checkLogIn(accountNumber,password)){
        ui->info->clear();
        emit logInSuccess(accountNumber);
        this->close();
    }
}

