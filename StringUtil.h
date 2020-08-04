#pragma once
#include<iostream>

namespace StringUtil
{
    template<typename ... Args>
    std::string Format(const std::string& format, Args ... args) //‘› ±≤ª”√C++20
    {
        size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
        if (size <= 0) { throw std::runtime_error("Error during formatting."); }
        std::unique_ptr<char[]> buf(new char[size]);
        snprintf(buf.get(), size, format.c_str(), args ...);
        return std::string(buf.get(), buf.get() + size - 1);
    }
}

