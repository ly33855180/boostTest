#include "DMonitorBox.h"
#include <boost/asio/streambuf.hpp>
#include <boost/regex.hpp>
#include <boost/asio/read_until.hpp>
#include "..\\tools\\DLogger.h"
#include "DOperXML.h"
#include <boost/array.hpp>




DMonitorBox::DMonitorBox():m_ep(ip::address::from_string(sServerInfo::GetIP()), sServerInfo::GetPort())
    ,m_bConnState(false)
{
    m_vecReadBuf.resize(1024 * 10);
}


DMonitorBox::~DMonitorBox()
{
}

bool DMonitorBox::StartMonitor()
{
    m_sockPtr = sock_ptr(new socket_type(m_io));
    m_sockPtr->async_connect(m_ep, boost::bind(&DMonitorBox::conn_handler, shared_from_this(), boost::asio::placeholders::error, m_sockPtr));

    m_ptrTimer = boost::shared_ptr<boost::asio::deadline_timer>(new boost::asio::deadline_timer(m_io, boost::posix_time::seconds(10)));
    m_ptrTimer->async_wait(boost::bind(&DMonitorBox::TimeOut, this, boost::asio::placeholders::error, m_ptrTimer.get(), ETimeOutType_Conn));

    m_work.reset(new boost::asio::io_service::work(m_io));
    m_io.run();
    return true;
}

bool DMonitorBox::StopMonitor()
{
    if (m_ptrTimer)
    {
        m_ptrTimer->cancel();
    }
    if (m_sockPtr)
    {
        m_sockPtr->close();
    }
    m_work.reset();
    m_io.stop();
    return true;
}

bool DMonitorBox::IsMonitoring()
{
    return m_bMonitor;
}

void DMonitorBox::SetBoxInfo(const sMonFrame & monFrame)
{
    //m_monFrame = monFrame;
    //m_monFrame.m_arrValue[sMonFrame::eMF_DEV_IDX];
}

void DMonitorBox::conn_handler(const boost::system::error_code&ec, sock_ptr sock)
{
    if (ec)
    {
        DLog_Normal << "conn_handler error!"<<ec.message();
        m_bConnState = false;
        return;
    }
    DLog_Normal << "DMonitorBox::conn_handler() 连接服务器成功！";
    m_bConnState = true;

    string str = DOperXML::Init()->GetXmlStr_ConnDev("001", "2", "C341701001");
    m_sockPtr->async_write_some(boost::asio::buffer(str.data(), str.length()), boost::bind(&DMonitorBox::write_handler, shared_from_this(), boost::asio::placeholders::error, m_sockPtr));
}

void DMonitorBox::write_handler(const boost::system::error_code&ec, sock_ptr sock)
{
    if (ec)
    {
        DLog_Normal << "write_handler error!";
        return;
    }

    std::fill(m_vecReadBuf.begin(), m_vecReadBuf.end(), 0);
    m_sockPtr->async_read_some(boost::asio::buffer(m_vecReadBuf), boost::bind(&DMonitorBox::read_handle, shared_from_this(),boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, m_vecReadBuf));

}

void DMonitorBox::read_handle(const boost::system::error_code & ec, std::size_t bytes_transferred, vector<unsigned char>& vecReadBuf)
{
    if (ec)
    {
        DLog_Normal << "DMonitorBox::read_handle, error = " << ec.message();
    }
    DLog_Normal << "bytes_transferred = " << bytes_transferred << endl;

    //m_vecRecvData.resize(m_vecRecvData.size() + bytes_transferred);
    m_vecRecvData.insert(m_vecRecvData.end(), m_vecReadBuf.begin(), m_vecReadBuf.end()); 

    for (size_t i = 0; i < m_vecRecvData.size(); i++)
    {
        cout << m_vecRecvData.at(i) << ",";
    }
    std::fill(m_vecReadBuf.begin(), m_vecReadBuf.end(), 0);
    m_sockPtr->async_read_some(boost::asio::buffer(m_vecReadBuf), boost::bind(&DMonitorBox::read_handle, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, m_vecReadBuf));
}


void DMonitorBox::TimeOut(const boost::system::error_code& e, boost::asio::deadline_timer* t, ETimeOutType eTimeOutType)
{
    return;
    if (e)
    {
        DLog_Normal << "定时器！ error = " << e.message();
    }

    if (!t || !m_sockPtr)
    {
        DLog_Normal << "定时器！ error = (!t || !m_sockPtr)";
        return;
    }

    if (ETimeOutType_Conn == eTimeOutType)
    {
        if (m_bConnState)
        {
            DLog_Normal << "DMonitorBox 连接服务器成功！发送心跳！";

            string str = DOperXML::Init()->GetXmlStr_ConnDev_Heart("001","2");
            m_sockPtr->async_write_some(boost::asio::buffer(str.data(), str.length()), boost::bind(&DMonitorBox::write_handler, shared_from_this(), boost::asio::placeholders::error, m_sockPtr));
        }
        else
        {
            if (m_nReconnCount++ < 5)
            {
                DLog_Normal << "连接服务器超时!尝试第" << m_nReconnCount << "次连接...";
                m_sockPtr->async_connect(m_ep, boost::bind(&DMonitorBox::conn_handler, shared_from_this(), boost::asio::placeholders::error, m_sockPtr));
            }
            else
            {
                DLog_Normal << "连接服务器超时!尝试第" << m_nReconnCount << "次连接...,停止连接！";
                m_nReconnCount = 0;
                return;
            }
        }

        t->expires_at(t->expires_at() + boost::posix_time::seconds(5));
        t->async_wait(boost::bind(&DMonitorBox::TimeOut, this, boost::asio::placeholders::error, t, eTimeOutType));
    }
}
