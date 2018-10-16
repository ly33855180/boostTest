#include "DLoginServer.h"
#include <iostream>
#include <sstream>


#include "QTextStream.h"
#include "QFile"

#include <boost/asio/streambuf.hpp>
#include <boost/regex.hpp>
#include <boost/asio/read_until.hpp>
#include <boost/smart_ptr\enable_shared_from_this.hpp>

#include <boost/asio/buffer.hpp>

#include <boost/array.hpp>
boost::array<char, 4096> response_;
boost::regex m_regex("\N");
#include <boost/format.hpp>

#include <boost/property_tree/detail/xml_parser_write.hpp>

#include <boost/typeof/typeof.hpp>
#include <boost/make_shared.hpp>

#include <istream>
//#include <fstream.h>
#include "..\\tools\\DLogger.h"
#define  ReconnCount 10

#include "DOperXML.h"

#include <qDebug>

DLoginServer::DLoginServer(): m_ep(ip::address::from_string(sServerInfo::GetIP()), sServerInfo::GetPort())
, m_nReconnCount(0)
, m_bSopStartGetMdData(false)
, m_bConnState(false)
{
}

DLoginServer::~DLoginServer()
{
	cout << "DLoginServer::~DLoginServer()" << endl;
}


void DLoginServer::StartGetMdData(boost::function<void(const s_Md &, bool)> callbackfun)
{

    m_callbackfun = callbackfun;
	m_sockPtr = sock_ptr(new socket_type(m_io));
	m_sockPtr->async_connect(m_ep, boost::bind(&DLoginServer::conn_handler, shared_from_this(), boost::asio::placeholders::error, m_sockPtr));

    m_ptrTimer = boost::shared_ptr<boost::asio::deadline_timer>(new boost::asio::deadline_timer(m_io, boost::posix_time::seconds(10)));
    m_ptrTimer->async_wait(boost::bind(&DLoginServer::TimeOut, shared_from_this(), boost::asio::placeholders::error, m_ptrTimer.get(), ETimeOutType_Conn));
    
    

    m_work.reset(new boost::asio::io_service::work(m_io));
    m_io.run();
}

void DLoginServer::conn_handler(const boost::system::error_code & ec, sock_ptr sock)
{
	if (!sock)
	{
		DLog_Normal << "conn_handler! error: sock is NULL!";
		m_bConnState = false;
		return;
	}
	if (ec)
	{
        DLog_Normal << "conn_handler! error = "<< ec.message();
        m_bConnState = false;
		return;
	}
    DLog_Normal << "conn_handler! success!";

    string str = DOperXML::Init()->GetXmlStr_Login("001", "1", "login", "2");
	//sock->async_write_some(boost::asio::buffer(str.data(), str.length()), boost::bind(&DLoginServer::write_handler, shared_from_this(), boost::asio::placeholders::error, sock));
	try
	{
		system::error_code ignored_error;
		std::size_t nWriteSize = sock->write_some(boost::asio::buffer(str.data(), str.length()), ignored_error);
		DLog_Normal << "conn_handler, write_some write = " << str<< ", size =" << nWriteSize;
		if (ignored_error)
		{
			DLog_Normal << "conn_handler,write_some error = " << ignored_error.message();
			m_bConnState = false;
			return;
		}

		boost::regex expr;
		expr.assign("</MD>|OK");

		response.consume(response.size());
		boost::asio::async_read_until(*sock.get(), response, expr, boost::bind(&DLoginServer::read_handle, shared_from_this(), _1, _2));
		m_bConnState = true;
		DLog_Normal << "conn_handler! write_some, success!";
	}
	catch (std::exception& e)
	{
		DLog_Normal << "conn_handler write_some catch error: "<<e.what();
		m_bConnState = false;
		return;
	}

}


void DLoginServer::write_handler(const boost::system::error_code&ec, sock_ptr sock)
{
	if (ec)
	{
        DLog_Normal << "write_handler！error = " << ec.message();
		return;
	}
    boost::regex expr;
    expr.assign("</MD>|OK");

    response.consume(response.size());
    boost::asio::async_read_until(*sock.get(), response, expr, boost::bind(&DLoginServer::read_handle, shared_from_this(), _1, _2));
}



