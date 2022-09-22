#include "src/http/http_server.h"


void run(){

}

int main(int argc,char** argv){
    sylar::IOManager iom(2);
    iom.schedule(run);
    return 0;
}