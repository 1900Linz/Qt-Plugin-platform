#pragma once

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QVariant>
#include <QQueue>

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
    explicit QDataPoolBasic(/*unsigned type,*/ QObject* parent = 0)
        :QThread(parent)
        //,m_type(type)
    {
        m_poolSize = 1000;
        m_stopped = true;
        m_dataQueue.clear();
    }

    ~QDataPoolBasic()
    {
        m_stopped = true;
        m_waitCondition.wakeOne();
        quit();
        wait();

        m_stopped = true;
    }

    bool recvData(QVariant data)
    {
        QMutexLocker lock(&m_threadRunnableMutex);
        if (static_cast<unsigned>(m_dataQueue.size()) > m_poolSize)
        {
            return false;
        }
        else
        {
            m_dataQueue.append(data);
            m_waitCondition.wakeOne();
            return true;
        }
    }

    void setPoolSize(unsigned size)
    {
        m_poolSize = size;
    }

    void turn_on()
    {
        if (m_stopped)
        {
            turn_on();

        }
    }

    void turn_off()
    {
        m_stopped = true;
        m_waitCondition.wakeOne();

        quit();
        wait();
    }

protected:
    void run() override
    {
        m_dataQueue.clear();
        m_stopped = false;

        while (1)
        {
            QMutexLocker lock(&m_threadRunnableMutex);
            if (m_dataQueue.isEmpty())
            {
                m_waitCondition.wait(&m_threadRunnableMutex);
            }
            else
            {
                auto data = m_dataQueue.takeFirst();
                lock.unlock();
                handleData(data);
            }

            if (m_stopped)
            {
                break;
            }
        }
    }

    virtual void handleData(QVariant) = 0; /*子类需要重新实现处理方法*/

private:
    QMutex m_threadRunnableMutex; /*线程锁*/

    QWaitCondition m_waitCondition; /*数据队列空时进入暂停等待状态，新数据进入时唤醒线程*/

    unsigned m_poolSize;            /*队列上限*/

    QQueue<QVariant> m_dataQueue; /*数据队列*/

    volatile bool m_stopped;

    //unsigned m_type; 
};

