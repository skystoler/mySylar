#include "http_servlet.h"

namespace sylar{
namespace http{

FunctionServlet::FunctionServlet(callback cb)
    :Servlet("FunctionServlet")
    ,m_cb(cb){

}

int32_t FunctionServlet::handle(sylar::http::HttpRequest::ptr request
                ,sylar::http::HttpResponse::ptr response
                ,sylar::http::HttpSession::ptr session){
    return m_cb(request,re) 
}

ServletDispatch::ServletDispatch(){

}

int32_t ServletDispatch::handle(sylar::http::HttpRequest::ptr request
                ,sylar::http::HttpResponse::ptr response
                ,sylar::http::HttpSession::ptr session){

}

void ServletDispatch::ServletDispatchaddServlet(const std::string& uri,Servlet::ptr slt){

}

void ServletDispatch::addServlet(const std::string& uri,FunctionServlet::callback cb){

}

void ServletDispatch::addGlobServlet(const std::string& uri,Servlet::ptr slt){

}

void ServletDispatch::addGlobServlet(const std::string& uri,FunctionServlet::callback cb){

}

void ServletDispatch::delServlet(const std::string& uri){

}

void ServletDispatch::delGlobServlet(const std::string& uri){

}

Servlet::ptr ServletDispatch::getServlet(const std::string& uri){

}

servlet::ptr ServletDispatch::getGlobServlet(const std::string& uri){

}

Servlet::ptr ServletDispatch::getMatchedServlet(const std::string& uri){

}

}
}