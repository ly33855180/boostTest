#include "DParseData.h"
#include "dataPublic.h"
#include <iostream>
#include "DOptDB.h"

#include <boost/thread/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/thread/locks.hpp>



using namespace  std;
#include <QDateTime>
QString GetCurTime()
{
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss.zzz");
    return current_date;
}
DParseData::DParseData()
{
    for (int i = 0; i < 12; i++)
    {
        CFilterService<int> *filterService = new CFilterService<int>(10 * 10, false, true, false, 0, 100, 0, 0);//标准
        m_FilterServiceList.push_back(filterService);
    }
}


DParseData::~DParseData()
{
    for (size_t i = 0; i < m_FilterServiceList.size(); i++)
    {
        CFilterService<int> *filterService = m_FilterServiceList.at(i);
        if (filterService)
        {
            delete filterService;
            filterService = NULL;
        }
    }
    m_FilterServiceList.clear();
	m_FilterServiceList.swap(vector<CFilterService<int> *>());

	m_mapWID2Callbackfun.clear();
}
boost::mutex g_readMutex0;
boost::mutex g_mapCallBcak;
void DParseData::StartParse(std::vector<unsigned char>& vecRecvBuf)
{
	int start = GetTickCount();
	//boost::lock_guard<boost::mutex> lock(g_readMutex0);
    std::vector<unsigned char>::iterator iterFind = std::find(vecRecvBuf.begin(), vecRecvBuf.end(), 0xA5);
    if(iterFind == vecRecvBuf.end())
    {
        return;
    }
    else
    {
        vecRecvBuf.erase(vecRecvBuf.begin(), iterFind);
        if (isLeadData(vecRecvBuf))//有效数据格式;
        {
            QDateTime statTime = QDateTime::currentDateTime();
            //qDebug() << "starttime = " << GetCurTime();
            int nDataLen = vecRecvBuf.at(6) + (vecRecvBuf.at(7) << 8);//数据长度;
            long long nPackageNum = (vecRecvBuf.at(8) & 0xff) + ((vecRecvBuf.at(9) & 0xff) << 8) + ((vecRecvBuf.at(10) & 0xff) << 16) + ((vecRecvBuf.at(11) & 0xff) << 24);//包序号
            int nPackCount = vecRecvBuf.at(12) & 0xff;//包个数;
            int nChannelCount = vecRecvBuf.at(13) & 0xff;//通道数;

            std::vector<unsigned char> vecParseData(2048);//包数据;
            vecParseData.assign(vecRecvBuf.begin() + 14, vecRecvBuf.begin() + 14 + 2048);

            sPackageData packageData;
            packageData.m_strRecvTime = GetCurTime().toStdString();//解包时间;
            packageData.m_nPackCount = nPackCount;//包个数;
            packageData.m_nChannelCount = nChannelCount;//通道数;
            packageData.m_nPackageNum = nPackageNum;//包序号;
            memcpy(packageData.m_ucData, &vecParseData[0], vecParseData.size() * sizeof(unsigned char));//原始数据;

            parse(packageData);
            //QDateTime endTime = QDateTime::currentDateTime();
            //int spanTime = statTime.msecsTo(endTime);
            //qDebug() << "spanTime = " << spanTime;
            //qDebug() << "endTime = " << GetCurTime();


            //DOptDB::Instance()->addLeadData(packageData);
			//
			{
				boost::lock_guard<boost::mutex> lock(g_mapCallBcak);
				for each (auto cbfun in m_mapWID2Callbackfun.values())
				{
					if (cbfun)
					{
						cbfun(packageData, 0);
					}
				}
			}


            //m_vecPackageData.push_back(packageData);
            vecRecvBuf.erase(vecRecvBuf.begin(), vecRecvBuf.begin() + 2064);
        }
        else if (isFormat(vecRecvBuf))//格式化指令格式;
        {
            int nDataLen = vecRecvBuf.at(6) + (vecRecvBuf.at(7) << 8);
            std::cout << "StartParse  nDataLen = " << nDataLen << endl;
        }
        else if (isBatteryAndSignal(vecRecvBuf))//信号电量查询格式;
        {
            int nDataLen = vecRecvBuf.at(6) + (vecRecvBuf.at(7) << 8);
            std::cout << "StartParse  nDataLen = " << nDataLen << endl;
        }
        else
        {
            std::cout << "StartParse  error!" << endl;
        }

    }
	//int end = GetTickCount();
	//qDebug() << "span = " << end - start;
}

