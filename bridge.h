#ifndef BRIDGE_H
#define BRIDGE_H
#include <QList>
#include <QString>
#include <QObject>
#include"threadhandle.h"
class bridge :public QObject
{
Q_OBJECT
public:
    static bridge* instance();
    bridge();
    ThreadHandle *m_thread;
public slots:
    void get(int,int,int,int,int,int,QString);
    void send_cmd(QString);
signals:
    void start_emit(QString);
    void emitSaveTOsignal(int,int,int,int,int,int,QString);
};

#endif // BRIDGE_H
