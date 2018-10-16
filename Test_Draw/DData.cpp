#include "DData.h"

sServerInfo::sServerInfo()
{

}

std::string sServerInfo::GetIP()
{
    return m_strIP;

}

int sServerInfo::GetPort()
{
    return m_nPort;
}

string sServerInfo::m_strIP = "192.168.0.183";
int sServerInfo::m_nPort = 4004;