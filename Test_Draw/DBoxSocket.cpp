#include "DBoxSocket.h"
#include "DParseData.h"
#define ReadBufSize 8192
#define SleepTime   1000

#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>

#include "..\\tools\\DLogger.h"
DBoxSocket::DBoxSocket(io_service& io, std::string strIP, int nPort) : m_ep(ip::address::from_string(strIP), nPort)
, m_nReconnCount(0)
, m_bConnState(false)
, m_bWillQuite(false)
, m_io(io)
, m_strand(io)
{
    m_strIP = strIP;
    m_nPort = nPort;
}

DBoxSocket::~DBoxSocket()
{
	DLog_Normal << "DBoxSocket::~DBoxSocket()";
}

void DBoxSocket::ConnectServer()
{
	m_sockPtr = sock_ptr(new socket_type(m_io));
	m_sockPtr->async_connect(m_ep, boost::bind(&DBoxSocket::conn_handler, shared_from_this(), boost::asio::placeholders::error, m_sockPtr));

	m_ptrTimer = boost::shared_ptr<boost::asio::deadline_timer>(new boost::asio::deadline_timer(m_io, boost::posix_time::seconds(10)));
	m_ptrTimer->async_wait(boost::bind(&DBoxSocket::TimeOut, this, boost::asio::placeholders::error, m_ptrTimer.get(), ETimeOutType_Conn));

}

void DBoxSocket::conn_handler(const boost::system::error_code&ec, sock_ptr sock)
{
    if (ec)
    {
        m_bConnState = false;
        std::cout << "连接服务器失败！error = " << ec.message();
        return;
    }
    m_bConnState = true;
    std::string str = "<?xml version = \"1.0\" encoding = \"utf-8\"?>\n\
<MD>\n\
<MONITOR_STATION ID = \"001\">\n\
<MSCMDTYPE>2</MSCMDTYPE>\n\
<MSDEVID>C341701188</MSDEVID>\n\
</MONITOR_STATION>\n\
</MD>";

	//
	try
	{
		system::error_code ignored_error;
		std::size_t nWriteSize = m_sockPtr->write_some(boost::asio::buffer(str.data(), str.length()), ignored_error);
		DLog_Normal << "conn_handler, write_some write = " << str << ", size =" << nWriteSize;
		if (ignored_error)
		{
			DLog_Normal << "conn_handler,write_some error = " << ignored_error.message();
			m_bConnState = false;
			return;
		}
		m_bConnState = true;
		DLog_Normal << "conn_handler! write_some, success! start async_read_some";

		if (m_sockPtr)
		{
			m_sockPtr->async_read_some(boost::asio::buffer(m_vecRecvBufTemp), boost::bind(&DBoxSocket::read_handle, shared_from_this(), _1, _2));
		}
	}
	catch (std::exception& e)
	{
		DLog_Normal << "conn_handler write_some catch error: " << e.what();
		m_bConnState = false;
		return;
	}
	//

}

void DBoxSocket::write_handler(const boost::system::error_code&ec, sock_ptr sock)
{
    if (ec)
    {
        std::cout << "write_handler! error = " << ec.message();
        return;
    }
    std::cout << "write_handler()!  success! " << endl;
    if (m_ptrTimer)
    {
        //m_ptrTimer->cancel();
    }

    m_vecRecvBufTemp.clear();
    m_vecRecvBufTemp.resize(2064);

    if (m_sockPtr)
    {
        m_sockPtr->async_read_some(boost::asio::buffer(m_vecRecvBufTemp), boost::bind(&DBoxSocket::read_handle, shared_from_this(), _1, _2));
    }
}
boost::mutex g_readMutex;
void DBoxSocket::read_handle(const boost::system::error_code& ec, std::size_t bytes_transferred)
{
	if (m_bWillQuite)
	{
		return;
	}
    if (ec)
    {
       // std::cout << "read_handle! error = " << ec.message() << endl;
        return;
    }

    //std::cout << "read_handle!success! bytes_transferred = " << bytes_transferred<<endl;

    if (0 == bytes_transferred)
    {
        //std::cout << "read_handle! error = bytes_transferred is 0!" << endl;
        //return;
    }

   // boost::lock_guard<boost::mutex> lock(g_readMutex);
    m_vecRecvBuf.reserve(m_vecRecvBuf.size() + bytes_transferred);
    m_vecRecvBuf.insert(m_vecRecvBuf.end(), m_vecRecvBufTemp.begin(), m_vecRecvBufTemp.end());
   // std::cout << "read_handle! m_vecRecvBuf = "<< m_vecRecvBuf.size() << endl;
    m_vecRecvBufTemp.clear();
    m_vecRecvBufTemp.resize(2064);

	m_strand.post(boost::bind(&DBoxSocket::parse_handler, shared_from_this()));

    //Sleep(SleepTime);
    if (m_sockPtr)
    {
        m_sockPtr->async_read_some(boost::asio::buffer(m_vecRecvBufTemp), boost::bind(&DBoxSocket::read_handle, shared_from_this(), _1, _2));
    }
}

