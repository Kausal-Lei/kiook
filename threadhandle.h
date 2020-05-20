//threadhandle.h
#ifndef THREADHANDLE_H
#define THREADHANDLE_H

#include <QObject>
#include <QThread>

class ThreadHandle : public QThread
{
    Q_OBJECT

public:
    ThreadHandle(QObject *parent = 0);
    ~ThreadHandle();

protected:
    void run();

public:
    int ggroup;int ccontestant;int iinittime;int mmatchesperday;int iinterval;int wwhatday;QString ss;
    bool signalFlag;

private slots:
    void slotFun(int Group,int Contestant,int Inittime,int Matchesperday,int Interval,int Whatday,QString S);
signals:
    void send_export_signal(QString);
};

#endif // THREADHANDLE_H
