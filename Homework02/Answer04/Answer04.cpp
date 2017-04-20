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
    generateTradeDates(200, tradeDateList);
    finder.sortByOperatorLess(tradeDateList);

    function<void(TRADE_DATE)> new_function =
        bind(
            &intersection_finder::intersect,
            &finder,
            placeholders::_1,
            tradeDateList.begin(),
            tradeDateList.end());

    for (auto date : tradeDateList)
    {
        new_function(date);
    }

	return 0;
}

