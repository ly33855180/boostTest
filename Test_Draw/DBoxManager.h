#pragma once

#include <QObject>
#include "DBoxSocket.h"
#include "DData.h"
#include <vector>
#include <QMap>
#include <qwidget.h>
using namespace std;

class DBoxManager;

typedef boost::shared_ptr<DBoxManager> DBoxManagerPtr ;
class DBoxManager
{
private:
	DBoxManager();
	~DBoxManager();
protected:
	QMap<QString, DBoxSocketPtr> m_mapBoxID2SocketPtr;
public:
	static DBoxManager* Instance();
	static void Release();
	void SubscribeLeadData(QString qsDEV_IDX, unsigned int nWidID,  boost::function<void(const sPackageData &, int)> callbackfun);
	void UnSubscribeLeadData(QString qsDEV_IDX, unsigned int nWidID, boost::function<void(const sPackageData &, int)> callbackfun);

	bool AddBoxSocketPtr(const sMonFrame& curMonFrame);
	bool Init(const sMonitorStation& monitorStation);
	bool UnInit();

	io_service m_io;
	boost::scoped_ptr<boost::asio::io_service::work> m_work;

	boost::thread m_thread;
	void WorkThread();

	QString MakeKey(unsigned int nWidID, const sMonFrame& curMonFrame);


};
