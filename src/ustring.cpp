/*
 * Ustring.cpp
 *
 *  Created on: 13 жовт. 2016
 *      Author: root
 */

#include <iostream>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <arpa/inet.h>

#include "ustring.h"

/******************************************************************************/
/*  SplitByWaitSpace                                                          */
/******************************************************************************/
vector<string> SplitByWaitSpace(const string& str)
{
   std::istringstream iss(str);
   vector<string> tokens;
   copy(istream_iterator<string>(iss),
        istream_iterator<string>(),
        back_inserter<vector<string>>(tokens));

   return tokens;
}

/******************************************************************************/
/*  Split                                                                     */
/******************************************************************************/
vector<string> Split(const string& str, char sep, bool keepEmptyParts)
{
   vector<string> lists;
   string::size_type start = 0;
   string::size_type end;
   while((end=str.find(sep, start))!=string::npos){
      if(start!=end || keepEmptyParts)
         lists.push_back(str.substr(start, end - start));
      start = end + 1;
   }
   if(start!=str.size() || keepEmptyParts)
       lists.push_back(str.substr(start));
   return lists;
}

/******************************************************************************/
/*  ReplaceStr                                                                */
/******************************************************************************/
void ReplaceStr(string& Str, const string& sOld, const string& sNew)
{
   for(string::size_type index=0; index=Str.find(sOld, index), index!=string::npos;){
      Str.replace(index, sOld.length(), sNew);
      index += sNew.length();
   }
}

/******************************************************************************/
/*  RemoveChar                                                                */
/******************************************************************************/
void RemoveChar(string& str, const char ch)
{
   str.erase(std::remove(str.begin(), str.end(), ch), str.end());
}

/******************************************************************************/
/*  RemoveNewLineChar                                                         */
/******************************************************************************/
void RemoveNewLineChar(string& str)
{
   RemoveChar(str, '\n');
}

/******************************************************************************/
/*  IsLiteral                                                                 */
/******************************************************************************/
bool IsLiteral(const string& str)
{
   const locale loc = locale("POSIX");//("en_US.UTF8");
   for(string::const_iterator it=str.begin(); it!=str.end(); ++it){
   //for(/*auto&*/string::const_iterator it: str){
      const char ch = std::toupper(*it, loc);
      if(!(ch >= 'A' && ch <= 'Z'))
         return false;
   }
   return true;
}

/******************************************************************************/
/*  IsDigit                                                                   */
/******************************************************************************/
bool IsDigit(const string& str)
{
   size_t count_dot = count(str.begin(), str.end(), '.');
   size_t count_comma = count(str.begin(), str.end(), ',');

   if(count_dot+count_comma > 1) return false;
   if(count(str.begin(), str.end(), '-') > 1) return false;

   return(str.find_first_not_of("-.,0123456789")==std::string::npos);
}

/******************************************************************************/
/*  IsIntValue                                                                */
/******************************************************************************/
bool IsIntValue(const string& str)
{
   string StrTemp = str;
   if(StrTemp.substr(0, 1)=="-") StrTemp.erase(0, 1);

   return(StrTemp.find_first_not_of("0123456789")==std::string::npos);
}

/******************************************************************************/
/*  IsHexValue                                                                */
/******************************************************************************/
bool IsHexValue(const string& str)
{
   string StrTemp = str;
   bool bSign = false;
   if(StrTemp.substr(0, 2)=="0x"){
      StrTemp.erase(0, 2);
      bSign = true;
   }

   if(StrTemp.substr(StrTemp.size()-1)=="h"){
      if(bSign) return false;
      StrTemp.erase(StrTemp.size()-1, 1);
   }

   return(StrTemp.find_first_not_of("0123456789AaBbCcDdEeFf")==std::string::npos);
}

/******************************************************************************/
/*  IsIpv4                                                                    */
/******************************************************************************/
bool IsIpv4(const string& str)
{
   if(count(str.begin(), str.end(), '.')!=3) return false;

   if(str.find_first_not_of(".0123456789")!=std::string::npos) return false;

   vector<string> StrList = Split(str, '.');

   for(auto& str: StrList){
      if(!IsIntValue(str) || atoi(str.c_str()) > 255) return false;
   }

   return true;
}

/******************************************************************************/
/*  IsMacAddr                                                                 */
/******************************************************************************/
bool IsMacAddr(const string& str)
{
   char Sep;
   if(count(str.begin(), str.end(), ':')==5)       Sep = ':';
   else if(count(str.begin(), str.end(), '-')==5)  Sep = '-';
   else return false;

   vector<string> StrList = Split(str, Sep);

   for(auto& str: StrList){
      if(!IsHexValue(str) || str.length()!=2) return false;
   }

   return true;
}

/******************************************************************************/
/*  Ipv4ToStr                                                                 */
/******************************************************************************/
string Ipv4ToStr(uint32_t u32Ip)
{
   in_addr Ip;
   Ip.s_addr = u32Ip;
   return string(inet_ntoa(Ip));
}

/******************************************************************************/
/*  StrToInt                                                                  */
/******************************************************************************/
bool StrToInt(const string& str, int& val)
{
   if(!IsIntValue(str)) return false;
   try{
      val = stoi(str, nullptr, 0);
   }
   catch(...){
      return false;
   }

   return true;
}