void DParseData::ProcessData(const std::vector<unsigned char>& vecRecvBuf, long long nPackageNum,int &nPointID)
{
    int idataDecode[20];
    double dCurData[18];
    double daftfilter = 0;
    for (int j = 0; j < 28; j++)
    {
        memset(idataDecode, 0, 20 * sizeof(int));
        memset(dCurData, 0, 18 * sizeof(double));

        for (int n = 0; n < 18; n++)
        {
            if ((n == 0) || (n == 1))
            {
                idataDecode[n] = vecRecvBuf[j * 18 + n + 2];
            }
            else if ((n == 2) || (n == 3))
            {

                idataDecode[n] = vecRecvBuf[j * 18 + n - 2];
            }
            else
            {
                idataDecode[n] = vecRecvBuf[j * 18 + n];
            }
        }
        PickupData(idataDecode, dCurData);

        //sLeadData data;
        //data.m_nPackageID = nPackageNum;
        //data.m_nPointID = nPointID++;
        //for (int k = 0; k < 12; k++)
        //{
        //    daftfilter = m_FilterServiceList.at(k)->OnePointFilter(dCurData[k]);
        //    daftfilter  = daftfilter / (256 * 81.92);
        //    data.m_dData[k] = daftfilter;
        //}

        
        //DOptDB::Instance()->addLeadData(data);
        //Sleep(1000);
    }
}


void DParseData::PickupData(int *pInData, double *pOutData)
{
    int b1, b2, b3, b4, b5;

    //if (m_writeData->m_nFangDaQiXieYi == FANGDAQI_XIEYI_PC)//PC协议
    {

        SetBaudRate(345600);
        //dataPro->SetChannelNum(m_writeData->m_nFangDaQiType);

        //其中有四个导联是自己生成出来的
        memset(pOutData, 0, sizeof(double) * 18);
        for (int i = 0; i < 8; i++)
        {
            double nDataYW;

            b1 = pInData[i * 2];
            b2 = pInData[i * 2 + 1];

            nDataYW = (b1 << 16) | (b2 << 8);
            if (nDataYW > 0x800000)
            {
                nDataYW = nDataYW - 0xffffff;
            }
            pOutData[i] = nDataYW;

            if (i > 1)
            {
                pOutData[i] = -pOutData[i];
            }
        }
    }
    //8/14导联-》12/18导联
    RawToECG(pOutData);
}

int DParseData::RawToECG(double * GetData)
{
    double Data[CHANNELNUM_IN];
    int    nRet = 12;

    for (int i = 0; i < CHANNELNUM_IN; i++)
    {
        Data[i] = -GetData[i];
    }
    double Wilson = 0;

    if (m_dwBaudRate == 115200 || m_dwBaudRate == 230400)
    {
        Wilson = (LA + RA) / 3;
    }

    for (int Chn = 0; Chn < 18; Chn++)
    {
        if (m_dwBaudRate == 115200 || m_dwBaudRate == 230400)
        {
            switch (Chn)
            {
            case 0:  GetData[Chn] = (LA - RA); break;      // I =L-R
            case 1:  GetData[Chn] = -RA; break;           // II =F-R
            case 2:  GetData[Chn] = -LA; break;           // III=F-L
            case 3:  GetData[Chn] = (RA - (LA / 2)); break;  // aVR = R-(F+L)/2
            case 4:  GetData[Chn] = (LA - (RA / 2)); break;  // aVL = L-(R+L)/2
            case 5:  GetData[Chn] = -((RA / 2) + (LA / 2)); break;// aVF = F-(R+L)/2
            case 6:  GetData[Chn] = (V1 - Wilson); break;  // V1 = C1-Wilson
            case 7:  GetData[Chn] = (V2 - Wilson); break;  // V2 = C2-Wilson
            case 8:  GetData[Chn] = (V3 - Wilson); break;  // V3 = C3-Wilson
            case 9:  GetData[Chn] = (V4 - Wilson); break;  // V4 = C4-Wilson
            case 10: GetData[Chn] = (V5 - Wilson); break;  // V5 = C5-Wilson
            case 11: GetData[Chn] = (V6 - Wilson); break;  // V6 = C6-Wilson
            }
        }
        else
        {
            switch (Chn)
            {
                // 导联数据计算公式
                // III=II-I；aVR=-1/2(I+II)；aVL=I-1/2II；
                // aVF=II-1/2I=1/2III+1/2II=1/2(II-I)+1/2II
            case 0:  GetData[Chn] = -Data[0]; break;		    // I =L-R
            case 1:  GetData[Chn] = -Data[1]; break;            // II =F-R
            case 2:  GetData[Chn] = GetData[1] - GetData[0]; break;                // III=F-L
            case 3:  GetData[Chn] = -(GetData[1] + GetData[0]) / 2; break;         // aVR = R-(F+L)/2
            case 4:  GetData[Chn] = GetData[0] - GetData[1] / 2; break;            // aVL = L-(R+L)/2
            case 5:  GetData[Chn] = GetData[1] - GetData[0] / 2; break;            // aVF = F-(R+L)/2
            case 6:  GetData[Chn] = (V1 - Wilson); break;  // V1 = C1-Wilson
            case 7:  GetData[Chn] = (V2 - Wilson); break;  // V2 = C2-Wilson
            case 8:  GetData[Chn] = (V3 - Wilson); break;  // V3 = C3-Wilson
            case 9:  GetData[Chn] = (V4 - Wilson); break;  // V4 = C4-Wilson
            case 10: GetData[Chn] = (V5 - Wilson); break;  // V5 = C5-Wilson
            case 11: GetData[Chn] = (V6 - Wilson); break;  // V6 = C6-Wilson
            case 12: GetData[Chn] = (V7 - Wilson); break;   // VI = A1-Wilson
            case 13: GetData[Chn] = (V8 - Wilson); break;   // VE = A2-Wilson
            case 14: GetData[Chn] = (V9 - Wilson); break;   // VM = A3-Wilson
            case 15: GetData[Chn] = (V3R - Wilson); break;  // VH = A4-Wilson
            case 16: GetData[Chn] = (V4R - Wilson); break;  // VI = A1-Wilson
            case 17: GetData[Chn] = (V5R - Wilson); break;  // VE = A2-Wilson
            }
        }
    }

    return nRet;
}

