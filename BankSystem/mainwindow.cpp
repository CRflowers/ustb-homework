#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "error.h"
#include "account.h"
#include "savingsaccount.h"
#include "creditaccount.h"
#include "date.h"

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QDir>
#include <QStringList>
#include <QTreeWidgetItem>
#include <QStringList>
#include <QDebug>

bool isNumber(const QString& text){
    bool ok;
    text.toDouble(&ok);
    return ok || text.toInt(&ok);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //连接信号与槽
    connect(&loginWidget,&LogIn::logInSuccess,this,&MainWindow::showWithAccount);   //登陆成功信号

    //设置初始列宽
    for(int i=0;i<4;i++){
        ui->accountRecord->setColumnWidth(i,130);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}


//显示登录界面
void MainWindow::showLogInWidget(){
    loginWidget.show();
}


//接收到登录成功信号，保存账户名，显示自身，进行预操作，追加模式创建/打开命令文件
void MainWindow::showWithAccount(QString accountNumber){
    ui->welcome->setText("用户"+accountNumber+"，欢迎使用银行系统！");

    //保存账户名
    bankAccountNumber = accountNumber;

    //使用QDir构建commands目录，以账号名为文件名，存储不同用户的操作
    QDir directory("./");
    if(!directory.exists("./commands")){
        directory.mkdir("./commands");
    }
    std::string path = "./commands/"+(bankAccountNumber.toStdString())+".txt";
    commands.open(path,std::ios::app);
    commands.close();

    //预操作
    this->preOperate();

    //更新一下日期
    ui->date->setText("现在是"+date.showText());

    this->show();
}


//点击退出登录，清除信息，返回登录界面
void MainWindow::on_exit_clicked()
{
    //清除信息
    date.changeDate(2008,11,1);      //用户账户的当前时间
    accounts.clear();               //用户的账户数组清除

    //清除控件显示
    ui->accountInfo->clear();
    ui->accountRecord->clear();
    ui->createAccountNumber->clear();
    ui->accountForm->setCurrentIndex(0);
    ui->rate->clear();
    ui->credit->clear();
    ui->fee->clear();

    ui->operateAccountNumber->clear();
    ui->amount->clear();
    ui->desc->clear();

    ui->dayInput->clear();
    ui->changeDateInput->clear();

    //关闭窗口
    this->close();
    loginWidget.show();

}


//执行操作 处理用户信号转换为的字符串，但是不写入文件，因为初始加载上次进度需要用这个函数
void MainWindow::operate(QString op){
    char cmd;           //操作类型
    //显示日期   总金额?
    //date.show();
    //cout << "\tTotal: " << Account::getTotal() << "\tcommand> ";
    char type;
    int index, day;
    double amount, credit, rate, fee;
    string id, desc;
    Account* account;
    Date date1, date2;

    //分割
    QStringList opLst = op.split(" ");
    cmd = op.toStdString()[0];

    //分类型操作
    switch (cmd) {
    case 'a'://增加账户
        type = opLst[2].toStdString()[0];
        id = opLst[1].toStdString();
        if(type == 's'){
            rate = opLst[3].toDouble();
            account = new SavingsAccount(this->date, id, rate);   //创建储蓄账户
        }
        else if(type == 'c'){
            credit = opLst[3].toDouble();
            rate = opLst[4].toDouble();
            fee = opLst[5].toDouble();
            account = new CreditAccount(this->date, id, credit, rate, fee);   //创建信用账户
        }
        this->accounts.push_back(account);          //加入账户容器

        //重要！！连接这个账户与槽函数！不然后续没办法接收日期改变
        connect(account,&Account::accountRecordSignal,this,&MainWindow::accountRecordSlot);

        //添加到下拉栏
        ui->operateAccountNumber->addItem(QString::fromStdString(id));

        break;

    case 'd'://存入现金,index是账户序列
        index = opLst[1].toInt();
        amount = opLst[2].toDouble();
        desc = opLst[3].toStdString();
        this->accounts[index]->deposit(this->date, amount, desc);
        break;

    case 'w'://取出现金
        index = opLst[1].toInt();
        amount = opLst[2].toDouble();
        desc = opLst[3].toStdString();
        this->accounts[index]->withdraw(this->date, amount, desc);
        break;

    /*展示方式之后改
    case 's'://查询各账户信息，在信息展示处显示
        for (size_t i = 0; i < accounts.size(); i++) {
            cout << "[" << i << "] ";
            accounts[i]->show();
        }
        break;
    */

    case 'c'://改变日期
        day = opLst[1].toInt();
        if(day < date.getDay()){
            errorDialog.setLabel("不得设置日期为当前日期之前！");
            errorDialog.exec();
            return ;
        }
        else if (day > date.getMaxDay()){
            errorDialog.setLabel("日期不合法！");
            errorDialog.exec();
            return ;
        }
        this->date = Date(date.getYear(), date.getMonth(), day);
        break;

    case 'n'://进入下个月
        if (date.getMonth() == 12){
            date = Date(date.getYear() + 1, 1, 1);
        }
        else{
            date = Date(date.getYear(), date.getMonth() + 1, 1);
        }
        for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)
            (*iter)->settle(date);
        break;

    case 'q'://查询一段时间内的账目
        date1 = Date::read();
        commands << date1.getYear() << '/' << date1.getMonth()
                 << '/' << date1.getDay() << ' ';

        date2 = Date::read();
        commands << date2.getYear() << '/' << date2.getMonth()
                 << '/' << date2.getDay();

        Account::query(date1, date2);
        break;
    }
}


