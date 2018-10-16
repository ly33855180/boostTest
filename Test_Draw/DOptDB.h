#pragma once
#include "sqlite3.h"
#include <string>
#include <vector>
#include <share.h>
#include <map>

#include <qstring.h>
#include <QDebug>
#include <sstream>
#include <iostream> 
using namespace  std;
#include <QMetaType>
struct sPackageData
{
    enum 
    {
        EDataLen = 2048,
    };

    sPackageData();
    ~sPackageData();

    std::string m_strRecvTime;//解包时间;
    int m_nPackCount;//包个数;
    int m_nChannelCount;//通道数;
    int m_nPackageNum;//包序号;

    unsigned char m_ucData[EDataLen];//原始数据;

    double m_dData[12][112];//12导联数据,每个导联112个点;
    bool m_bShedFlag[4][12];//脱落标记;

    string Log()
    {
        std::stringstream stream;
        stream << "m_strRecvTime =  " << m_strRecvTime << "m_nPackageNum = " << m_nPackageNum << endl;
        cout << stream.str();
    }
};
Q_DECLARE_METATYPE(sPackageData);
class DOptDB
{
public:
    static DOptDB *Instance();
    static void Release();

    int Begin();
    int Commit();
    int RollBack();

    void addLeadData(const sPackageData& leadData);


    void queryData(std::vector<unsigned char>& vecData);
private:
    DOptDB();
    virtual ~DOptDB();


    sqlite3* m_sq3DB;

    string m_strFilePath;
    bool Init(void);
    void CloseDB(void);
    void FreeResult();



    
    sqlite3 * db;
    int result;
    char * errmsg;
    char **dbResult;
    int m_nRow, m_nColumn;
    int index;
};



