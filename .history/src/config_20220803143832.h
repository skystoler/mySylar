#ifndef __SYLAR__CONFIG_H__
#define __SYLAR__CONFIG_H__


#include <memory>
#include <string>
#include <sstream>
#include <boost/lexical_cast.hpp>
#include <yaml-cpp/yaml.h>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <functional>

#include "log.h"
#include "util.h"

namespace sylar{

class ConfigVarBase{
public:
    using ptr=std::shared_ptr<ConfigVarBase>;
    
    
    ConfigVarBase(const std::string& name,const std::string& description ="")
        :m_name(name)
        ,m_description(description){
            std::transform(m_name.begin(),m_name.end(),m_name.begin(),::tolower);
    }

    virtual ~ConfigVarBase(){}

    const std::string& getName() const {return m_name;}
    const std::string& getDescription() const {return m_description;}

    virtual std::string toString()=0;
    virtual bool fromString(const std::string& val)=0;
    virtual std::string getTypeName() const =0;
protected:
    std::string m_name;
    std::string m_description;
};   



//F:from_type,T:to_type,该类类似一个仿函数，功能是类型转换
template<class F,class T>
class LexicalCast{
public:
    T operator()(const F& v){
        return boost::lexical_cast<T>(v);
    }
};

//模板的偏特化:vector和string互转
//string->yaml,for yaml_node in yaml,yaml_node->sstream->string->T,push into vector
template<class T>
class LexicalCast<std::string,std::vector<T> >{
public:
    std::vector<T> operator()(const std::string& v){
        YAML::Node node=YAML::Load(v);
        typename std::vector<T> vec;
        std::stringstream ss;
        for(size_t i=0;i<node.size();++i){
            ss.str("");
            ss << node[i];
            vec.push_back(LexicalCast<std::string,T>()(ss.str()));
        }
        return vec;
    }
};



//for T in vector,T->yaml_node->sstream->string
template <class T>
class LexicalCast<std::vector<T>,std::string >{
public:
    std::string operator()(const std::vector<T>& v){
        YAML::Node node;
        for(auto& i:v){
            node.push_back(YAML::Load(LexicalCast<T,std::string>()(i)));
        }
        std::stringstream ss;
        ss << node;
        return ss.str();
    }
};


//模板的偏特化:list和string互转
//string->yaml,for yaml_node in yaml,yaml_node->sstream->string->T,push into list
template <class T>
class LexicalCast<std::string,std::list<T> >{
public:
    std::list<T> operator()(const std::string& v){
        YAML::Node node=YAML::Load(v);
        typename std::list<T> li;
        std::stringstream ss;
        for(size_t i=0;i<node.size();++i){
            ss.str("");
            ss<<node[i];
            li.push_back(LexicalCast<std::string,T>()(ss.str()));
        }
        return li;
    }
};



//for T in list,T->yaml_node->sstream->string
template <class T>
class LexicalCast<std::list<T>,std::string >{
public:
    std::string operator()(const std::list<T>& v){
        YAML::Node node;
        for(auto& i:v){
            node.push_back(YAML::Load(LexicalCast<T,std::string>()(i)));
        }
        std::stringstream ss;
        ss<<node;
        return ss.str();
    }
};


//模板的偏特化:set和string互转
//string->yaml,for yaml_node in yaml,yaml_node->sstream->string->T,push into set
template <class T>
class LexicalCast<std::string,std::set<T> >{
public:
    std::set<T> operator()(const std::string& v){
        YAML::Node node=YAML::Load(v);
        typename std::set<T> se;
        std::stringstream ss;
        for(size_t i=0;i<node.size();++i){
            ss.str("");
            ss<<node[i];
            se.insert(LexicalCast<std::string,T>()(ss.str()));
        }
        return se;
    }
};



//for T in set,T->yaml_node->sstream->string
template <class T>
class LexicalCast<std::set<T>,std::string >{
public:
    std::string operator()(const std::set<T>& v){
        YAML::Node node;
        for(auto& i:v){
            node.push_back(YAML::Load(LexicalCast<T,std::string>()(i)));
        }
        std::stringstream ss;
        ss<<node;
        return ss.str();
    }
};


//模板的偏特化:unordered_set和string互转
//string->yaml,for yaml_node in yaml,yaml_node->sstream->string->T,push into unordered_set
template <class T>
class LexicalCast<std::string,std::unordered_set<T> >{
public:
    std::unordered_set<T> operator()(const std::string& v){
        YAML::Node node=YAML::Load(v);
        typename std::unordered_set<T> se;
        std::stringstream ss;
        for(size_t i=0;i<node.size();++i){
            ss.str("");
            ss<<node[i];
            se.insert(LexicalCast<std::string,T>()(ss.str()));
        }
        return se;
    }
};



//for T in unordered_set,T->yaml_node->sstream->string
template <class T>
class LexicalCast<std::unordered_set<T>,std::string >{
public:
    std::string operator()(const std::unordered_set<T>& v){
        YAML::Node node;
        for(auto& i:v){
            node.push_back(YAML::Load(LexicalCast<T,std::string>()(i)));
        }
        std::stringstream ss;
        ss<<node;
        return ss.str();
    }
};


//模板的偏特化:map和string互转
//string->yaml,for yaml_node in yaml,yaml_node->sstream->string->T,push into map
template <class T>
class LexicalCast<std::string,std::map<std::string,T> >{
public:
    std::map<std::string,T> operator()(const std::string& v){
        YAML::Node node=YAML::Load(v);
        typename std::map<std::string,T> m;
        std::stringstream ss;
        for(auto it=node.begin();it!=node.end();++it){
            ss.str("");
            ss<<it->second;
            m.insert(std::make_pair(it->first.Scalar(),
                            LexicalCast<std::string,T>()(ss.str())));
        }
        return m;
    }
};



//for T in map,T->yaml_node->sstream->string
template <class T>
class LexicalCast<std::map<std::string,T>,std::string >{
public:
    std::string operator()(const std::map<std::string,T>& v){
        YAML::Node node;
        for(auto& i:v){
            node[i.first]=YAML::Load(LexicalCast<T,std::string>()(i.second));
        }
        std::stringstream ss;
        ss<<node;
        return ss.str();
    }
};


//模板的偏特化:unordered_map和string互转
//string->yaml,for yaml_node in yaml,yaml_node->sstream->string->T,push into unordered_map
template <class T>
class LexicalCast<std::string,std::unordered_map<std::string,T> >{
public:
    std::unordered_map<std::string,T> operator()(const std::string& v){
        YAML::Node node=YAML::Load(v);
        typename std::unordered_map<std::string,T> m;
        std::stringstream ss;
        for(auto it=node.begin();it!=node.end();++it){
            ss.str("");
            ss<<it->second;
            m.insert(std::make_pair(it->first.Scalar(),
                            LexicalCast<std::string,T>()(ss.str())));
        }
        return m;
    }
};



//for T in unordered_map,T->yaml_node->sstream->string
template <class T>
class LexicalCast<std::unordered_map<std::string,T>,std::string >{
public:
    std::string operator()(const std::unordered_map<std::string,T>& v){
        YAML::Node node;
        for(auto& i:v){
            node[i.first]=YAML::Load(LexicalCast<T,std::string>()(i.second));
        }
        std::stringstream ss;
        ss<<node;
        return ss.str();
    }
};






//该模板具备一般类型和string的相互转化，其他复杂类型及自定义类型依赖偏特化实现
//FromString T operator()(const std::string&)
//ToStr std::string operator()(const T&)
template<class T,class FromStr = LexicalCast<std::string, T>
                ,class ToStr = LexicalCast<T, std::string> >
class ConfigVar : public ConfigVarBase{
public:
    using RWMutexType=RWMutex;
    using ptr=std::shared_ptr<ConfigVar>;
    //回调函数作为闭包传递
    using on_change_cb=std::function<void (const T& old_value,const T& new_value)>;

