#include "DLogger.h"




#include  <direct.h>  
#include  <stdio.h> 




enum
{
    LOG_RECORDS_TO_WRITE = 100,
    THREAD_COUNT = 3
};

BOOST_LOG_ATTRIBUTE_KEYWORD(_moduleName, "ModuleName", std::string)
BOOST_LOG_ATTRIBUTE_KEYWORD(_severity, "Severity", severity_level)
BOOST_LOG_ATTRIBUTE_KEYWORD(_timestamp, "TimeStamp", boost::posix_time::ptime)
BOOST_LOG_ATTRIBUTE_KEYWORD(_uptime, "Uptime", attrs::timer::value_type)
BOOST_LOG_ATTRIBUTE_KEYWORD(_scope, "Scope", attrs::named_scope::value_type)


BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(g_log, src::severity_logger_mt<severity_level>)
//! This function is executed in multiple threads
void thread_fun(boost::barrier& bar)
{
    /*BOOST_LOG_FUNCTION();*/
    // Wait until all threads are created
    bar.wait();
    BOOST_LOG_FUNCTION();
    // Now, do some logging
    for (unsigned int i = 0; i < LOG_RECORDS_TO_WRITE; ++i)
    {
        BOOST_LOG_SEV(g_log::get(), normal) << "Log record " << i;
        BOOST_LOG_SEV(g_log::get(), warning) << "Log record " << i;
        BOOST_LOG_SEV(g_log::get(), error) << "Log record " << i;
        BOOST_LOG_SEV(g_log::get(), critical) << "Log record " << i;
    }
}
DLogger::DLogger()
{
    
}


DLogger::~DLogger()
{

}



bool DLogger::InitLog(int ntag,const string& strFilePath)
{
    if (ntag & DLogger::eOutTag_NotOut)
    {
        return false;

    }

    logging::formatter formatter =
#pragma region 初始化fomatter

        expr::stream
        << expr::format_date_time(_timestamp, "[%Y-%m-%d %H:%M:%S.%f]")
        /*ThreadID*/
        << expr::if_(expr::has_attr< attrs::current_thread_id::value_type  >("ThreadID"))
        [
            expr::stream << "[" << expr::attr< attrs::current_thread_id::value_type >("ThreadID") << "]"
        ]
    .else_
        [
            expr::stream << ""
        ]
    /*Scope*/
    << expr::if_(expr::has_attr< attrs::named_scope::value_type  >("Scope"))
        [
            expr::stream << expr::format_named_scope("Scope", keywords::format = "[%n (%f:%l)]")
        ]
    .else_
        [
            expr::stream << ""
        ]
    /*Severity*/
    << expr::if_(expr::has_attr< severity_level>("Severity"))
        [
            expr::stream << "[" << expr::attr< severity_level >("Severity") << "]"
        ]
    .else_
        [
            expr::stream << ""
        ]
    /*ModuleName*/
    << expr::if_(expr::has_attr< std::string >("ModuleName"))
        [
            expr::stream << "[" << expr::attr< std::string >("ModuleName") << "]"
        ]
    .else_
        [
            expr::stream << ""
        ]

    /*Uptime*/
    << expr::if_(expr::has_attr(_uptime))
        [
            expr::stream << expr::format_date_time(_uptime, "[%O:%M:%S]")
        ]
    .else_
        [
            expr::stream << ""
        ]

    << " " << expr::message;
#pragma endregion 初始化fomatter

    if (ntag & DLogger::eOutTag_File)
    {
        string strFile = strFilePath;
        if(strFile.empty())
        {
            char   buffer[255] = "";
            getcwd(buffer, 255);
            strFile = string(buffer);
            if (strFile.empty())
            {
                strFile = "d:\\log\\temp.log";
            }
            else
            {
                strFile += "\\log\\temp.log";
            }
        }
        size_t npos = strFile.find_last_of('.');
        strFile.insert(npos, "_%Y-%m-%d");
        //


        //

        boost::shared_ptr<sinks::text_file_backend> backend1 = boost::make_shared<sinks::text_file_backend>(
            keywords::file_name = strFile,
            keywords::rotation_size = 10 * 1024 * 1024,
            keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0),
            keywords::min_free_space = 30 * 1024 * 1024,
            keywords::open_mode = std::ios_base::app);

        boost::shared_ptr< sinks::synchronous_sink< sinks::text_file_backend > > sink(
            new sinks::synchronous_sink< sinks::text_file_backend >(backend1));


        sink->set_formatter(formatter);
        sink->locked_backend()->auto_flush(true);
        logging::core::get()->add_sink(sink);
    }
    if (ntag & DLogger::eOutTag_Console)
    {
        auto console_sink = logging::add_console_log();
        console_sink->set_formatter(formatter);
        logging::core::get()->add_sink(console_sink);
    }
    logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());
    //g_log::get().add_attribute("ThreadID", attrs::current_thread_id());
    //g_log::get().add_attribute("ModuleName", boost::log::attributes::constant<std::string>("liuyu"));
    //g_log::get().add_attribute("Scope", attrs::named_scope());
    //g_log::get().add_attribute("Uptime", attrs::timer());
    
    logging::core::get()->set_filter(_severity >= normal);




    // //Create logging threads
    //boost::barrier bar(THREAD_COUNT);
    //boost::thread_group threads;
    //for (unsigned int i = 0; i < THREAD_COUNT; ++i)
    //    threads.create_thread(boost::bind(&thread_fun, boost::ref(bar)));

    //// Wait until all action ends
    //threads.join_all();

   
    return true;
}

void DLogger::ReleaseLog()
{
    logging::core::get()->remove_all_sinks();
}

void DLogger::Normal(const string &strlog)
{
    BOOST_LOG_FUNCTION();
    BOOST_LOG_SEV(g_log::get(), normal) << strlog;
}

void DLogger::Warning(const string &strlog)
{
    BOOST_LOG_FUNCTION();
    BOOST_LOG_SEV(g_log::get(), warning) << strlog;
}

void DLogger::Error(const string &strlog)
{
    BOOST_LOG_FUNCTION();
    BOOST_LOG_SEV(g_log::get(), normal) << strlog;
}

void DLogger::Critical(const string &strlog)
{
    BOOST_LOG_FUNCTION();
    BOOST_LOG_SEV(g_log::get(), critical) << strlog;
}

void DLogger::OutPutLogByLvl(const string &strlog, severity_level lvl)
{
    BOOST_LOG_FUNCTION();
    BOOST_LOG_SEV(g_log::get(), lvl) << strlog;
}

src::severity_logger_mt<severity_level> DLogger::GetLogger()
{
    return g_log::get();
}

