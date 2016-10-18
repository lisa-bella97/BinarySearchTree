#ifndef BINARYSEARCHTREE_LOGICAL_ERROR_HPP
#define BINARYSEARCHTREE_LOGICAL_ERROR_HPP

#include <iostream>
#include <exception>

template<typename T>
class logical_error : std::logic_error
{
public:
    explicit logical_error(const std::string& message, const T& value) : std::logic_error(message), value_(value) {}
    explicit logical_error(const char* message, const T& value) : std::logic_error(message), value_(value) {}
    const char* what() const noexcept override
    {
        return std::logic_error::what();
    }
    const T& getValue() const noexcept
    {
        return value_;
    }
private:
    T value_;
};

#endif // BINARYSEARCHTREE_LOGICAL_ERROR_HPP