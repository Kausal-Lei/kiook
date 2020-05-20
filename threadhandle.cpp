//threadhandle.cpp
#include "threadhandle.h"
#include "a.h"
#include<QDebug>
#include<QThread>
ThreadHandle::ThreadHandle(QObject *parent)
 : QThread()
{
     signalFlag = false;
}

void ThreadHandle::run()
{
    while (1)
    {
        if (signalFlag == true)
        {
            signalFlag = false;
            method a;
            QString ans=QString::fromStdString(a.init(ggroup,ccontestant,iinittime,mmatchesperday,iinterval,wwhatday,ss.toStdString()));
            emit send_export_signal(ans);
            break;
        }
    }
}


void ThreadHandle::slotFun(int GGroup,int CContestant,int IInittime,int MMatchesperday,int IInterval,int WWhatday,QString SS)
{
     ggroup=GGroup;
     ccontestant=CContestant;
     iinittime=IInittime;
     mmatchesperday=MMatchesperday;
     iinterval=IInterval;
     wwhatday=WWhatday;
     ss=SS;
     signalFlag = true;
}

ThreadHandle::~ThreadHandle()
{
}
