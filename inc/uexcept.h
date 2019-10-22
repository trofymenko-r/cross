/*
 * uexcept.h
 *
 *  Created on: 16 трав. 2017
 *      Author: root
 */


#pragma once

#include <stdexcept>
#include <string>

#define CODE_LOCATE  (std::string("file ") + __FILE__ + ", fuction " + __FUNCTION__ + ", line " + std::to_string(__LINE__))
#define RT_ERROR(msg)  std::runtime_error(CODE_LOCATE + ": " + msg);



