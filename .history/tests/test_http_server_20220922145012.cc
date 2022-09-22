#include "src/http/http_server.h"
#include "src/log.h"

static sylar::Logger::ptr g_logger=SYLAR_LOG_ROOT();

void run(){

}

int main(int argc,char** argv){
    sylar::IOManager iom(2);
    iom.schedule(run);
    return 0;
}