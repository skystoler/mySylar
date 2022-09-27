#ifndef __SYLAR_URI_H__
#define __SYLAR_URI_H__


#include <memory>
#include <string>


namespace sylar{

/*
     foo://user@sylar.com:8042/over/there?name=ferret#nose
       \_/   \______________/\_________/ \_________/ \__/
        |           |            |            |        |
     scheme     authority       path        query   fragment
*/

class URI{
public:
    using ptr=std::shared_ptr<URI>;
private:
    std::string m_scheme;
    std::string m_
};

}

#endif