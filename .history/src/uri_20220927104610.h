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

class Uri{
public:
    using ptr=std::shared_ptr<URI>;

    static Uri::ptr Create(const std::string& uri);
    Uri();
    
    const std::string& getScheme() const { return m_scheme;}
    const std::string& getUserinfo() const { return m_userinfo;}
    const std::string& getHost() const { return m_host;}
    const std::string& getPath() const;
    const std::string& getQuery() const { return m_query;}
    const std::string& getFragment() const { return m_fragment;}
    int32_t getPort() const;

    void setScheme(const std::string& v) { m_scheme = v;}
    void setUserinfo(const std::string& v) { m_userinfo = v;}
    void setHost(const std::string& v) { m_host = v;
    void setPath(const std::string& v) { m_path = v;}
    void setQuery(const std::string& v) { m_query = v;}
    void setFragment(const std::string& v) { m_fragment = v;}
    void setPort(int32_t v) { m_port = v;}

private:
    //schema
    std::string m_scheme;
    //用户信息
    std::string m_userinfo;
    //host
    std::string m_host;
    //端口
    int32_t m_port;
    //路径
    std::string m_path;
    //查询参数
    std::string m_query;
    //fragment
    std::string m_fragment;
};

}

#endif