void DParseData::SetBaudRate(long dwBaudRate)
{
    m_dwBaudRate = dwBaudRate;
}

bool DParseData::AddObserverWidID(unsigned int nWidID, boost::function<void(const sPackageData &, int)> callbackfun)
{
	boost::lock_guard<boost::mutex> lock(g_mapCallBcak);
	m_mapWID2Callbackfun.insert(nWidID, callbackfun);
	return true;
}

bool DParseData::RemoveObserverWidID(unsigned int nWidID, boost::function<void(const sPackageData &, int)> callbackfun)
{
	boost::lock_guard<boost::mutex> lock(g_mapCallBcak);
	m_mapWID2Callbackfun.remove(nWidID);
	return true;
}

bool DParseData::isLeadData(const std::vector<unsigned char>& vecRecvBuf) const
{
    int nLen = vecRecvBuf.size();

    if ((nLen >= 2064)
        && (vecRecvBuf.at(5) == 0x00)
        && (vecRecvBuf.at(4) == 0xDD)
        && (vecRecvBuf.at(3) == 0x3C)
        && (vecRecvBuf.at(2) == 0xC3)
        && (vecRecvBuf.at(1) == 0x5A)
        && (vecRecvBuf.at(0) == 0xA5))
    {
        return true;
    }
    return false;
}

bool DParseData::isBatteryAndSignal(const std::vector<unsigned char>& vecRecvBuf) const
{
    int nLen = vecRecvBuf.size();
    if ((nLen >= 18)
        && (vecRecvBuf.at(5) == 0x04)
        && (vecRecvBuf.at(4) == 0xCC)
        && (vecRecvBuf.at(3) == 0x3C)
        && (vecRecvBuf.at(2) == 0xC3)
        && (vecRecvBuf.at(1) == 0x5A)
        && (vecRecvBuf.at(0) == 0xA5))
    {
        return true;
    }
    return false;
}

bool DParseData::isFormat(const std::vector<unsigned char>& vecRecvBuf) const
{
    int nLen = vecRecvBuf.size();
    if ((nLen >= 18)
        && (vecRecvBuf.at(5) == 0x06)//格式化指令格式
        && (vecRecvBuf.at(4) == 0xCC)
        && (vecRecvBuf.at(3) == 0x3C)
        && (vecRecvBuf.at(2) == 0xC3)
        && (vecRecvBuf.at(1) == 0x5A)
        && (vecRecvBuf.at(0) == 0xA5))
    {
        return true;
    }
    return false;
}

sPackageData::sPackageData()
{

}

sPackageData::~sPackageData()
{

}