    ConfigVar(const std::string& name
            ,const T& default_value
            ,const std::string& description = "")
        :ConfigVarBase(name,description)
        ,m_val(default_value){

    }

    std::string toString() override{
        try{
           //return boost::lexical_cast<std::string>(m_val);
           RWMutexType::ReadLock lock(m_mutex);
           return ToStr()(m_val);
        }catch(std::exception& e){
            SYLAR_LOG_ERROR(SYLAR_LOG_ROOT())<<"ConfigVar::toString exception"
                <<e.what()<<"convert: "<<typeid(m_val).name()<<"to string";
        }

        return "";
    }

    bool fromString(const std::string& val) override{
        try{
            //m_val=boost::lexical_cast<T>(val);
            setValue(FromStr()(val));
        }catch(std::exception& e){
            SYLAR_LOG_ERROR(SYLAR_LOG_ROOT())<<"ConfigVar::toString exception"
                <<e.what()<<"convert: string to "<<typeid(m_val).name();
        }

        return false;
    }

    //设置当前参数值，如果变化则通知回调函数
    const T getValue() const{
        RWMutexType::ReadLock lock(m_mutex);
        return m_val;
    }

    void setValue(const T& v){
        RWMutexType::ReadLock lock(m_mutex);
        if(v== m_val){
            return;
        }
        for(auto &i :m_cbs){
            //i.second是map每个pair对应的值,是一个函数指针,m_val为old值,v为新值
            i.second(m_val,v);
        }       
        RWMutexType::WriteLock lock(m_mutex);
        m_val=v;
    }
    std::string getTypeName() const override{return typeid(T).name();}

