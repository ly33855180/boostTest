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

    std::string m_strRecvTime;//���ʱ��;
    int m_nPackCount;//������;
    int m_nChannelCount;//ͨ����;
    int m_nPackageNum;//�����;

    unsigned char m_ucData[EDataLen];//ԭʼ����;

    double m_dData[12][112];//12��������,ÿ������112����;
    bool m_bShedFlag[4][12];//������;

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



