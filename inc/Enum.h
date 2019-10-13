/*
 * Enum.h
 *
 *  Created on: 16 трав. 2017
 *      Author: root
 */

#pragma once

#include <tuple>

namespace cross {

class CEnum
{
public:
   CEnum();
   virtual ~CEnum();

public:
   static bool RegisterEnum(...){return true;}
};

#define ARGS(...) __VA_ARGS__

#define AWESOME_MAKE_ENUM(name, ...) enum class name { __VA_ARGS__, __COUNT};

#define PAIR(type, str) {type, str}

//#define MAKE_ENUM(name, ...) enum class name{ __VA_ARGS__, __COUNT};

#define MAKE_MAP(name, ...) std::map<int, string> name = {__VA_ARGS__};

#define MACRO(...) \
    std::cout << "num args: " \
    << std::tuple_size<decltype(std::make_tuple(__VA_ARGS__))>::value \
    << std::endl;


#define ENUM_CLASS_NAME(name)  C##name##Enum

#define MAKE_ENUM(name, ...)  \
class ENUM_CLASS_NAME(name) : public CEnum  \
{\
public:\
   ENUM_CLASS_NAME(name)():CEnum(){}\
   static const bool bRegResult;\
};\
\
const bool ENUM_CLASS_NAME(name)::bRegResult = CEnum::RegisterEnum(__VA_ARGS__);

} /* namespace cross */
