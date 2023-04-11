#pragma once

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QVariant>
#include <QQueue>

/*
Note:
    1.�������ݴ��䣬���߳̽��պʹ���
    2.���ݿ���߳�д��
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

    virtual void handleData(QVariant) = 0; /*������Ҫ����ʵ�ִ�����*/

private:
    QMutex m_threadRunnableMutex; /*�߳���*/

    QWaitCondition m_waitCondition; /*���ݶ��п�ʱ������ͣ�ȴ�״̬�������ݽ���ʱ�����߳�*/

    unsigned m_poolSize;            /*��������*/

    QQueue<QVariant> m_dataQueue; /*���ݶ���*/

    volatile bool m_stopped;

    //unsigned m_type; 
};