void DLoginServer::read_handle(const boost::system::error_code& ec, std::size_t bytes_transferred)
{
	boost::asio::streambuf::const_buffers_type cbt = response.data();
	std::string request_data(boost::asio::buffers_begin(cbt), boost::asio::buffers_end(cbt));
	//DLog_Normal << "request_data="<< request_data <<",size="<< request_data.size()<< ", bytes_transferred=" << bytes_transferred;

    if (request_data == "OK")
    {
		DLog_Normal << "read_handle request_data = ok!" << endl;
        return;
    }

	if (request_data.empty() || (0 == bytes_transferred))
	{
		DLog_Normal << "read_handle request_data is empty or bytes_transferred is 0!" << endl;
		return;
	}
	ptree pt_MD;
	s_Md md;
	try {

        std::istringstream s1(request_data);
        std::istream s2(s1.rdbuf());

        read_xml(s2, pt_MD);

		if (pt_MD.empty())
		{
			DLog_Normal << "read_handle pt_MD is empty!" << endl;
			return;
		}
		auto findPos = pt_MD.find("MD");
		GetMD(findPos->second, md);

        if (m_callbackfun)
        {
            m_callbackfun(md, true);
        }
		s1.clear();
		s2.clear();
		request_data.clear();

	}
	catch (std::exception& e)
	{
		DLog_Normal << " read_handle Error:" << e.what();
	}
	pt_MD.clear();
}

void DLoginServer::parseXML()
{

}

void DLoginServer::GetItem(const ptree &ptParent, sItem &item)
{
	item.m_qsIDX     = QString(ptParent.get<string>("IDX", "").c_str());
	item.m_qsID_CODE = QString(ptParent.get<string>("ID_CODE", "").c_str());
	item.m_qsDB_ID   = QString(ptParent.get<string>("DB_ID", "").c_str());
	item.m_qsCAPTION = QString(ptParent.get<string>("CAPTION", "").c_str());
	item.m_qsCONTENT = QString(ptParent.get<string>("CONTENT", "").c_str());
}

void DLoginServer::GetCandidateInfo(const ptree &ptParent, sCandidateInfo& candidateInfo)
{
	for (BOOST_AUTO(pos, ptParent.begin()); pos != ptParent.end(); ++pos)
	{
		if ("<xmlattr>" == pos->first)//属性
		{
			continue;
		}
		else if ("<xmlcomment>" == pos->first)//注释
		{
			continue;
		}
		else
		{
			sItem item;
			GetItem(pos->second, item);
            candidateInfo.m_vecItem.push_back(item);
		}
	}
}

void DLoginServer::GetMonFrame(const ptree &ptParent, sMonFrame& monFrame)
{

	monFrame.m_qsNO           = QString(ptParent.get<string>("NO", "").c_str());
	monFrame.m_qsDEV_IDX      = QString(ptParent.get<string>("DEV_IDX", "").c_str());
	monFrame.m_qsDEV_IP       = QString(ptParent.get<string>("DEV_IP", "").c_str());
	monFrame.m_qsDEV_PORT     = QString(ptParent.get<string>("DEV_PORT", "").c_str());
	monFrame.m_qsVALID_DATE   = QString(ptParent.get<string>("VALID_DATE", "").c_str());
	monFrame.m_qsDEV_TYPE     = QString(ptParent.get<string>("DEV_TYPE", "").c_str());
	monFrame.m_qsDEV_FORMATID = QString(ptParent.get<string>("DEV_FORMATID", "").c_str());
	monFrame.m_qsDEV_STATUS   = QString(ptParent.get<string>("DEV_STATUS", "").c_str());
	monFrame.m_qsDEV_STUDYID  = QString(ptParent.get<string>("DEV_STUDYID", "").c_str());

    monFrame.m_nNo = monFrame.m_qsNO.toInt();

	sCandidateInfo candidateInfo;
	auto findPos = ptParent.find("CANDIDATE_INFO");
	GetCandidateInfo(findPos->second, candidateInfo);
	monFrame.m_sCandidateInfo = candidateInfo;
			
}

