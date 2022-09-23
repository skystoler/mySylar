#ifndef __SYLAR_HTTP_SERVLET_H__
#define __SYLAR_HTTP_SERVLET_H__

#include <memory>
#include <functional>
#include <string>
#include <vector>
#include <unordered_map>
#include "http.h"
#include "http_session.h"
#include "src/thread.h"

namespace sylar{
namespace http{
 
class Servlet{
public:
    using ptr=std::shared_ptr<Servlet>;
    Servlet(const std::string& name)
        :m_name(name){}
    virtual ~Servlet(){}
    virtual int32_t handle(sylar::http::HttpRequest::ptr request
                    ,sylar::http::HttpResponse::ptr response
                    ,sylar::http::HttpSession::ptr session)=0;
    const std::string& getName() const {return m_name;}
protected:
    std::string m_name;
};

class FunctionServlet:public Servlet{
public:
    using ptr=std::shared_ptr<FunctionServlet>;
    using callback=std::function<int32_t (sylar::http::HttpRequest::ptr request
                    ,sylar::http::HttpResponse::ptr response
                    ,sylar::http::HttpSession::ptr session)>;

    FunctionServlet(callback cb);
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

    ServletDispatch();
    virtual int32_t handle(sylar::http::HttpRequest::ptr request
                    ,sylar::http::HttpResponse::ptr response
                    ,sylar::http::HttpSession::ptr session) override;

    void addServlet(const std::string& uri,Servlet::ptr slt);
    void addServlet(const std::string& uri,FunctionServlet::callback cb);
    void addGlobServlet(const std::string& uri,Servlet::ptr slt);
    void addGlobServlet(const std::string& uri,FunctionServlet::callback cb);

    void delServlet(const std::string& uri);
    void delGlobServlet(const std::string& uri);

    Servlet::ptr getDefault() const {return m_default;}
    void setDefault(const std::string& v){m_default=v;}

    Servlet::ptr getServlet(const std::string& uri);
    Servlet::ptr getGlobServlet(const std::string& uri);

    Servlet::ptr getMatchedServlet(const std::string& uri);
private:
    RWMutexType m_mutex;
    //uri(/sylar/xxx)->servlet
    std::unordered_map<std::string,Servlet::ptr> m_datas;
    //uri(/sylar/*)->servlet
    std::vector<std::pair<std::string,Servlet::ptr>> m_globs;
    //所有路径都没有匹配到，使用默认路径
    Servlet::ptr m_default;
};


class NotFoundServlet :public Servlet{
public:
    using ptr=std::shared_ptr<NotFoundServlet>;
    NotFoundServlet();
    virtual int32_t handle(sylar::http::HttpRequest::ptr request
                    ,sylar::http::HttpResponse::ptr response
                    ,sylar::http::HttpSession::ptr session) override;
};

}
}

#endif