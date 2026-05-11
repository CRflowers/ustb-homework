#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <fstream>
#include <cstring>
#include <string>
#include <algorithm>

#include <QDebug>
#include <QDir>

using namespace std;
const int bookNum = 8;          //书籍数量

string outBookName(int i){            //用于输出书名
    switch(i){
    case 0:return "HP2--Harry_Potter_and_the_Chamber_of_Secrets_Book_2_";
    case 1:return "HP7--Harry_Potter_and_the_Deathly_Hallows_Book_7_";
    case 2:return "J.K. Rowling - HP 0 - Harry Potter Prequel";
    case 3:return "J.K. Rowling - HP 3 - Harry Potter and the Prisoner of Azkaban";
    case 4:return "J.K. Rowling - HP 4 - Harry Potter and the Goblet of Fire";
    case 5:return "J.K. Rowling - HP 6 - Harry Potter and the Half-Blood Prince";
    case 6:return "J.K. Rowling - Quidditch Through the Ages";
    case 7:return "J.K. Rowling - The Tales of Beedle the Bard";
    }
    return "";
}



bool isNum(char* str){              //判断一个字符是否为数字
    for(int i = 0;i < (int)strlen(str);i++){
        if((int(str[i] - '0') < 0 ) || (int(str[i] - '0') > 9 )){

            return false;
        }
    }
    return true;
}


int switchToNum(char* str){         //把一个字符串表示的数字转化为数字
    int sum = 0;
    for(int i = 0;i < (int)strlen(str);i++){
        sum *= 10;
        sum += int(str[i] - '0');
    }
    return sum;
}

//名字匹配，分全字匹配(1)和部分匹配(0)，区分/不区分大小写
bool findName(char* cText,string name,int mode=1,bool caseSensitive=false){
    string text(cText);
    if(!caseSensitive){
        transform(text.begin(),text.end(),text.begin(),::tolower);      //不区分大小写，用transform()函数
        transform(name.begin(),name.end(),name.begin(),::tolower);
    }

    if(mode == 1){                  //全字匹配，用string重载过的==运算符
        if(text == name){
            return true;
        }
        else{
            return false;
        }
    }

    else if(mode == 0){             //部分匹配，用string自带的find()函数
        if(text.find(name) == string::npos){
            return false;
        }
        else{
            return true;
        }
    }
    return false;
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_searchButton_clicked()
{
    //先清除列表和上下文
    ui->result->clear();
    ui->context->clear();

    //判断是否为空输入，防止程序炸掉
    if(ui->searchInput->text().isEmpty()){
        return ;
    }

    string name = ui->searchInput->text().toStdString();    //要查询的内容
    char* text = new char[2000];     //文本字符串，每次取一行
    char* temp = new char[2000];     //临时储存text，以便操作text
    char* part = new char[50];      //分割的单词储存在part中

    ifstream b[bookNum];            //打开文件
    b[0].open("books\\HP2--Harry_Potter_and_the_Chamber_of_Secrets_Book_2_.txt",ios::out);
    b[1].open("books/HP7--Harry_Potter_and_the_Deathly_Hallows_Book_7_.txt",ios::out);
    b[2].open("books\\J.K. Rowling - HP 0 - Harry Potter Prequel.txt",ios::out);
    b[3].open("books\\J.K. Rowling - HP 3 - Harry Potter and the Prisoner of Azkaban.txt",ios::out);
    b[4].open("books\\J.K. Rowling - HP 4 - Harry Potter and the Goblet of Fire.txt",ios::out);
    b[5].open("books\\J.K. Rowling - HP 6 - Harry Potter and the Half-Blood Prince.txt",ios::out);
    b[6].open("books\\J.K. Rowling - Quidditch Through the Ages.txt",ios::out);
    b[7].open("books\\J.K. Rowling - The Tales of Beedle the Bard.txt",ios::out);


    int num = 1;        //序号
    int page = 0;       //页数
    int chapter = 0;    //章节
    int sptr;           //输出流指针
    const char* k = " ";    //分割单词用的字符，这里是空格

    for(int i = 0;i < bookNum;i++){         //遍历所有书
        while(!b[i].eof()){                 //检查是否读到文件尾，防止溢出
            sptr = b[i].tellg();            //当前指针位置，用sptr存储，后面查询就要用这个位置
            b[i].getline(text,5000);        //读取一行到text中
            strcpy(temp,text);              //用临时变量temp储存
            part = strtok(text,k);          //把一行分割成单词，并把第一个单词储存到part中

            if(strcmp(text,"") == 0){       //空行直接跳过
                continue;
            }

            if(strcmp(part,"Chapter") * strcmp(part,"CHAPTER") == 0){   //章节行，章节数自增
                chapter++;
                continue;
            }

            else if(isNum(temp)){               //页数行，页数改变
                page = switchToNum(part);
                continue;
            }

            //以上都不是，则开始匹配单词
            while(part){
                int mode = (ui->isGrep->checkState()==Qt::Checked)?1:0;
                bool isCaseSensitive = (ui->isCaseSensitive->checkState()==Qt::Checked)?true:false;
                if(findName(part,name,mode,isCaseSensitive)){
                    QStringList result;
                    result << QString::number(num);
                    result << QString::fromStdString(part);
                    result << QString::number(page);
                    result << QString::number(chapter);
                    result << QString::fromStdString(outBookName(i));

                    QTreeWidgetItem* _result = new QTreeWidgetItem(result);

                    //输出信息到result控件
                    ui->result->addTopLevelItem(_result);

                    sentence[num][0] = i;                  //储存位置指针
                    sentence[num][1] = sptr;

                    num++;
                }

                //cout << "temp:" << temp << "\npart:" << part << endl;

                part = strtok(NULL,k);
            }



        }
        //读完一本书，重置状态
        page = 0;
        chapter = 0;
        b[i].seekg(0);

    }


    //读完所有书，清除指针并移动到最开始
    for(int i=0;i<8;i++){
        b[i].clear();
        b[i].seekg(0);
    }

}

//槽函数，当某个结果被点击时，显示对应的文本
void MainWindow::on_result_itemClicked(QTreeWidgetItem *item, int column)
{
    //先清除内容
    ui->context->clear();

    //先获取编号，定义好文本
    int num = item->text(0).toInt();
    char* text = new char[5000];


    //打开文件
    ifstream b[bookNum];            //打开文件
    b[0].open("books\\HP2--Harry_Potter_and_the_Chamber_of_Secrets_Book_2_.txt",ios::out);
    b[1].open("books/HP7--Harry_Potter_and_the_Deathly_Hallows_Book_7_.txt",ios::out);
    b[2].open("books\\J.K. Rowling - HP 0 - Harry Potter Prequel.txt",ios::out);
    b[3].open("books\\J.K. Rowling - HP 3 - Harry Potter and the Prisoner of Azkaban.txt",ios::out);
    b[4].open("books\\J.K. Rowling - HP 4 - Harry Potter and the Goblet of Fire.txt",ios::out);
    b[5].open("books\\J.K. Rowling - HP 6 - Harry Potter and the Half-Blood Prince.txt",ios::out);
    b[6].open("books\\J.K. Rowling - Quidditch Through the Ages.txt",ios::out);
    b[7].open("books\\J.K. Rowling - The Tales of Beedle the Bard.txt",ios::out);

    //移动到指针位置
    //qDebug()<< "指针位置:" << sentence[num][1];
    b[sentence[num][0]].seekg(sentence[num][1]);
    b[sentence[num][0]].getline(text,5000);

    //显示在context控件上
    ui->context->setHtml(text);

}

