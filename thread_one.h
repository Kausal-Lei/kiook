#ifndef THREAD_ONE_H
#define THREAD_ONE_H

#include <QThread>
#include <QString>
class thread_one : public QThread
{
    Q_OBJECT
public:
    explicit thread_one(QObject *parent = nullptr);
protected:
    void run(int group,int contestant,int inittime,int matchesperday,int interval,int whatday,QString s);//多线程执行的内容将通过重新该虚函数实现
signals:
    void over(QString s);
public slots:
};

#endif // THREAD_ONE_H