//预处理文件保存的内容
void MainWindow::preOperate(){
    //读方式打开文件
    std::string path = "./commands/"+(bankAccountNumber.toStdString())+".txt";
    commands.open(path,std::ios::in);

    //定义命令
    string _command;
    QString command("a " + ui->createAccountNumber->text() + " ");

    commands.peek();
    while(!commands.eof()){
        //每次读一行
        std::getline(commands,_command);
        command = QString::fromStdString(_command);
        //qDebug() << command;

        //调用函数
        this->operate(command);

        //检测eof
        commands.peek();
    }
    commands.close();
}


//查找账户是否已存在
bool MainWindow::searchAccountNumber(QString accountNumber){
    for(vector<Account*>::iterator iter = accounts.begin();iter != accounts.end();++iter){
        if((*iter)->getId() == accountNumber.toStdString()){
            return true;
        }
    }
    return false;
}


//创建账户 下拉栏选择账户类型，控制后续不需要填写的账户属性的锁定
void MainWindow::on_accountForm_currentTextChanged(const QString &arg1)
{
    if(arg1 == "储蓄卡账户"){
        ui->rate->setEnabled(true);
        ui->rate->clear();
        ui->credit->setEnabled(false);
        ui->credit->setText("--------");
        ui->fee->setEnabled(false);
        ui->fee->setText("--------");
    }
    else if(arg1 == "信用卡账户"){
        ui->rate->setEnabled(true);        //草信用卡账户需要利息的利率，我忘了
        ui->rate->clear();
        ui->credit->clear();
        ui->credit->setEnabled(true);
        ui->fee->clear();
        ui->fee->setEnabled(true);

    }
}


//创建账户 按钮点击
void MainWindow::on_createAccountButton_clicked()
{
    //定义错误提示
    QString label("");

    //先检查信息是否填写完全
    if(ui->createAccountNumber->text().isEmpty()){
        label = "账号不得为空！";
    }
    else if(ui->createAccountNumber->text().indexOf(" ")!=-1){
        label = "账号不得含有空格！";
    }
    else if(searchAccountNumber(ui->createAccountNumber->text())){
        label = "账号已存在！";
    }
    else if(ui->accountForm->currentIndex() == 0){
        label = "请选择账户类型！";
    }
    else if(ui->rate->text().isEmpty()){
        label = "未输入年利率！";
    }
    else if(ui->credit->text().isEmpty()){
        label= "未输入透支额度！";
    }
    else if(ui->fee->text().isEmpty()){
        label = "未输入年费！";
    }

    //弹出弹窗
    if(!label.isEmpty()){
        errorDialog.setLabel((label));
        errorDialog.exec();
        return ;
    }

    //信息完整，写入文件，并调用操作函数创建账户，注意信用卡格式是"c" id credit rate fee
    std::string path = "./commands/"+(bankAccountNumber.toStdString())+".txt";
    commands.open(path,std::ios::app);

    QString command("a " + ui->createAccountNumber->text() + " ");
    if(ui->accountForm->currentText() == "储蓄卡账户"){
        command += "s " + ui->rate->text();
    }
    else if(ui->accountForm->currentText() == "信用卡账户"){
        command += "c " + ui->credit->text() + " " +
                    ui->rate->text() + " " + ui->fee->text();
    }

    //写入文件
    commands << command.toStdString() << "\n";
    commands.close();
    //调用函数
    this->operate(command);

    //显示创建成功
    QString showText("成功创建"+ui->accountForm->currentText()+ui->createAccountNumber->text()+"！");
    ui->accountInfo->append(showText);
}


