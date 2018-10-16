#pragma once
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <QString>
using namespace std;

class sServerInfo
{
private:
    static std::string m_strIP;
    static int m_nPort;
    sServerInfo();

public:
    static string GetIP();
    static int GetPort();

};
struct sItem
{
    QString m_qsIDX;
    QString m_qsID_CODE;
    QString m_qsDB_ID;
    QString m_qsCAPTION;
    QString m_qsCONTENT;

	string log() const
	{
		std::cout << "*****sItem begin*****" << endl;
		std::cout << "eItem_IDX:" << m_qsIDX.toStdString()<< endl;
		std::cout << "eItem_ID_CODE:" << m_qsID_CODE.toStdString() << endl;
		std::cout << "eItem_DB_ID:" << m_qsDB_ID.toStdString() << endl;
		std::cout << "eItem_CAPTION:" << m_qsCAPTION.toStdString() << endl;
		std::cout << "eItem_CONTENT:" << m_qsCONTENT.toStdString() << endl;
		std::cout << "*****sItem end  *****" << endl;

		return "";
	}
};
struct sCandidateInfo
{
    vector<sItem> m_vecItem;
	string log() const
	{
		std::cout << "*****sCandidateInfo begin*****" << endl;
		for (size_t i = 0; i < m_vecItem.size(); i++)
		{
            const sItem& item = m_vecItem.at(i);
			item.log();
		}
		std::cout << "*****sCandidateInfo end  *****" << endl;

		return "";
	}
	~sCandidateInfo()
	{
		m_vecItem.clear();
		m_vecItem.swap(vector<sItem>());
	}
};
struct sMonFrame
{
    QString m_qsNO;
    int m_nNo;
    QString m_qsDEV_IDX;
    QString m_qsDEV_IP;
    QString m_qsDEV_PORT;
    QString m_qsVALID_DATE;
    QString m_qsDEV_TYPE;
    QString m_qsDEV_FORMATID;
    QString m_qsDEV_STATUS;
    QString m_qsDEV_STUDYID;

	sCandidateInfo m_sCandidateInfo;

	string log() const
	{
		std::cout << "*****sMonFrame begin*****" << endl;
		std::cout << "eMF_NO:" << m_qsNO.toStdString() << endl;
		std::cout << "eMF_DEV_IDX:" << m_qsDEV_IDX.toStdString() << endl;
		std::cout << "eMF_DEV_IP:" << m_qsDEV_IP.toStdString() << endl;
		std::cout << "eMF_DEV_PORT:" << m_qsDEV_PORT.toStdString() << endl;
		std::cout << "eMF_VALID_DATE:" << m_qsVALID_DATE.toStdString() << endl;
		std::cout << "eMF_DEV_TYPE:" << m_qsDEV_TYPE.toStdString() << endl;
		std::cout << "eMF_DEV_FORMATID:" << m_qsDEV_FORMATID.toStdString() << endl;
		std::cout << "eMF_DEV_STATUS:" << m_qsDEV_STATUS.toStdString() << endl;
		std::cout << "eMF_DEV_STUDYID:" << m_qsDEV_STUDYID.toStdString() << endl;

		m_sCandidateInfo.log();
		std::cout << "*****sMonFrame end  *****" << endl;
		return "";
	}
	~sMonFrame()
	{

	}
};

struct sMonitorStation
{

    QString m_qsECGrealtimemonitorbuffer;
    QString m_qsID;
    QString m_qsMinimalECGdisplaytime;
    QString m_qsCOUNT;
    QString m_qsRIGHT;

    vector<sMonFrame> m_vecMonFrame;

	string log() const
	{
		std::cout << "*****sMonitorStation begin*****" << endl;
		std::cout << "eMs_ECGrealtimemonitorbuffer:" << m_qsECGrealtimemonitorbuffer.toStdString() << endl;
		std::cout << "eMs_ID:" << m_qsID.toStdString() << endl;
		std::cout << "eMs_MinimalECGdisplaytime:" << m_qsMinimalECGdisplaytime.toStdString() << endl;
		std::cout << "eMs_COUNT:" << m_qsCOUNT.toStdString() << endl;
		std::cout << "eMs_RIGHT:" << m_qsRIGHT.toStdString() << endl;

        for (size_t i = 0; i < m_vecMonFrame.size(); i++)
        {
            const sMonFrame& item = m_vecMonFrame.at(i);
            item.log();
        }

		std::cout << "*****sMonitorStation end  *****" << endl;
		return "";
	}
	~sMonitorStation() 
	{
		m_vecMonFrame.clear();
		m_vecMonFrame.swap(vector<sMonFrame>());
	}
};
struct s_Md
{
    QString m_qsSERVICE_TYPE;
    vector<sMonitorStation> m_vecMonitorStation;

	string log() const
	{
		std::cout << "*****s_Md begin*****" << endl;
		std::cout << "eMd_SERVICE_TYPE:" << m_qsSERVICE_TYPE.toStdString() << endl;

        for (size_t i = 0; i < m_vecMonitorStation.size(); i++)
        {
            const sMonitorStation& item = m_vecMonitorStation.at(i);
            item.log();
        }

		std::cout << "*****s_Md end  *****" << endl;
		return "";
	}
	~s_Md()
	{
		m_vecMonitorStation.clear();
		m_vecMonitorStation.swap(vector<sMonitorStation>());
	}
};
