/*
 * uexcept.h
 *
 *  Created on: 16 трав. 2017
 *      Author: root
 */


#pragma once

#include <stdexcept>

#define CODE_LOCATE  (string("file ") + __FILE__ + ", fuction " + __FUNCTION__ + ", line " + to_string(__LINE__))
#define RT_ERROR(msg)  runtime_error(CODE_LOCATE + ": " + msg);