//点击按钮 查询账户信息
void MainWindow::on_searchAccountNumberButton_clicked()
{
    QString text;
    if(accounts.empty()){
        errorDialog.setLabel("您还没有账户哦，快创建一个吧！\n少女祈祷中...");
        errorDialog.exec();
        return ;
    }
    //遍历所有账户，输出信息
    for(vector<Account*>::iterator iter = accounts.begin();iter != accounts.end();++iter){
        text = (*iter)->showText();
        ui->accountInfo->append(text);
    }
    //总计 突然发现这个是整个银行的总计，不给用户看了还是）
    //double total;
    //total = Account::getTotal();
    //ui->accountInfo->append("总计余额："+QString::number(total));
}


//点击按钮 存钱
void MainWindow::on_depositButton_clicked()
{
    //定义变量、错误提示
    int accountIndex = ui->operateAccountNumber->currentIndex();
    QString _accountNumber = ui->operateAccountNumber->currentText();
    QString _amount = ui->amount->text();
    QString _desc = ui->desc->toPlainText();
    QString label("");

    //先检查信息是否填写完全，行为是否合法
    if(_accountNumber.isEmpty()){
        label = "账号不得为空！";
    }
    else if(_amount.isEmpty()){
        label = "未输入金额！";
    }
    else if(!isNumber(_amount)){
        label = "请输入数字金额！";
    }
    else if(_amount.toDouble()<=0){
        label = "请输入正数金额！";
    }

    //弹出弹窗
    if(!label.isEmpty()){
        errorDialog.setLabel((label));
        errorDialog.exec();
        return ;
    }

    //信息完整，写入文件，并调用操作函数存款
    std::string path = "./commands/"+(bankAccountNumber.toStdString())+".txt";
    commands.open(path,std::ios::app);

    //操作字符串
    if(_desc.isEmpty()){
        _desc = "------";
    }
    QString command("d " + QString::number(accountIndex) + " " + _amount + " " + _desc);


    //写入文件
    commands << command.toStdString() << "\n";
    commands.close();
    //调用函数
    this->operate(command);
    //显示这笔帐目交给函数来完成
}


//点击按钮 取钱
void MainWindow::on_withdrawButton_clicked()
{
    //定义变量、错误提示
    int accountIndex = ui->operateAccountNumber->currentIndex();
    QString _accountNumber = ui->operateAccountNumber->currentText();
    QString _amount = ui->amount->text();
    QString _desc = ui->desc->toPlainText();
    QString label("");
    Account* account = accounts[accountIndex];

    //先检查信息是否填写完全，行为是否合法
    if(_accountNumber.isEmpty()){
        label = "账号不得为空！";
    }
    else if(_amount.isEmpty()){
        label = "未输入金额！";
    }
    else if(!isNumber(_amount)){
        label = "请输入数字金额！";
    }
    else if(_amount.toDouble()<=0){
        label = "请输入正数金额！";
    }
    else if(!account->testWithdraw(_amount.toDouble())){
        if(account->getAccountForm()=="savingsAccount"){
            label = "余额不足！";
        }
        else if(account->getAccountForm()=="creditAccount"){
            label = "可用额度不足！";
        }
    }

    //弹出弹窗
    if(!label.isEmpty()){
        errorDialog.setLabel((label));
        errorDialog.exec();
        return ;
    }

    //信息完整，写入文件，并调用操作函数取款
    std::string path = "./commands/"+(bankAccountNumber.toStdString())+".txt";
    commands.open(path,std::ios::app);

    //操作字符串
    if(_desc.isEmpty()){
        _desc = "------";
    }
    QString command("w " + QString::number(accountIndex) + " " + _amount + " " + _desc);


    //写入文件
    commands << command.toStdString() << "\n";
    commands.close();
    //调用函数
    this->operate(command);
    //显示这笔帐目交给函数来完成
}


