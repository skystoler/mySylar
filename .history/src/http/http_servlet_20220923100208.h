#ifndef __SYLAR_HTTP_SERVLET_H__
#define __SYLAR_HTTP_SERVLET_H__

#include <memory>
#include <functional>
#include <string>
#include "http.h"
#include "http_session.h"

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

}
}

#endif