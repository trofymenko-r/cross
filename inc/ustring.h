/*
 * ustring.h
 *
 *  Created on: 13 жовт. 2016
 *      Author: root
 */


#pragma once

#include <string>
#include <vector>

#define BACKSPACE " "

#define __TO_STRING(something) std::string(#something)
#define VARIABLE_TO_STRING(Variable) (void(Variable),#Variable)
#define FUNCTION_TO_STRING(Function) (void(&Function),#Function)
#define METHOD_TO_STRING(ClassName,Method) (void(&ClassName::Method),#Method)
#define TYPE_TO_STRING(Type) (void(sizeof(Type)),#Type)


using namespace std;

vector<string> SplitByWaitSpace(const string& str);
vector<string> Split(const string& str, char sep, bool keepEmptyParts=false);
void ReplaceStr(string& Str, const string& sOld, const string& sNew);
void RemoveChar(string& str, const char ch);
void RemoveNewLineChar(string& str);
bool IsLiteral(const string& str);
bool IsDigit(const string& str);
bool IsIntValue(const string& str);
bool IsHexValue(const string& str);
bool IsIpv4(const string& str);
bool IsMacAddr(const string& str);
string Ipv4ToStr(uint32_t u32Ip);
bool StrToInt(const string& str, int& val);
