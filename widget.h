#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QBitmap>
#include <QPainter>
#include <QWebEngineView>
#include <QMainWindow>
#include <QFrame>
#include <string>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsDropShadowEffect>
#include<QPainter>
#include <QDir>
#include <QtWebChannel>
#include "bridge.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
    void resizeEvent(QResizeEvent *);
private slots:
    void read_emit(QString s);
private:
    Ui::Widget *ui;
    QWebEngineView view;
    QWebChannel *webChannel = nullptr;
};

#endif // WIDGET_H
