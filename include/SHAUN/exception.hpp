#ifndef EXCEPTION_HPP
#define EXCEPTION_HPP

#include <SHAUN/shaun.hpp>
#include <sstream>

namespace shaun
{
  
class exception
{
public:
    virtual ~exception() {}
    virtual std::string to_string() const = 0;
    
    
    friend std::ostream& operator<<(std::ostream& out, const exception& err);
};

class parse_error : public exception
{
public:
    parse_error(size_t line, size_t column, const std::string& error)
    {
        line_ = line+1;
        column_ = column+1;
        error_ = error;
    }
    
    ~parse_error()
    {
      
    }
    
    std::string to_string() const
    {
        std::stringstream ss;
        ss << "Parse error at line: " << line_
             << " column: " << column_
             << " (" << error_ << ")";
        return ss.str();
    }
    
private:
    size_t line_;
    size_t column_;
    std::string error_;
};

class type_error : public exception
{
public:
    type_error(Type exp, Type got, const std::string& name)
    {
        exp_ = exp;
        got_ = got;
        name_ = name;
    }
    
    ~type_error() {}
    
    std::string to_string() const
    {
        return "Expected " + type_to_string(exp_)
             + " but " + name_ + " has type " + type_to_string(got_);
    }
    
private:
    Type exp_;
    Type got_;
    std::string name_;
};

class list_index_error : public exception
{
public:
    list_index_error() {}
    ~list_index_error() {}
    
    std::string to_string() const
    {
      return "index out of range";
    }
};

} // namespace

#endif // EXCEPTION_HPP
