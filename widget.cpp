#include "widget.h"
#include "ui_widget.h"
#include "bridge.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);
    //ui->widgett->setStyleSheet("QWidget{background-image: url(:/te3.png);border-radius:6px;}");

    this->setWindowFlags(   this->windowFlags() |            // Previous flags
                      Qt::FramelessWindowHint //|  // FramelessWindowHint
                      //Qt::Tool |               // No taskbar entry
                      //Qt::WindowStaysOnTopHint   // Top-Most (at least over normal windows)
                  );
    this->setAttribute(Qt::WA_NoSystemBackground, true);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    QIcon *ico = new QIcon("qrc:/icon.ico");
    this->setWindowIcon(*ico);
    // Add a Web container
    view.setParent(this);
    view.setAttribute(Qt::WA_TranslucentBackground);
    view.setStyleSheet("background:transparent");
    view.move(0,0);
    view.resize(1072, 696);
    view.page()->setBackgroundColor(Qt::transparent);
    view.load(QUrl("qrc:/login.html"));
    QWebChannel *channel = new QWebChannel(this);
    channel->registerObject("bridge", (QObject*)bridge::instance());
    view.page()->setWebChannel(channel);
    /*connect(ui->pushButton, &QPushButton::clicked, [this]() {
            QString command = QString("showAlert('%1');").arg("abcd") ;
            view.page()->runJavaScript(command);
    });*/
    void (bridge::*xx)(QString) = &bridge::start_emit;
    connect(bridge::instance(),xx,this,&Widget::read_emit);
    //myemit.get(4,16,30,6,2,5,"F:/ACM/tmpcode/A.in");
}

Widget::~Widget()
{
    delete ui;
}
void Widget::resizeEvent(QResizeEvent *)
{
    //view->resize(ui->widget->size());
}
void Widget::read_emit(QString s)
{
    qDebug()<<"AAAAAAA";
    QString command = QString("showAlert('%1');").arg(s);
    view.page()->runJavaScript(command);
}

