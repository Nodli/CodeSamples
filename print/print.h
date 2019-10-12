#pragma once

#include <iostream>

#define PRINT(...) Print(std::cout, __VA_ARGS__)
#define LOG(...) Print(std::cerr, "LINE:", __LINE__, "FILE:", __FILE__, "FUNCTION:", __func__, "LOG:",  __VA_ARGS__)
#define RAWLOG(...) Print(std::cerr, __VA_ARGS__)

#ifndef _WIN32
inline void Print(std::ostream& stream){};
#endif

template<typename T>
inline void privatePrint(std::ostream& stream, const T& thing){
    stream << thing << ' ';
}

template<typename T>
inline void privatePrint(std::ostream& stream, const T* const thing_ptr){
    if(thing_ptr){
        stream << thing_ptr << ' ';
    }
}

template<typename T, typename ... otherT>
inline void Print(std::ostream& stream, const T& thing, const otherT&... otherThing){
    privatePrint(stream, thing);
    Print(stream, otherThing...);

    if constexpr(sizeof...(otherThing) < 1){
        stream << '\n';
    }
}

template<typename T>
inline void Print(std::ostream& stream, const T& thing){
    privatePrint(stream, thing);
    stream << '\n';
}

template<typename T>
inline void Print(std::ostream& stream, const T* const thing){
    privatePrint(stream, thing);
    stream << '\n';
}
