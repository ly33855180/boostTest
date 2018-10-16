#include "DOperXML.h"

#include <boost/format.hpp>
#include <boost/make_shared.hpp>

boost::shared_ptr<DOperXML> g_ptrOptXml = boost::shared_ptr<DOperXML>();

boost::shared_ptr<DOperXML> DOperXML::Init()
{
    if (!g_ptrOptXml)
    {
        g_ptrOptXml = boost::shared_ptr<DOperXML>(new DOperXML);
    }
    return g_ptrOptXml;
}

DOperXML::DOperXML()
{
}


DOperXML::~DOperXML()
{
}

std::string DOperXML::GetXmlStr_Login(const string& strStationID, const string& strCmdType, const string& strLogin, const string& strGetLite)
{
    if (DOperXML::m_strXml_Login.empty())
    {
        boost::format fmt2("<?xml version=\"1.0\" encoding=\"utf - 8\"?>\n\
            <MD>\n\
            <MONITOR_STATION ID = \"%1%\">\n\
            <MSCMDTYPE>%2%</MSCMDTYPE>\n\
            <MSLOGIN>%3%</MSLOGIN>\n\
            <MSGETLIET>%4%</MSGETLIET>\n\
            </MONITOR_STATION>\n\
            </MD>");
        fmt2 %strStationID %strCmdType %strLogin %strGetLite;
        DOperXML::m_strXml_Login = fmt2.str();
    }
    return DOperXML::m_strXml_Login;
}
std::string DOperXML::GetXmlStr_ConnDev(const string& strStationID, const string& strCmdType, const string& strDevID)
{
    if (DOperXML::m_strXml_ConnDev.empty())
    {
        boost::format fmt2("<?xml version=\"1.0\" encoding=\"utf - 8\"?>\n\
            <MD>\n\
            <MONITOR_STATION ID = \"%1%\">\n\
            <MSCMDTYPE>%2%</MSCMDTYPE>\n\
            <MSDEVID>%3%</MSDEVID>\n\
            </MONITOR_STATION>\n\
            </MD>");
        fmt2 %strStationID %strCmdType% strDevID;
        DOperXML::m_strXml_ConnDev = fmt2.str();
    }
    return DOperXML::m_strXml_ConnDev;
}

std::string DOperXML::GetXmlStr_ConnDev_Heart(const string& strStationID, const string& strCmdType)
{
    if (DOperXML::m_strXml_ConnDev_Heart.empty())
    {
        boost::format fmt2("<?xml version=\"1.0\" encoding=\"utf - 8\"?>\n\
            <MD>\n\
            <MONITOR_STATION ID = \"%1%\">\n\
            <MSCMDTYPE>%2%</MSCMDTYPE>\n\
            </MONITOR_STATION>\n\
            </MD>");
        fmt2 %strStationID %strCmdType;
        DOperXML::m_strXml_ConnDev_Heart = fmt2.str();
    }
    return DOperXML::m_strXml_ConnDev_Heart;
}
