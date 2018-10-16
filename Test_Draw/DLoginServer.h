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

//����xml;
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

enum ETimeOutType
{
    ETimeOutType_Conn = 0,
    ETimeOutType_Write,
    ETimeOutType_Read,
};

class DLoginServer :public boost::enable_shared_from_this<DLoginServer>
{
public:
	

	DLoginServer();
	~DLoginServer();

    bool m_bSopStartGetMdData;
	void StartGetMdData(boost::function<void(const s_Md &, bool)> callbackfun);
    void StopStartGetMdData();

	void conn_handler(const boost::system::error_code&ec, sock_ptr sock);
	void write_handler(const boost::system::error_code&ec, sock_ptr sock);
	void read_handle(const boost::system::error_code& ec, std::size_t bytes_transferred);
    void TimeOut(const boost::system::error_code&, boost::asio::deadline_timer* t, ETimeOutType eTimeOutType);


private:
    boost::scoped_ptr<boost::asio::io_service::work> m_work;
	io_service m_io;
	ip::tcp::endpoint m_ep;
	sock_ptr m_sockPtr;
	boost::asio::streambuf response;

	/*����xml*/
	void parseXML();

	void GetItem(const ptree &ptParent ,sItem &item);
	void GetCandidateInfo(const ptree &ptParent, sCandidateInfo& candidateInfo);
	void GetMonFrame(const ptree &ptParent, sMonFrame& monFrame);
	void GetMonitorStation(const ptree &ptParent, sMonitorStation& monitorStation);
	void GetMD(const ptree &ptParent, s_Md& md);


    boost::function<void(const s_Md &, bool)> m_callbackfun;//����ص�����;
    int m_nReconnCount;//��������;


    boost::asio::io_service m_ioTimer;//��ʱ��io;
    boost::shared_ptr<boost::asio::deadline_timer> m_ptrTimer;//��ʱ��;
    bool m_bConnState;
};
