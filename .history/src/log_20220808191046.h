#ifndef __SYLAR_LOG_H
#define __SYLAR_LOG_H

#include<string>
#include<stdint.h>
#include<memory>
#include<list>
#include<sstream>
#include<fstream>
#include<vector>
#include<stdarg.h>
#include<map>
#include"thread.h"
#include"util.h"
#include"singleton.h"

//使用流式方法将日志级别level的日志写入logger
#define SYLAR_LOG_LEVEL(logger,level) \
    if(logger->getLevel()<=level) \
        sylar::LogEventWrap(sylar::LogEvent::ptr(new sylar::LogEvent(logger,level, \
                        __FILE__,__LINE__,0,sylar::GetThreadId(), \
                    sylar::GetFiberId(),time(0),sylar::Thread::GetName()))).getSS()

#define SYLAR_LOG_DEBUG(logger) SYLAR_LOG_LEVEL(logger,sylar::LogLevel::DEBUG)
#define SYLAR_LOG_INFO(logger) SYLAR_LOG_LEVEL(logger,sylar::LogLevel::INFO)    
#define SYLAR_LOG_WARN(logger) SYLAR_LOG_LEVEL(logger,sylar::LogLevel::WARN)
#define SYLAR_LOG_ERROR(logger) SYLAR_LOG_LEVEL(logger,sylar::LogLevel::ERROR)
#define SYLAR_LOG_FATAL(logger) SYLAR_LOG_LEVEL(logger,sylar::LogLevel::FATAL)


//使用格式化方法将日志级别level的日志写入logger
#define SYLAR_LOG_FMT_LEVEL(logger,level,fmt,...) \
    if(logger->getLevel()<=level) \
        sylar::LogEventWrap(sylar::LogEvent::ptr(new sylar::LogEvent(logger,level, \
                        __FILE__,__LINE__,0,sylar::GetThreadId(), \
                    sylar::GetFiberId(),time(0)))).getEvent()->format(fmt,__VA_ARGS__)

#define SYLAR_LOG_FMT_DEBUG(logger,fmt,...) SYLAR_LOG_FMT_LEVEL(logger,sylar::LogLevel::DEBUG,fmt,__VA_ARGS__)
#define SYLAR_LOG_FMT_INFO(logger,fmt,...) SYLAR_LOG_FMT_LEVEL(logger,sylar::LogLevel::INFO,fmt,__VA_ARGS__)    
#define SYLAR_LOG_FMT_WARN(logger,fmt,...) SYLAR_LOG_FMT_LEVEL(logger,sylar::LogLevel::WARN,fmt,__VA_ARGS__)
#define SYLAR_LOG_FMT_ERROR(logger,fmt,...) SYLAR_LOG_FMT_LEVEL(logger,sylar::LogLevel::ERROR,fmt,__VA_ARGS__)
#define SYLAR_LOG_FMT_FATAL(logger,fmt,...) SYLAR_LOG_FMT_LEVEL(logger,sylar::LogLevel::FATAL,fmt,__VA_ARGS__)

//获取主日志器
#define SYLAR_LOG_ROOT() sylar::LoggerMgr::GetInstance()->getRoot()

#define SYLAR_LOG_NAME(name) sylar::LoggerMgr::GetInstance()->getLogger(name)

namespace sylar{

class Logger;
class LoggerManager;

//日志级别
class LogLevel{
public:
    enum Level{
        UNKNOW=0,
        DEBUG=1,
        INFO=2,
        WARN=3,
        ERROR=4,
        FATAL=5
    };

    //日志级别转文本
    static const char* ToString(LogLevel::Level level);

    static LogLevel::Level FromString(const std::string& str);
};

//日志事件
class LogEvent{
public:
    using ptr=std::shared_ptr<LogEvent>; 
    LogEvent(std::shared_ptr<Logger> logger,LogLevel::Level level
            ,const char* file,int32_t line,uint32_t elapse,uint32_t thread_id
            ,uint32_t fiber_id,uint64_t time,const std::string& thread_name);

    const char* getFile() const{return m_file;}
    int32_t getLine() const{return m_line;}
    uint32_t getElapse() const{return m_elapse;}
    uint32_t getThreadId() const{return m_threadId;}
    uint32_t getFiberId() const{return m_fiberId;}
    std::string GetThreadName() const{return m_threadName;}
    uint64_t getTime() const{return m_time;}
    std::string getContent() const{return m_ss.str();}
    std::shared_ptr<Logger> getLogger() const {return m_logger;}
    LogLevel::Level getLevel() const{return m_level;}

