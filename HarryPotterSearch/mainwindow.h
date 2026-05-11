#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>

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

private slots:
    void on_searchButton_clicked();

    void on_result_itemClicked(QTreeWidgetItem *item, int column);

private:
    Ui::MainWindow *ui;
    int sentence[50000][2];         //储存查询结果位置

};
#endif // MAINWINDOW_H
