#include "QDataPoolBasic.h"

QDataPoolBasic::QDataPoolBasic(/*unsigned type,*/ QObject* parent)
	:QThread(parent)
	//,m_type(type)

{
	m_poolSize = 1000;
	m_stopped = true;
	m_dataQueue.clear();
}

QDataPoolBasic::~QDataPoolBasic()
{
	m_stopped = true;
	m_waitCondition.wakeOne();
	quit();
	wait();

	m_stopped = true;
}

bool QDataPoolBasic::recvData(QVariant data)
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

void QDataPoolBasic::setPoolSize(unsigned size)
{
	m_poolSize = size;
}

void QDataPoolBasic::turn_on()
{
	if (m_stopped)
	{
		turn_on();

	}
}

void QDataPoolBasic::turn_off()
{
	m_stopped = true;
	m_waitCondition.wakeOne();

	quit();
	wait();
}

void QDataPoolBasic::run()
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