    //传参cb为函数指针，添加回调函数，返回唯一id用于删除回调
    uint64_t addListener(uint64_t key,on_change_cb cb){
        static uint64_t s_fun_id=0;
        RWMutexType::WriteLock lock(m_mutex);
        ++s_fun_id;
        m_cbs[s_fun_id]=cb;
        return s_fun_id;
    }

    void delListener(uint64_t key){
        RWMutexType::WriteLock lock(m_mutex);
        m_cbs.erase(key);
    }

    //获取回调函数
    on_change_cb getListener(uint64_t key){
        RWMutexType::ReadLock lock(m_mutex);
        auto it=m_cbs.find(key);
        return it==m_cbs.end()?nullptr:it->second;
    }

    void clearListener(){
        m_cbs.clear();
    }

private:
    T m_val;

    //变更回调函数组,uint64_t key要求唯一,一般可以用hash
    std::map<uint64_t,on_change_cb> m_cbs; 
};

class Config{
public:
    using ConfigVarMap=std::unordered_map<std::string,ConfigVarBase::ptr>;

    template <class T>
    static typename ConfigVar<T>::ptr Lookup(const std::string& name,
            const T& default_value,const std::string& description = ""){
        auto it =GetDatas().find(name);
        if(it!=GetDatas().end()){
            auto tmp = std::dynamic_pointer_cast<ConfigVar<T> >(it->second);
            if(tmp){
                SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) <<"Lookup name:" << name << "exists";
                return tmp;
            }else {
                SYLAR_LOG_ERROR(SYLAR_LOG_ROOT()) <<"Lookup name:" << name 
                        << "exists but type not " << typeid(T).name()<< 
                        "reaql_type=" <<it->second->getTypeName()<<
                        " "<<it->second->toString();
                return nullptr;
            }
        }

        if(name.find_first_not_of("abcdefghijklmnopqrstuvwxyz._12345678")\
            !=std::string::npos){
                SYLAR_LOG_ERROR(SYLAR_LOG_ROOT())<<"Lookup name:"<<name<<"invalid";
                throw std::invalid_argument(name);
        }

        typename ConfigVar<T>::ptr v(new ConfigVar<T>(name,default_value,description));
        GetDatas()[name]=v;
        return v;
    }

    template <class T>
    static typename ConfigVar<T>::ptr Lookup(const std::string& name){
        auto it=GetDatas().find(name);
        if(it==GetDatas().end()){
            return nullptr;
        }
        //如果找到，将指针从config基类转为config子类的智能指针,偏特化
        return std::dynamic_pointer_cast<ConfigVar<T> >(it->second);
    }

    static void LoadFromYaml(const YAML::Node& root);

    static void LoadFromConfDir(const std::string& path, bool force = false);

    static ConfigVarBase::ptr LookupBase(const std::string& name);

    static void Visit(std::function<void(ConfigVarBase::ptr)> cb);
private:
    static ConfigVarMap& GetDatas() {
        static ConfigVarMap s_datas;
        return s_datas;
    }
};

}
#endif