#pragma once
#include <iostream>
#include <boost/shared_ptr.hpp>
using namespace std;

#define  MakeFunc(Name)\
public:\
    std::string GetXmlStr_##Name();\
private:\
    std::string m_strXml_##Name;

class DOperXML
{
public:
    static boost::shared_ptr<DOperXML> Init();
private:
    DOperXML();
public:
    ~DOperXML();

    //MakeFunc(Login)
    //MakeFunc(ConnDev)
public:

    std::string GetXmlStr_Login(const string& strStationID, const string& strCmdType, const string& strLogin, const string& strGetLite);
    std::string GetXmlStr_ConnDev(const string& strStationID, const string& strCmdType, const string& strDevID);
    std::string GetXmlStr_ConnDev_Heart(const string& strStationID, const string& strCmdType);
private:
    std::string m_strXml_Login;
    std::string m_strXml_ConnDev;
    std::string m_strXml_ConnDev_Heart;
};

