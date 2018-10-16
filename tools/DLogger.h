#pragma once
#include <sstream>
#include <iostream>
using namespace std;
//
#include <stdexcept>
#include <string>
#include <iostream>
#include <fstream>
#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/thread/thread.hpp>
#include <boost/thread/barrier.hpp>

#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>

#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/named_scope.hpp>

#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

using boost::shared_ptr;

enum severity_level
{
    normal,
    warning,
    error,
    critical
};

template< typename CharT, typename TraitsT >
inline std::basic_ostream< CharT, TraitsT >& operator<< (
    std::basic_ostream< CharT, TraitsT >& strm, severity_level lvl)
{
    static const char* const str[] =
    {
        "normal",
        "warning",
        "error",
        "critical"
    };
    if (static_cast<std::size_t>(lvl) < (sizeof(str) / sizeof(*str)))
        strm << str[lvl];
    else
        strm << static_cast<int>(lvl);
    return strm;
}

class DLogger
{
public:

    enum eOutTag
    {
        eOutTag_Console = 0x0001,
        eOutTag_File = 0x0002,
        eOutTag_NotOut = 0x1000,
    };

    static bool InitLog(int nTag, const string &strLogFile = "");
    static void ReleaseLog();



    static src::severity_logger_mt<severity_level> GetLogger();

    /*using namespace std;
    ostringstream ostr;
    ostr << "d = " << 123 << "f = " << 12.345 << "test format" << std:endl;
    string str = ostr.str();
    cout << ostr.str().c_str()*/

private:
    DLogger();
    virtual ~DLogger();

    static void Normal(const string &strlog);
    static void Warning(const string &strlog);
    static void Error(const string &strlog);
    static void Critical(const string &strlog);

    static void OutPutLogByLvl(const string &strlog, severity_level lvl);

};



#define DLog_Normal \
    BOOST_LOG_FUNCTION(); \
    BOOST_LOG_SEV(DLogger::GetLogger(), normal)

#define DLog_Warning \
    BOOST_LOG_FUNCTION(); \
    BOOST_LOG_SEV(DLogger::GetLogger(), warning)

#define DLog_Error\
    BOOST_LOG_FUNCTION(); \
    BOOST_LOG_SEV(DLogger::GetLogger(), error)

#define DLog_Critical \
    BOOST_LOG_FUNCTION(); \
    BOOST_LOG_SEV(DLogger::GetLogger(), critical)
