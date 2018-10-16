#pragma once
#define PackageLen 2064
#include "FilterServer/FilterService.h"
#include <vector>
#include <string>
using namespace std;
#include "DOptDB.h"

#include <boost/bind.hpp>
#include <boost/function.hpp>

#include <QMap>
class DParseData
{
public:
    DParseData();
    virtual ~DParseData();

    void StartParse(std::vector<unsigned char>& vecRecvBuf);

private:
    bool isLeadData(const std::vector<unsigned char>& vecRecvBuf) const;
    bool isBatteryAndSignal(const std::vector<unsigned char>& vecRecvBuf) const;
    bool isFormat(const std::vector<unsigned char>& vecRecvBuf) const;

private:
    void parse(sPackageData &packageData);
    vector<sPackageData> m_vecPackageData;

    void parseData_Lead(sPackageData &packageData, int nIndex, const unsigned char * pData, int nLen = 504);
    void parseData_ShedFlag(sPackageData &packageData, int nIndex, const unsigned char * pData, int nLen = 8);

    void ProcessData(const std::vector<unsigned char>& vecRecvBuf, long long nPackageNum, int &nPointID);
    void PickupData(int *pInData, double *pOutData);
    int RawToECG(double * GetData);
    void SetBaudRate(long dwBaudRate);

    long  m_dwBaudRate;// ²¨ÌØÂÊ
    vector<CFilterService<int> *> m_FilterServiceList;

public:
	QMap<unsigned int, boost::function<void(const sPackageData &, int)> > m_mapWID2Callbackfun;
	bool AddObserverWidID(unsigned int nWidID, boost::function<void(const sPackageData &, int)> callbackfun);
	bool RemoveObserverWidID(unsigned int nWidID, boost::function<void(const sPackageData &, int)> callbackfun);
};