void DLoginServer::GetMonitorStation(const ptree &ptParent, sMonitorStation& monitorStation)
{

	monitorStation.m_qsECGrealtimemonitorbuffer = QString(ptParent.get<string>("<xmlattr>.ECGrealtimemonitorbuffer", "").c_str());
	monitorStation.m_qsID                       = QString(ptParent.get<string>("<xmlattr>.ID", "").c_str());
	monitorStation.m_qsMinimalECGdisplaytime    = QString(ptParent.get<string>("<xmlattr>.MinimalECGdisplaytime", "").c_str());
	monitorStation.m_qsCOUNT                    = QString(ptParent.get<string>("<xmlattr>.COUNT", "").c_str());
	monitorStation.m_qsRIGHT                    = QString(ptParent.get<string>("<xmlattr>.RIGHT", "").c_str());

	for (BOOST_AUTO(pos, ptParent.begin()); pos != ptParent.end(); ++pos)
	{
		if ("<xmlattr>" == pos->first)//属性
		{
			continue;
		}
		else if ("<xmlcomment>" == pos->first)//注释
		{
			continue;
		}
		else
		{
			sMonFrame monFrame;
			GetMonFrame(pos->second, monFrame);
			monitorStation.m_vecMonFrame.push_back(monFrame);
		}
	}
    std::sort(monitorStation.m_vecMonFrame.begin(), monitorStation.m_vecMonFrame.end(), [](sMonFrame m0, sMonFrame m1) 
    {
        return (m0.m_nNo < m1.m_nNo);
    });

	int nIndex = 1;
	for_each(monitorStation.m_vecMonFrame.begin(), monitorStation.m_vecMonFrame.end(), [&nIndex](sMonFrame & m0)
	{
		m0.m_nNo = nIndex++;
	});

}

void DLoginServer::GetMD(const ptree &ptParent, s_Md& md)
{
	for (BOOST_AUTO(pos, ptParent.begin()); pos != ptParent.end(); ++pos)
	{
		//cout << "pos->frist = " << pos->first << endl;
		if ("<xmlattr>" == pos->first)//属性
		{
			continue;
		}
		else if ("<xmlcomment>" == pos->first)//注释
		{
			continue;
		}
		else if ("SERVICE_TYPE" == pos->first)
		{
			md.m_qsSERVICE_TYPE = QString(pos->second.data().c_str());
		}
		else if ("MONITOR_STATION" == pos->first)
		{
			sMonitorStation monitorStation;
			GetMonitorStation(pos->second, monitorStation);
			md.m_vecMonitorStation.push_back(monitorStation);
		}
	}
}

void DLoginServer::StopStartGetMdData()
{
    if (m_ptrTimer)
    {
        m_ptrTimer->cancel();
    }
    if (m_sockPtr)
    {
        m_sockPtr->close();
        m_sockPtr = sock_ptr();
    }
    m_work.reset();
    m_io.stop();
}

void DLoginServer::TimeOut(const boost::system::error_code& e, boost::asio::deadline_timer* t, ETimeOutType eTimeOutType)
{
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
            //DLog_Normal << "连接服务器成功！发送心跳！" ;

            string str = DOperXML::Init()->GetXmlStr_ConnDev_Heart("001","3");
            //m_sockPtr->async_write_some(boost::asio::buffer(str.data(), str.length()), boost::bind(&DLoginServer::write_handler, shared_from_this(), boost::asio::placeholders::error, m_sockPtr));

			try
			{
				system::error_code ignored_error;
				std::size_t nWriteSize = m_sockPtr->write_some(boost::asio::buffer(str.data(), str.length()), ignored_error);
				DLog_Normal << "TimeOut, write_some write = " << str << ", size =" << nWriteSize;
				if (ignored_error)
				{
					DLog_Normal << "TimeOut, write_some error = " << ignored_error.message();
					m_bConnState = false;
				}
				DLog_Normal << "TimeOut! write_some, success!";
			}
			catch (std::exception& e)
			{
				DLog_Normal << "conn_handler write_some catch error: " << e.what();
				m_bConnState = false;
				return;
			}

        }
        else
        {
            if(true)/*if (m_nReconnCount++ < 10)*/
            {
				m_nReconnCount++;
                DLog_Normal << "连接服务器超时!尝试第"<< m_nReconnCount <<"次连接...";
				m_sockPtr->close();
				m_sockPtr = sock_ptr(new socket_type(m_io));
                m_sockPtr->async_connect(m_ep, boost::bind(&DLoginServer::conn_handler, shared_from_this(), boost::asio::placeholders::error, m_sockPtr));
            }
            else
            {
                DLog_Normal << "连接服务器超时!尝试第" << m_nReconnCount << "次连接...,停止连接！";
                m_nReconnCount = 0;
                return;
            }
        }

        t->expires_at(t->expires_at() + boost::posix_time::seconds(5));
        t->async_wait(boost::bind(&DLoginServer::TimeOut, this, boost::asio::placeholders::error, t, eTimeOutType));
    }
}
