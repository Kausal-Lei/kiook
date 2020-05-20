#include "bridge.h"
#include "threadhandle.h"
#include <QMessageBox>
#include <QDebug>
bridge* bridge::instance()
{
    static bridge s_obj;
    return &s_obj;
}

bridge::bridge()
{
}

void bridge::get(int group,int contestant,int inittime,int matchesperday,int interval,int whatday,QString s)
{
    m_thread = new ThreadHandle();
    connect(this, SIGNAL(emitSaveTOsignal(int,int,int,int,int,int,QString)), m_thread, SLOT(slotFun(int,int,int,int,int,int,QString)));//接连2
    connect(m_thread,SIGNAL(send_export_signal(QString)),this,SLOT(send_cmd(QString)),Qt::BlockingQueuedConnection);
    m_thread->start();
    emit(emitSaveTOsignal(group,contestant,inittime,matchesperday,interval,whatday,s));
    //qDebug()<<"HAHA";
    //method a;
    //qDebug()<<group<<" "<<group<<" "<<contestant<<" "<<inittime<<" "<<matchesperday<<" "<<interval<<" "<<whatday<<" "<<s<<" ";
    //QString ans=QString::fromStdString(a.init(group,contestant,inittime,matchesperday,interval,whatday,s.toStdString()));
    //qDebug()<<ans;
    //emit start_emit(ans);
}
void bridge::send_cmd(QString s) {
    emit start_emit(s);
}
