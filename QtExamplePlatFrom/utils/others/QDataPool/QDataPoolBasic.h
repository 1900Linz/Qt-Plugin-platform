#pragma once

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QQueue>
#include <QVariant>

/*
Note:
    1.网络数据传输，多线程接收和处理
    2.数据库多线程写入
*/
class QDataPoolBasic :
    public QThread
{
    Q_OBJECT
public:
    explicit QDataPoolBasic(/*unsigned type,*/ QObject* parent = 0);

    ~QDataPoolBasic();

    bool recvData(QVariant);

    void setPoolSize(unsigned size);

    void turn_on();

    void turn_off();

protected:
    void run() override;

    virtual void handleData(QVariant) = 0; /*子类需要重新实现处理方法*/

private:
    QMutex m_threadRunnableMutex; /*线程锁*/

    QWaitCondition m_waitCondition; /*数据队列空时进入暂停等待状态，新数据进入时唤醒线程*/

    unsigned m_poolSize;            /*队列上限*/

    QQueue<QVariant> m_dataQueue; /*数据队列*/

    volatile bool m_stopped;

    //unsigned m_type; 
};