    std::stringstream& getSS() {return m_ss;}
    void format(const char* fmt,...);
    void format(const char* fmt,va_list al);
private:
    const char* m_file=nullptr; //文件名
    int32_t m_line=0;           //行号
    uint32_t m_elapse=0;        //程序1启动开始到现在的毫秒数
    uint32_t m_threadId=0;      //线程id
    uint32_t m_fiberId=0;       //协程id
    uint64_t m_time;            //时间戳
    std::string m_threadName;
    std::stringstream m_ss;

    std::shared_ptr<Logger> m_logger;
    LogLevel::Level m_level;
};

class LogEventWrap{
public:
    LogEventWrap(LogEvent::ptr e);
    ~LogEventWrap();

    LogEvent::ptr getEvent() const {return m_event;}
    std::stringstream& getSS();
private:
    LogEvent::ptr m_event;
};

//日志格式器
class LogFormatter{
public:
    using ptr=std::shared_ptr<LogFormatter>;
    LogFormatter(const std::string& pattern);
    //%t    %thread_id %m%n
    std::string format(std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event);

public:
    class FormatItem {
    public:
        using ptr=std::shared_ptr<FormatItem>;
        //FormatItem(const std::string& fmt=""){}
        virtual ~FormatItem() {}
        virtual void format(std::ostream& os,std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event)=0;
    };

    void init();

    bool isError() const {return m_error;}

    const std::string getPattern() const { return m_pattern;}
private:
    std::vector<FormatItem::ptr> m_items;
    std::string m_pattern;
    bool m_error =false;
};

//日志输出地
class LogAppender{
friend class Logger;
public:
    using ptr=std::shared_ptr<LogAppender>; 
    using MutexType=Spinlock;
    virtual ~LogAppender(){}

    virtual void log(std::shared_ptr<Logger> logger,LogLevel::Level level,LogEvent::ptr event) = 0;

    virtual std::string toYamlString() = 0;
    void setFormatter(LogFormatter::ptr val);
    LogFormatter::ptr getFormatter();

    LogLevel::Level getLevel() const{return m_level;}
    void setLevel(LogLevel::Level level) {m_level=level;}
protected:
    LogLevel::Level m_level=LogLevel::DEBUG;
    bool m_hasFormatter = false;
    MutexType m_mutex;
    LogFormatter::ptr m_formatter;
};

//日志器
class Logger :public std::enable_shared_from_this<Logger>{
friend class LoggerManager;
public:
    using ptr=std::shared_ptr<Logger>; 
    using MutexType=Spinlock;
    Logger(const std::string& name="root");

    void log(LogLevel::Level level, LogEvent::ptr event);
    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    void clearAppenders();

    LogLevel::Level getLevel() const {return m_level;}
    void setLevel(LogLevel::Level val){m_level=val;}

    const std::string& getName() const{return m_name;}

    void setFormatter(LogFormatter::ptr val);
    void setFormatter(const std::string& val);
    
    LogFormatter::ptr getFormatter();

    std::string toYamlString();
private:
    std::string m_name;                            //日志名称
    LogLevel::Level m_level;                       //日志级别
    MutexType m_mutex;
    std::list<LogAppender::ptr> m_appenders;      //Appender集合
    LogFormatter::ptr m_formatter;                  //日志格式器
    Logger::ptr m_root;                           //主日志器
};

//输出到控制台
class StdoutLogAppender:public LogAppender{
public:
    using ptr=std::shared_ptr<StdoutLogAppender>;
    void log(Logger::ptr logger,LogLevel::Level level,LogEvent::ptr event) override;
    std::string toYamlString() override;
}; 

//输出到文件
class FileLogAppender:public LogAppender{
public:
    using ptr=std::shared_ptr<FileLogAppender>;
    FileLogAppender(const std::string& filename);
    void log(Logger::ptr logger,LogLevel::Level level,LogEvent::ptr event) override;
    std::string toYamlString() override;
    
    //重新打开文件
    bool reopen();
private:
    std::ofstream m_filestream;
    std::string m_filename;
    uint64_t m_lastTime = 0;
};

class LoggerManager{
public:
    using MutexType=Spinlock;
    LoggerManager();
    Logger::ptr getLogger(const std::string& name);

    void init();
    Logger::ptr getRoot() const{return m_root;}

    std::string toYamlString();
private:
    MutexType m_mutex;
    std::map<std::string,Logger::ptr> m_loggers;
    Logger::ptr m_root;
};

using LoggerMgr=sylar::Singleton<LoggerManager>;
}

#endif