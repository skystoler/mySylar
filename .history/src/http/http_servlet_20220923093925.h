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
    virtual ~Servlet(){}
private:

};
}
}

#endif