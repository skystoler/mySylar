#include "src/http/http_parser.h"
#include "src.log.h"

static sylar::Logger::ptr g_logger=SYLAR_LOG_NAME("system");

const char test_request_data[]="GET / HTTP/1.1\r\n";
void test(){

}

int main(int argc,char** argv){
    test();
    return 0;
}