//按键 更改日期
void MainWindow::on_changeDayButton_clicked()
{
    //定义变量、错误提示
    int day = ui->dayInput->text().toInt();
    QString label("");

    //先检查信息是否填写完全，行为是否合法
    if(day <= 0){
        label = "请输入正数日期！";
    }
    else if(day < date.getDay()){
        label = "不能移动到以前的日期！";
    }
    else if(day > date.getMaxDay()){
        label = "日期不合法！";
    }

    //弹出弹窗
    if(!label.isEmpty()){
        errorDialog.setLabel((label));
        errorDialog.exec();
        return ;
    }

    //信息完整，写入文件，并调用操作函数改变日期
    std::string path = "./commands/"+(bankAccountNumber.toStdString())+".txt";
    commands.open(path,std::ios::app);

    //操作字符串
    QString command("c " + QString::number(day));

    //写入文件
    commands << command.toStdString() << "\n";
    commands.close();
    //调用函数
    this->operate(command);
    //显示日期的改变
    ui->date->setText("现在是"+date.showText());
}


//快捷按键 移动到下一天
void MainWindow::on_nextDay_clicked()
{
    std::string path = "./commands/"+(bankAccountNumber.toStdString())+".txt";
    commands.open(path,std::ios::app);
    QString command("");
    if(date.getDay() == date.getMaxDay()){
        //相当于下个月一号
        command = "n";
    }
    else{
        //相当于输入日期day+1
        command = "c "+QString::number(date.getDay()+1);
    }
    //写入文件
    commands << command.toStdString() << "\n";
    commands.close();
    //调用函数
    this->operate(command);
    //显示日期的改变
    ui->date->setText("现在是"+date.showText());
}



//快捷按键 移动到下一个月1日
void MainWindow::on_nextMonth_clicked()
{
    std::string path = "./commands/"+(bankAccountNumber.toStdString())+".txt";
    commands.open(path,std::ios::app);
    QString command("n");
    //写入文件
    commands << command.toStdString() << "\n";
    commands.close();
    //调用函数
    this->operate(command);
    //显示日期的改变
    ui->date->setText("现在是"+date.showText());
}



//自定义日期
void MainWindow::on_changeDateButton_clicked()
{
    //定义变量、错误提示
    QList dateLst = ui->changeDateInput->text().split("/");
    int year = dateLst[0].toInt();
    int month = dateLst[1].toInt();
    int day = dateLst[2].toInt();
    Date changeDate(year,month,day);
    QString label("");

    //先检查信息是否填写完全，行为是否合法
    if(day <= 0 || month <= 0 || year <= 0){
        label = "请输入正数日期！";
    }
    else if(changeDate < date){
        label = "不能移动到以前的日期！";
    }
    else if(day > changeDate.getMaxDay() || month > 12){
        label = "日期不合法！";
    }

    //弹出弹窗
    if(!label.isEmpty()){
        errorDialog.setLabel((label));
        errorDialog.exec();
        return ;
    }

    //分成若干个n和一个c day来处理
    std::string path = "./commands/"+(bankAccountNumber.toStdString())+".txt";
    commands.open(path,std::ios::app);

    QString command("n");
    int totalMonth = changeDate.monthDistance(date);
    for(int i=0;i<totalMonth;i++){
        //写入文件
        commands << command.toStdString() << "\n";
        //调用函数
        this->operate(command);
    }

    command = "c "+QString::number(day);
    //写入文件
    commands << command.toStdString() << "\n";
    commands.close();
    //调用函数
    this->operate(command);

    //显示日期的改变
    ui->date->setText("现在是"+date.showText());
}


//显示账目的槽函数
void MainWindow::accountRecordSlot(Date _date,QString _id,double _amount,double _balance,QString _desc){
    QStringList record;
    record << _date.showText();
    record << _id;
    record << QString::number(_amount);
    record << QString::number(_balance);
    record << _desc;

    QTreeWidgetItem* _record = new QTreeWidgetItem(record);
    ui->accountRecord->addTopLevelItem(_record);
}


