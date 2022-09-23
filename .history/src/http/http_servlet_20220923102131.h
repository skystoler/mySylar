#ifndef __SYLAR_HTTP_SERVLET_H__
#define __SYLAR_HTTP_SERVLET_H__

#include <memory>
#include <functional>
#include <string>
#include <vector>
#include <unordered_map>
#include "http.h"
#include "http_session.h"
#include "sylar/thread.h"

namespace sylar{
namespace http{
 
class Servlet{
public:
    using ptr=std::shared_ptr<Servlet>;
    Servlet(const std::string& name)
        :m_name(name){}
    virtual ~Servlet(){}
    virtual int32_t handle(sylar::http::HttpRequest::ptr request
                    ,sylar::http::HttpResponse::ptr HttpResponse
                    ,sylar::http::HttpSession::ptr session)=0;
    std::string& getName() const {return m_name;}
protected:
    std::string m_name;
};

class FunctionServlet:publci Servlet{
public:
    using ptr=std::shared_ptr<FunctionServlet>;
    FunctionServlet(callback cb);
    using callback=std::function<int32_t (sylar::http::HttpRequest::ptr request
                    ,sylar::http::HttpResponse::ptr HttpResponse
                    ,sylar::http::HttpSession::ptr session)>;
     virtual int32_t handle(sylar::http::HttpRequest::ptr request
                    ,sylar::http::HttpResponse::ptr HttpResponse
                    ,sylar::http::HttpSession::ptr session) override;
private:
    callback m_cb;
};

class ServletDispatch:public Servlet{
public:
    using ptr=std::shared_ptr<ServletDispatch>;
    using RWMutexType=RWMutex;

    void addServlet(const std::string& uri,Servlet::ptr slt);
    void addServlet(const std::string& uri,FunctionServlet::callback cb);
    void addGlobServlet(const std::string& uri,Servlet::ptr slt);
    void addGlobServlet(const std::string& uri,FunctionServlet::callback cb);

    void delServlet(const std::string& uri);
    void delGlobServlet(const std::string& uri);

    Servlet::ptr getDefault() const {return m_default;}
    void setDefault(const std::string& uri){m_default=v;}

    Servlet::ptr getServlet(const std::string& uri);
    servlet::ptr getGlobServlet(const std::string& uri);

    Servlet::ptr getMatchedServlet(const std::string& uri);
private:
    //uri(/sylar/xxx)->servlet
    std::unordered_map<std::string,Servlet::ptr> m_datas;
    //uri(/sylar/*)->servlet
    std::vector<std::pair<std::string,Servlet::ptr>> m_globs;
    //所有路径都没有匹配到，使用默认路径
    Servlet::ptr m_default;
};

}
}

#endif