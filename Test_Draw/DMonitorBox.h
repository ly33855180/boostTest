#pragma once

#include <boost/asio/placeholders.hpp>
#include <boost/system/error_code.hpp>
#include <boost/bind/bind.hpp>
#include <boost/asio.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/scoped_ptr.hpp>

using namespace boost;
using namespace boost::asio;

//解析xml;
#include "DData.h"
#include <iostream>
#include <string>
#include <boost/property_tree/xml_parser.hpp>

#include <boost/function.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using boost::property_tree::ptree;
using namespace std;

typedef boost::asio::ip::tcp::socket socket_type;
typedef boost::shared_ptr<socket_type> sock_ptr;



class DMonitorBox :public boost::enable_shared_from_this<DMonitorBox>
{
public:

    enum ETimeOutType
    {
        ETimeOutType_Conn = 0,
        ETimeOutType_Write,
        ETimeOutType_Read,
    };

    DMonitorBox();
    virtual ~DMonitorBox();
    bool StartMonitor();
    bool StopMonitor();
    bool IsMonitoring();
    void SetBoxInfo(const sMonFrame & monFrame);


private:
    bool m_bMonitor;

    void conn_handler(const boost::system::error_code&ec, sock_ptr sock);
    void write_handler(const boost::system::error_code&ec, sock_ptr sock);
    void read_handle(const boost::system::error_code& ec, std::size_t bytes_transferred,vector<unsigned char>& vecReadBuf);
    void TimeOut(const boost::system::error_code&, boost::asio::deadline_timer* t, ETimeOutType eTimeOutType);

    boost::function<void(const s_Md &, bool)> m_callbackfun;//保存回调函数;
    int m_nReconnCount;//重连次数;


    boost::asio::io_service m_ioTimer;//定时器io;
    boost::shared_ptr<boost::asio::deadline_timer> m_ptrTimer;//定时器;
    bool m_bConnState;

private:
    boost::scoped_ptr<boost::asio::io_service::work> m_work;
    io_service m_io;
    ip::tcp::endpoint m_ep;
    sock_ptr m_sockPtr;
    boost::asio::streambuf response;

    std::vector<unsigned char> m_vecReadBuf;
    std::vector<unsigned char> m_vecRecvData;
    sMonFrame  m_monFrame;
};