void DBoxSocket::StartGetMdData()
{
    m_thread = boost::thread(boost::bind(&DBoxSocket::ConnectServer, shared_from_this()));

   // m_thParse = boost::thread(boost::bind(&DBoxSocket::parse_handler, shared_from_this()));
}
                                                                                                                                                                                                                                                                   
void DBoxSocket::StopStartGetMdData()
{
    m_bWillQuite = true;


    if (m_ptrTimer)
    {
        m_ptrTimer->cancel();
    }

    if (m_sockPtr)
	{
        m_sockPtr->close();
        m_sockPtr = sock_ptr();
    }

	m_thread.join();
	//m_thParse.join();

	m_vecRecvBufTemp.clear();
	m_vecRecvBufTemp.swap(std::vector<unsigned char>());

	m_vecRecvBuf.clear();
	m_vecRecvBuf.swap(std::vector<unsigned char>());
}

void DBoxSocket::TimeOut(const boost::system::error_code& e, boost::asio::deadline_timer* t, ETimeOutType eTimeOutType)
{
    if (e)
    {
       std::cout << "定时器！ error = " << e.message()<<endl;
       return;
    }

    if (!t || !m_sockPtr)
    {
        std::cout << "定时器！ error = (!t || !m_sockPtr)" << endl;
        return;
    }

    if (ETimeOutType_Conn == eTimeOutType)
    {
        if (m_bConnState)
        {
            std::cout << "定时器,连接成功! m_nReconnCount = " << m_nReconnCount << endl;
            t->cancel();
            return;
        }
        else
        {
            if(1)/* if (m_nReconnCount++ < 5)*/
            {
                std::cout << "连接服务器超时!尝试第" << m_nReconnCount << "次连接...";
                m_sockPtr->async_connect(m_ep, boost::bind(&DBoxSocket::conn_handler, shared_from_this(), boost::asio::placeholders::error, m_sockPtr));

                t->expires_at(t->expires_at() + boost::posix_time::seconds(10));
                t->async_wait(boost::bind(&DBoxSocket::TimeOut, this, boost::asio::placeholders::error, t, eTimeOutType));
            }
            else
            {
                std::cout << "连接服务器超时!尝试第" << m_nReconnCount << "次连接...,停止连接！";
                t->cancel();
            }
        }
    }
}

void DBoxSocket::parse_handler()
{
	if (m_bWillQuite)
	{
		return;
	}
	m_parseData.StartParse(m_vecRecvBuf);
	return;
    while (!m_bWillQuite)
    {
        if (m_vecRecvBuf.size() > 18)//最少18个字节的包
        {
			//boost::lock_guard<boost::mutex> lock(g_readMutex);
            //m_parseData.StartParse(m_vecRecvBuf);
            Sleep(SleepTime);
        }
    }
}

void DBoxSocket::SetMonFrame(const sMonFrame & monFrame)
{
	m_sMonFrame = monFrame;
	this->StartGetMdData();
}

bool DBoxSocket::AddObserverWidID(unsigned int nWidID, boost::function<void(const sPackageData &, int)> callbackfun)
{
	m_parseData.AddObserverWidID(nWidID, callbackfun);
	return true;
}

bool DBoxSocket::RemoveObserverWidID(unsigned int nWidID, boost::function<void(const sPackageData &, int)> callbackfun)
{
	m_parseData.RemoveObserverWidID(nWidID, callbackfun);
	return true;
}