void DParseData::parse(sPackageData &packageData)
{
    for (size_t i = 0; i < 4; i++)
    {
        parseData_Lead(packageData, i, &packageData.m_ucData[i * 512], 504);
        parseData_ShedFlag(packageData, i, &packageData.m_ucData[i * 512 + 504], 8);
    }
}

void DParseData::parseData_Lead(sPackageData &packageData, int nIndex, const unsigned char * pData, int nLen /*= 504*/)
{
    int idataDecode[20];
    double dCurData[18];
    double daftfilter = 0;
    for (int j = 0; j < 28; j++)
    {
        memset(idataDecode, 0, 20 * sizeof(int));
        memset(dCurData, 0, 18 * sizeof(double));

        for (int n = 0; n < 18; n++)
        {
            if ((n == 0) || (n == 1))
            {
                idataDecode[n] = pData[j * 18 + n + 2];
            }
            else if ((n == 2) || (n == 3))
            {

                idataDecode[n] = pData[j * 18 + n - 2];
            }
            else
            {
                idataDecode[n] = pData[j * 18 + n];
            }
        }
        PickupData(idataDecode, dCurData);

        for (int k = 0; k < 12; k++)
        {
            daftfilter = m_FilterServiceList.at(k)->OnePointFilter(dCurData[k]);
            daftfilter = daftfilter / (256 * 81.92);

            packageData.m_dData[k][nIndex * 28 + j] = daftfilter;
        }
    }
}

void DParseData::parseData_ShedFlag(sPackageData &packageData, int nIndex, const unsigned char * pData, int nLen /*= 8*/)
{
    int nsensp = (pData[1] & 0xff);//505
    if (((nsensp >> 1) & 0x01) == 1 && (nsensp & 0x01) == 1)//L F全脱落
    {
        for (int m = 0; m < 12; m++)
        {
            packageData.m_bShedFlag[nIndex][m] = true;
        }
    }
    else
    {
        bool bflag = false;
        for (int nlead = 0; nlead < 8; nlead++)
        {
            if (((nsensp >> nlead) & 0x01) == 1)
            {
                bflag = true;
            }
            else
            {
                bflag = false;
            }

            switch (nlead)
            {
            case 0://F
                packageData.m_bShedFlag[nIndex][1] = bflag;
                if (!packageData.m_bShedFlag[nIndex][2])
                {
                    packageData.m_bShedFlag[nIndex][2] = bflag;
                }
                if (!packageData.m_bShedFlag[nIndex][3])
                {
                    packageData.m_bShedFlag[nIndex][3] = bflag;
                }
                if (!packageData.m_bShedFlag[nIndex][5])
                {
                    packageData.m_bShedFlag[nIndex][5] = bflag;
                }
                break;
            case 1://L
                packageData.m_bShedFlag[nIndex][0] = bflag;
                if (!packageData.m_bShedFlag[nIndex][2])
                {
                    packageData.m_bShedFlag[nIndex][2] = bflag;
                }
                if (!packageData.m_bShedFlag[nIndex][3])
                {
                    packageData.m_bShedFlag[nIndex][3] = bflag;
                }
                packageData.m_bShedFlag[nIndex][4] = bflag;
                if (!packageData.m_bShedFlag[nIndex][5])
                {
                    packageData.m_bShedFlag[nIndex][5] = bflag;
                }
                break;
            case 2://V1
                packageData.m_bShedFlag[nIndex][6] = bflag;
                break;
            case 3://V2
                packageData.m_bShedFlag[nIndex][7] = bflag;
                break;
            case 4://V3
                packageData.m_bShedFlag[nIndex][8] = bflag;
                break;
            case 5://V4
                packageData.m_bShedFlag[nIndex][9] = bflag;
                break;
            case 6://V5
                packageData.m_bShedFlag[nIndex][10] = bflag;
                break;
            case 7://V6
                packageData.m_bShedFlag[nIndex][11] = bflag;
                break;
            }
        }
        int nsensn = pData[0] & 0xff;//504

        if (((nsensn >> 1) & 0x01) == 0x01 || (nsensn & 0x01) == 0x01)//R
        {
           packageData.m_bShedFlag[nIndex][0] = true;
           packageData.m_bShedFlag[nIndex][1] = true;
           packageData.m_bShedFlag[nIndex][2] = true;
           packageData.m_bShedFlag[nIndex][3] = true;
           packageData.m_bShedFlag[nIndex][4] = true;
           packageData.m_bShedFlag[nIndex][5] = true;

        }
    }
}
