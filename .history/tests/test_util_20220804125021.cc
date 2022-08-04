#include "src/sylar.h"
#include <assert.h>

syalr::Logger:::ptr g_logger =SYLAR_LOG_ROOT();

void test_assert(){
    assert(0);
}

int main(int argc,char** argv){
    test_assert(); 
    return 0;
}