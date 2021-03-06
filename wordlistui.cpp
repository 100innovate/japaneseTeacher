﻿#include "wordlistui.h"
#include<QMediaPlayer>
#include<QDebug>

WordListUI::WordListUI(QWidget *parent) : QWidget(parent)
{
    this->setGeometry(0,0,parent->width(),parent->height());
    this->setStyleSheet("background-color:#ffffff;border:0px groove gray;border-radius:0px;padding:0px 0px;");

    gotostudy=new QPushButton(this);
    gototest=new QPushButton(this);

    gotostudy->setStyleSheet("background:#42A1E1;");
    gototest->setStyleSheet("background:#42A1E1");

    tipBox= new QGroupBox(this);
    tips = new QLabel(tipBox);
    numberTips = new QLabel(tipBox);

    gotostudy->setText("进入学习");
    gototest->setText("马上测试");

    gotostudy->setStyleSheet("QPushButton{border:1px groove gray;border-radius:5px;padding:0px 0px;color:#ffffff;font-size:13px;font-family:MingLiu;}"
                             "QPushButton{background:#62B1E1;}"
                             "QPushButton:hover{background:#42A1E1;}"
                             "QPushButton:pressed{background:#2281B1;}");
    gototest->setStyleSheet("QPushButton{border:1px groove gray;border-radius:5px;padding:0px 0px;color:#ffffff;font-size:13px;font-family:MingLiu;}"
                            "QPushButton{background:#62B1E1;}"
                            "QPushButton:hover{background:#42A1E1;}"
                            "QPushButton:pressed{background:#2281B1;}");

    gotostudy->setGeometry(540,525,80,30);
    gototest->setGeometry(630,525,80,30);

    tipBox->setGeometry(10,45,this->width()-20,40);
    tipBox->setStyleSheet("background:#F1F1F1;border:0px groove gray;border-radius:0px;padding:0px 0px;");
    tips->setText("消息播放器：这是一条测试消息");
    tips->move(15,15);


    numberTips->setText("已选择 100 词/ 共100词");
    numberTips->move(550,15);

    WordList=new QListWidget(this);
    WordList->setGeometry(15,100,this->width()-30,this->height()-200);
    WordList->setStyleSheet("QListWidget{border:1px groove gray;}");

    QFile StyleSheet(":/qss/QScrollBar");
    StyleSheet.open(QFile::ReadOnly);
    WordList->verticalScrollBar()->setStyleSheet(StyleSheet.readAll());

}

void WordListUI::AddWord()
{
    int count=MainManagement->get_sise();

    for(int i=0; i<count; i++)
    {
        QListWidgetItem *item = new QListWidgetItem("a",NULL);
        QWidget *itemwidget=new QWidget();
        QPushButton *button=new QPushButton(itemwidget);
        QCheckBox *checkBox =new QCheckBox(itemwidget);
        QLabel *japanese= new QLabel(itemwidget);
        QLabel *chinese= new QLabel(itemwidget);

        QMediaPlayer *player=new QMediaPlayer(itemwidget);

        QString Url=("qrc:///1/1w");
        Url+=QString::number(i+1);
        player->setMedia(QUrl(Url));

        japanese->setText(QString::fromStdString
                           (MainManagement->get_i_Jan(i)));
        chinese->setText(QString::fromStdString
                           ("["+MainManagement->get_i_propety(i)+"]"+MainManagement->get_i_ch(i)));
        item->setSizeHint(QSize(WordList->width()-25, 38));
        button->setGeometry(65,9,20,20);
        checkBox->setGeometry(35,9,20,20);
        japanese->move(100,11);
        chinese->move(370,11);
        checkBox->setStyleSheet("background-color:rgba(255,255,255,0);");
        itemwidget->setStyleSheet("QWidget{background:#FFFFFF;}"
                                  "QWidget:hover{background:#F2F1F1;}"
                                  "QWidget:pressed{background:#F2F1F1;}"
                                  "QLabel{background-color:rgba(255,255,255,0);}");
        button->setStyleSheet("QPushButton{background:#62B1E1;border-radius:10px;}"
                              "QPushButton:hover{background:#42A1E1;}"
                              "QPushButton:pressed{background:#2281B1;}");
        //QComboBox *box = new QComboBox();
        //box->addItems(QStringList()<<"1"<<"2");
        WordList->addItem(item);
        WordList->setItemWidget(item,itemwidget);

        QObject::connect(button,&QPushButton::clicked,player,&QMediaPlayer::play);
    }
}
