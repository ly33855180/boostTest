#include "DOptDB.h"

#include <string>
#include <QDir.h>
#include <qDebug.h>

#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

#include <QDateTime>
#include <iostream>
using namespace  std;

# if 0
#define SQL_NEWDB "CREATE TABLE t_LeadData (\
curTime   DATETIME NOT NULL,\
packageID INTEGER NOT NULL,\
pointID   INTEGER  NOT NULL,\
lead_I    REAL     NOT NULL,\
lead_II   REAL     NOT NULL,\
lead_III  REAL     NOT NULL,\
lead_aVR  REAL     NOT NULL,\
lead_aVL  REAL     NOT NULL,\
lead_aVF  REAL     NOT NULL,\
lead_V1   REAL     NOT NULL,\
lead_V2   REAL     NOT NULL,\
lead_V3   REAL     NOT NULL,\
lead_V4   REAL     NOT NULL,\
lead_V5   REAL     NOT NULL,\
lead_V6   REAL     NOT NULL,\
primary key(packageID, pointID));"


#define SQL_ADDDATA "insert into t_LeadData(\
curTime ,\
packageID ,\
pointID ,\
lead_I ,\
lead_II ,\
lead_III ,\
lead_aVR ,\
lead_aVL ,\
lead_aVF ,\
lead_V1 ,\
lead_V2 ,\
lead_V3 ,\
lead_V4 ,\
lead_V5 ,\
lead_V6) VALUES (\"%1\",%2,%3,%4,%5,%6,%7,%8,%9,%10,%11,%12,%13,%14,%15);"

#endif

#define SQL_NEWDB "CREATE TABLE t_LeadData (\
curTime   DATETIME NOT NULL UNIQUE,\
packageID INTEGER  PRIMARY KEY NOT NULL UNIQUE,\
data      BLOB     NOT NULL);"


#define SQL_ADDDATA "insert into t_LeadData values(?, ?, ?);"

#define  SQL_DBNAME  "/test.zip"
DOptDB * g_instance = NULL;
DOptDB * DOptDB::Instance()
{
    if (!g_instance)
    {
        g_instance = new DOptDB();
        if (!g_instance->Init())
        {
            return NULL;
        }
    }
    return g_instance;
}

DOptDB::DOptDB()
{
}


DOptDB::~DOptDB()
{
}

bool DOptDB::Init(void)
{
    QString fullpath = QDir::currentPath() + QString(SQL_DBNAME);
    std::string strBuf = fullpath.toStdString();
    m_strFilePath = strBuf;

    int nn = sqlite3_config(SQLITE_CONFIG_SERIALIZED);
    if (SQLITE_OK != sqlite3_open_v2(strBuf.c_str(), &m_sq3DB, SQLITE_OPEN_READWRITE, NULL))
    {
        if (!m_sq3DB)
        {
            qDebug() << "sqlite error! null == m_sq3DB";
            return false;
        }
        //创建新的数据库
        int nRet = SQLITE_OK;
        nRet = sqlite3_open_v2(strBuf.c_str(), &m_sq3DB, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
        if (SQLITE_OK != nRet)
        {
            qDebug() << "sqlite3_open_v2 error! fullpath ="<< fullpath;
            return false;
        }
        nRet = sqlite3_exec(m_sq3DB, SQL_NEWDB, NULL, NULL, NULL);
        if (SQLITE_OK != nRet)
        {
            qDebug() << "SQL_NEWDB error!";
            return false;
        }
        qDebug() << "sqlite 创建数据库成功！"<< fullpath;
    }
    qDebug() << "sqlite 初始化数据库成功！" << fullpath;
    
    return true;
}

void DOptDB::CloseDB(void)
{
    if (m_sq3DB)
    {
        sqlite3_close(m_sq3DB);
    }
}
void DOptDB::FreeResult()
{
    if (dbResult)
    {
        sqlite3_free_table(dbResult);
        dbResult = NULL;
    }

}


void DOptDB::addLeadData(const sPackageData& leadData)
{
    if (!m_sq3DB)
    {
        qDebug() << "addLeadData addData  error = m_sq3DB is Null!";
        return;
    }

    sqlite3_stmt* stmt;
    if (sqlite3_prepare(m_sq3DB, SQL_ADDDATA, -1, &stmt, NULL) != SQLITE_OK)
    {
        if (stmt)
        {
            sqlite3_finalize(stmt);
        }
        qDebug() << "addLeadData sqlite3_prepare eror!";
        return;
    }

    int nRet;
    nRet = sqlite3_bind_text(stmt, 1, leadData.m_strRecvTime.c_str(), -1, NULL);
    nRet = sqlite3_bind_int(stmt, 2, leadData.m_nPackageNum);
    nRet = sqlite3_bind_blob(stmt, 3, leadData.m_ucData, sPackageData::EDataLen, NULL);

    if (SQLITE_OK != nRet)
    {
        qDebug() << "addLeadData sqlite3_bind_XXX error!";
    }

    nRet = sqlite3_step(stmt);
    if (nRet != SQLITE_DONE)
    {
        qDebug() << "addLeadData sqlite3_step eror!";
    }
    sqlite3_finalize(stmt);
}

void DOptDB::queryData(std::vector<unsigned char>& vecData)
{
    string strSql = "select * from t_LeadData where packageID = 81087;";
    char** pResult;
    int nRow = 0;
    int nCol = 0;
    int nResult = sqlite3_get_table(m_sq3DB, strSql.c_str(), &pResult, &nRow, &nCol, &errmsg);
    if (nResult != SQLITE_OK)
    {
        sqlite3_close(m_sq3DB);
        sqlite3_free(errmsg);
    }

    string strOut;
    int nIndex = nCol;
    for (int i = 0; i < nRow; i++)
    {
        for (int j = 0; j < nCol; j++)
        {
            strOut += pResult[j];
            strOut += ":";
            strOut += pResult[nIndex];
            strOut += "\n";
            ++nIndex;
        }
    }
    sqlite3_free_table(pResult);  //使用完后务必释放为记录分配的内存，否则会内存泄漏
    std::cout<< strOut.c_str()<<endl;
   // sqlite3_close(m_sq3DB);
    return ;
}

void DOptDB::Release()
{
    if (g_instance)
    {
        g_instance->FreeResult();
        g_instance->CloseDB();
        delete g_instance;
    }
}

int DOptDB::Begin()
{
    char* cErrMsg;
    int nRet = sqlite3_exec(m_sq3DB,"begin", 0, 0, &cErrMsg); // 开始一个事务
    if (nRet != SQLITE_OK)
    {
        sqlite3_free(cErrMsg);
    }
    return nRet;
}

int DOptDB::Commit()
{
    char* cErrMsg;
    int nRet = sqlite3_exec(m_sq3DB, "commit", 0, 0, &cErrMsg); // 开始一个事务
    if (nRet != SQLITE_OK)
    {
        sqlite3_free(cErrMsg);
    }
    return nRet;

}

int DOptDB::RollBack()
{
    char* cErrMsg;
    int nRet = sqlite3_exec(db, "rollback", 0, 0, &cErrMsg); // 开始一个事务
    if (nRet != SQLITE_OK)
    {
        sqlite3_free(cErrMsg);
    }
    return nRet;
}

