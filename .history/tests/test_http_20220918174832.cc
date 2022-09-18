#include "src/http/http.h"
#include "src/log.h"


void test(){
    sylar::http::HttpRequest::ptr req(new sylar::http::HttpRequest);
    req->setHeader("host","www.sylar.top");
    req->setBody("hello skystoler!");
    req->dump(std::cout)<<std::endl;
}

int main(int argc,char** argv){
    test();
    return 0;
}
