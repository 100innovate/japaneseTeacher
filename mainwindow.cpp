﻿#include"mainwindow.h"
#include"qheadfile.h"

const static int pos_min_x = 0;
const static int pos_max_x = 1050;
const static int pos_min_y = 0;
const static int pos_max_y = 75;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->SetWindowsSize(1050,700);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("QWidget{background-color:#4da6de;border:2px groove gray;border-radius:10px;padding:2px 4px;}");
    isMousePressed=false;
    SetFillet();
    MainManagement=new management;

    Topwindows =new TopWindowsUI(this);
    FootGroupBox=new QGroupBox(this);                          SetFooterMessage();
    MainUiGroupBox=new QGroupBox(this);                        SetMainGroupBox();
    RightGroupBox=new QGroupBox(this);                         SetRightGroupBox();

    FunctionSelection =new FunctionSelectionUI(MainUiGroupBox);  //主页选择页面
    WordList =new WordListUI(MainUiGroupBox);                    //单词列表
    WordStudy = new WordStudyUI(MainUiGroupBox);                 //单词学习
    Problem = new ProblemUI(MainUiGroupBox);                     //测试页面

    //WordStudyGroupBox=new QGroupBox(MainUiGroupBox);           SetWordStudyGroupBox();
    //WordStudyGroupBox->hide();

    WordList->MainManagement=MainManagement;
    WordStudy->MainManagement=MainManagement;
    FunctionSelection->MainManagement=MainManagement;
    Problem->MainManagement=MainManagement;

    AllWindowsHide();   //隐藏所有窗口
    SetMainConnect();   //各类窗口切换Connect
}

MainWindow::~MainWindow()
{
    delete MainManagement;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    mousePosition = event->pos();
    //只对标题栏范围内的鼠标事件进行处理
    if (mousePosition.x()<=pos_min_x)
    return;
    if ( mousePosition.x()>=pos_max_x)
    return;
    if (mousePosition.y()<=pos_min_y )
    return;
    if (mousePosition.y()>=pos_max_y)
    return;
    isMousePressed = true;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if ( isMousePressed==true )
    {
    QPoint movePot = event->globalPos() - mousePosition;
    move(movePot);
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    isMousePressed=false;
}



void MainWindow::SetWindowsSize(int x, int y)
{
    this->resize(x,y);
    this->setMaximumSize(x,y);
    this->setMinimumSize(x,y);
}


void MainWindow::SetFillet()
{
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),20,20);
    setMask(bmp);
}

void MainWindow::SetFooterMessage()
{
    FootGroupBox->setGeometry(5,this->height()*0.94,this->width()-6,this->height()*0.06);
    FootGroupBox->setStyleSheet("border:0px groove gray;");
    QLabel *FootLabel=new QLabel(FootGroupBox);
    FootLabel->setStyleSheet("color:#ffffff;border:0px groove gray;");
    FootLabel->move(20,17);
    FootLabel->setText("V 1.00 版权所有 水木日语教育科技有限公司");
}

void MainWindow::SetMainGroupBox()
{
    MainUiGroupBox->setGeometry(5,Topwindows->height(),this->width()*0.7,this->height()-Topwindows->height()-FootGroupBox->height());
    MainUiGroupBox->setStyleSheet("background-color:#ffffff;border:1px groove gray;border-radius:0px;padding:0px 0px;");
}

void MainWindow::SetRightGroupBox()
{
    RightGroupBox->setGeometry(MainUiGroupBox->width()+5,Topwindows->height(),this->width()-MainUiGroupBox->width()-10,this->height()-Topwindows->height()-FootGroupBox->height());
    RightGroupBox->setStyleSheet("background-color:#ffffff;border:1px groove gray;border-radius:0px;padding:0px 0px;");

    QGroupBox *RightTopBox=new QGroupBox(RightGroupBox);
    QGroupBox *FootTopBox=new QGroupBox(RightGroupBox);
    RightTopBox->setGeometry(0,0,RightGroupBox->width(),RightGroupBox->height()*0.3);
    FootTopBox->setGeometry(0,RightTopBox->height(),RightGroupBox->width(),RightGroupBox->height()-RightTopBox->height());

    QPushButton *ProblemButton=new QPushButton(RightTopBox);
    ProblemButton->setText( "我的词本");
    ProblemButton->setStyleSheet("QPushButton{border:1px groove gray;border-radius:5px;padding:0px 0px;color:#ffffff;font-weight:bold;}"
                                 "QPushButton{background:#62B1E1;}"
                                 "QPushButton:hover{background:#42A1E1;}"
                                 "QPushButton:pressed{background:#2281B1;}");
    ProblemButton->setGeometry((RightTopBox->width()-110)/2,(RightTopBox->height()-45)/2,110,40);
}


void MainWindow::SetMainConnect()
{
    QObject::connect(Topwindows->NavigationButton1,&QPushButton::clicked,this,&MainWindow::GoBackToMain);
    QObject::connect(FunctionSelection->BegainButton,&QPushButton::clicked,this,&MainWindow::GoToWordList);
    QObject::connect(WordList->gotostudy,&QPushButton::clicked,this,&MainWindow::GoToWordStudy);
    QObject::connect(WordList->gototest,&QPushButton::clicked,this,&MainWindow::GoToProblem);
    QObject::connect(WordStudy->gototest,&QPushButton::clicked,this,&MainWindow::GoToProblem);
}

void MainWindow::AllWindowsHide()
{
    WordList->hide();
    WordStudy->hide();
    Problem->hide();
}

void MainWindow::GoBackToMain()
{
    Problem->newstart();
    FunctionSelection->show();
    WordList->hide();
    WordList->WordList->clear();
    WordStudy->hide();
    Problem->hide();
    Problem->pro->make_empty();


}

void MainWindow::GoToWordList()
{
    MainManagement->clear();
    MainManagement->readfile();
    FunctionSelection->hide();
    WordList->AddWord();
    WordList->show();
    WordStudy->hide();
    Problem->hide();
}

void MainWindow::GoToWordStudy()
{
    FunctionSelection->hide();
    WordList->hide();
    WordStudy->show();
    WordStudy->former_change();
    Problem->hide();
}

void MainWindow::GoToProblem()
{
    Problem->pro->init();
    FunctionSelection->hide();
    WordList->hide();
    WordStudy->hide();
    Problem->show();
}
