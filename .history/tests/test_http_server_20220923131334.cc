#include "src/http/http_server.h"
#include "src/log.h"

static sylar::Logger::ptr g_logger=SYLAR_LOG_ROOT();

void run(){
    sylar::http::HttpServer::ptr server(new sylar::http::HttpServer);
    sylar::Address::ptr addr=sylar::Address::LookupAnyIPAddress("0.0.0.0:8020");
    while(!server->bind(addr)){
        sleep(2);
    }
    auto sd=server->getServletDispatch();
    sd->addServlet("/sylar/xx",[](sylar::http::HttpRequest::ptr req
                                ,sylar::http:HttpResponse::ptr rsp
                                ,sylar::http:HttpSession::ptr session){
        rsp->setBody(req->toString());
    });
    sd->addServlet("/sylar/*",[](sylar::http::HttpRequest::ptr req
                                ,sylar::http:HttpResponse::ptr rsp
                                ,sylar::http:HttpSession::ptr session){
        rsp->setBody("Glob:\r\n" + req->toString());
    });
    server->start();
}

int main(int argc,char** argv){
    sylar::IOManager iom(2);
    iom.schedule(run);
    return 0;
}