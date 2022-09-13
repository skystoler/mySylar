#include "src/socket.h"
#include "src/sylar.h"
#include "src/iomanager.h"

static sylar::Logger::ptr g_logger=SYLAR_LOG_ROOT();

void test_socket(){
    
}

int main(int argc,char** argv){
    sylar::IOManager iom;
    iom.schedule(&test_socket);
    return 0;
}
