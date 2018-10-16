#include "DBoxManager.h"
#include <QDebug>

DBoxManager* g_boxManagerPtr = NULL;

DBoxManager::DBoxManager()
{
	m_thread = boost::thread(boost::bind(&DBoxManager::WorkThread, this));
}

DBoxManager::~DBoxManager()
{
}


void DBoxManager::SubscribeLeadData(QString qsDEV_IDX, unsigned int nWidID, boost::function<void(const sPackageData &, int)> callbackfun)
{
	if (m_mapBoxID2SocketPtr.contains(qsDEV_IDX))
	{
		DBoxSocketPtr ptrBoxSocket = m_mapBoxID2SocketPtr[qsDEV_IDX];
		ptrBoxSocket->AddObserverWidID(nWidID, callbackfun);
	}
	else
	{
		qDebug() << "SubscribeLeadData error!";
	}
}

void DBoxManager::UnSubscribeLeadData(QString qsDEV_IDX, unsigned int nWidID, boost::function<void(const sPackageData &, int)> callbackfun)
{
	if (m_mapBoxID2SocketPtr.contains(qsDEV_IDX))
	{
		DBoxSocketPtr ptrBoxSocket = m_mapBoxID2SocketPtr[qsDEV_IDX];
		ptrBoxSocket->RemoveObserverWidID(nWidID, callbackfun);
	}
	else
	{
		qDebug() << "UnSubscribeLeadData error!";
	}
}

bool DBoxManager::AddBoxSocketPtr(const sMonFrame& curMonFrame)
{
	string strIP = curMonFrame.m_qsDEV_IP.toStdString();
	int nPort = curMonFrame.m_qsDEV_PORT.toInt();

	DBoxSocketPtr ptrBoxSocket = DBoxSocketPtr(new DBoxSocket(m_io,"127.0.0.1", 4004));
	ptrBoxSocket->SetMonFrame(curMonFrame);
	m_mapBoxID2SocketPtr.insert(curMonFrame.m_qsDEV_IDX, ptrBoxSocket);
	return true;
}

bool DBoxManager::Init(const sMonitorStation& monitorStation)
{
	for each (auto var in m_mapBoxID2SocketPtr.values())
	{
		var->StopStartGetMdData();
	}

	m_mapBoxID2SocketPtr.clear();

	for (size_t i = 0; i < monitorStation.m_vecMonFrame.size(); i++)
	{
		const sMonFrame& curMonFrame = monitorStation.m_vecMonFrame.at(i);
		AddBoxSocketPtr(curMonFrame);
	}

	return true;
}

bool DBoxManager::UnInit()
{
	m_mapBoxID2SocketPtr.clear();
	return true;
}

void DBoxManager::WorkThread()
{

	m_work.reset(new boost::asio::io_service::work(m_io));
	m_io.run();
}

QString DBoxManager::MakeKey(unsigned int nWidID, const sMonFrame& curMonFrame)
{
	QString qsTemp = QStringLiteral("%1_%2").arg(nWidID).arg(curMonFrame.m_qsDEV_IDX);
	return qsTemp;
}

DBoxManager* DBoxManager::Instance()
{
	if (!g_boxManagerPtr)
	{
		g_boxManagerPtr = new DBoxManager();
	}
	return g_boxManagerPtr;
}

void DBoxManager::Release()
{
	if (!g_boxManagerPtr)
	{
		delete g_boxManagerPtr;
		g_boxManagerPtr = NULL;
	}
}
