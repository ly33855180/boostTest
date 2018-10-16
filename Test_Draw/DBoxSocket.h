#pragma once
#include <string>

#include <boost/bind.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp> 
#include <iostream>  
#include <boost/property_tree/xml_parser.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/asio/placeholders.hpp>
#include <boost/system/error_code.hpp>
#include <boost/asio.hpp>

#include <boost/enable_shared_from_this.hpp>
#include <boost/scoped_ptr.hpp>
#include "DParseData.h"
using boost::property_tree::ptree;
using namespace std;

typedef boost::asio::ip::tcp::socket socket_type;
typedef boost::shared_ptr<socket_type> sock_ptr;

using namespace boost;
using namespace boost::asio;


#include "DData.h"

class DBoxSocket : public boost::enable_shared_from_this<DBoxSocket>
{
public:

    enum ETimeOutType
    {
        ETimeOutType_Conn = 0,
        ETimeOutType_Write,
        ETimeOutType_Read,
    };

    DBoxSocket(io_service& io, std::string strIP, int nPort);
    virtual ~DBoxSocket();

    void StartGetMdData();
	void StopStartGetMdData();
	void SetMonFrame(const sMonFrame & monFrame);
	sMonFrame m_sMonFrame;
private:
    boost::thread m_thread;
    std::string m_strIP;
    int m_nPort;

    bool m_bWillQuite;
    boost::thread m_thParse;
    void parse_handler();


    void ConnectServer();

    void conn_handler(const boost::system::error_code&ec, sock_ptr sock);
    void write_handler(const boost::system::error_code&ec, sock_ptr sock);
    void read_handle(const boost::system::error_code& ec, std::size_t bytes_transferred);

    void TimeOut(const boost::system::error_code&, boost::asio::deadline_timer* t, ETimeOutType eTimeOutType);

private:
    io_service& m_io;
    ip::tcp::endpoint m_ep;
    sock_ptr m_sockPtr;
    boost::asio::streambuf response;

	io_service::strand m_strand;
	

    int m_nReconnCount;//重连次数;
    boost::shared_ptr<boost::asio::deadline_timer> m_ptrTimer;//定时器;
    bool m_bConnState;

    std::vector<unsigned char> m_vecRecvBufTemp;
public:
    std::vector<unsigned char> m_vecRecvBuf;


    DParseData m_parseData;

	bool AddObserverWidID(unsigned int nWidID, boost::function<void(const sPackageData &, int)> callbackfun);
	bool RemoveObserverWidID(unsigned int nWidID, boost::function<void(const sPackageData &, int)> callbackfun);
private:
    std::vector<sPackageData> m_vecPackageData;
};

typedef boost::shared_ptr<DBoxSocket> DBoxSocketPtr;