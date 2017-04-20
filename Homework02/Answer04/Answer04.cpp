// Answer04.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <functional>
#include "TradeDate04.h"
#include "IntersectionFinder04.h"


/*
Use std::bind to create std::function that can print out all intersection of a
TRADE_DATE object in the vector
4.1. std::function < void(TRADE_DATE) > new_function = std::bind
(intersection_finder, …);
*/


int _tmain(int argc, _TCHAR* argv[])
{
    vector<TRADE_DATE> tradeDateList;
    intersection_finder finder;
    generateTradeDates(1000, tradeDateList);
    finder.sortByOperatorLess(tradeDateList);

    function<void(const TRADE_DATE&)> new_function =
        bind(
            &intersection_finder::intersect,
            &finder,
            placeholders::_1,
            tradeDateList.begin(),
            tradeDateList.end());

    TRADE_DATE testDate1(tradeDateList[250].getBeginDate(), 10);
    TRADE_DATE testDate2(tradeDateList[500].getBeginDate(), 10);
    TRADE_DATE testDate3(tradeDateList[750].getBeginDate(), 10);

    new_function(testDate1);
    new_function(testDate2);
    new_function(testDate3);
    
	return 0;
}

