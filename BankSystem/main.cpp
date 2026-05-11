#include "mainwindow.h"
#include "LogIn.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;    //先调用mainwindow的成员函数，显示登录界面，mainwindow在登录成功信号发出后才显示
    w.showLogInWidget();

    return a.exec();
}
