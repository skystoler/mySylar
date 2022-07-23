#ifndef __SYLAR_LOG_H
#define __SYLAR_LOG_H

#include<string>
#include<stdint.h>
#include<memory>
#include<list>
#include<sstream>
#include<fstream>

namespace sylar{

//日志事件
class LogEvent{
public:
    using ptr=std::shared_ptr<LogEvent>; 
    LogEvent();
private:
    const char* m_file=nullptr; //文件名
    int32_t m_line=0;           //行号
    uint32_t m_elapse=0;        //程序1启动开始到现在的毫秒数
    uint32_t m_threadId=0;      //线程id
    uint32_t m_fiverId=0;       //协程id
    uint64_t m_time;            //时间戳
    std::string m_content;      
};

//日志级别
class LogLevel{
public:
    enum Level{
        DEBUG=1,
        INFO=2,
        WARN=3,
        ERROR=4,
        FATAL=5
    };
};

//日志格式器
class LogFormatter{
public:
    using ptr=std::shared_ptr<LogFormatter>;

    std::string format(LogEvent::ptr event);

private:
};

//日志输出地
class LogAppender{
public:
    using ptr=std::shared_ptr<LogAppender>; 
    virtual ~LogAppender(){}

    virtual void log(LogLevel::Level level,LogEvent::ptr event) = 0;

    void setFormatter(LogFormatter::ptr val){m_formatter=val;}
    LogFormatter::ptr getFormatter() const{return m_formatter;}
private:
    LogLevel::Level m_level;
    LogFormatter::ptr m_formatter;
};

//日志器
class Logger{
public:
    using ptr=std::shared_ptr<Logger>; 

    Logger(const std::string& name="root");

    void log(LogLevel::Level level, LogEvent::ptr event);
    void debug(LogEvent::ptr event);
    void info(LogEvent::ptr event);
    void warn(LogEvent::ptr event);
    void error(LogEvent::ptr event);
    void fatal(LogEvent::ptr event);

    void addAppender(LogAppender::ptr appender);
    void delAppender(LogAppender::ptr appender);
    LogLevel::Level getLevel() const {return m_level;}
    void setLevel(LogLevel::Level val){m_level=val;}
private:
    std::string m_name;                            //日志名称
    LogLevel::Level m_level;                       //日志级别
    std::list<LogAppender::ptr> m_appenders;      //Appender集合
};

//输出到控制台
class StdOutLogAppender:public LogAppender{
public:
    using ptr=std::shared_ptr<StdOutLogAppender>;
    virtual void log(LogLevel::Level level,LogEvent::ptr event) override;
}; 

//输出到文件
class FileLogAppender:public LogAppender{
public:
    using ptr=std::shared_ptr<FileLogAppender>;
    FileLogAppender(const std::string& filename);
    virtual void log(LogLevel::Level level,LogEvent::ptr event) override;

    //重新打开文件
    bool reopen();
private:
    std::string m_name;
    std::ofstream m_filestream;
    std::stirng m_filename;
};

}

#endif