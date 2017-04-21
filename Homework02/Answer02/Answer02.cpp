// Answer02.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <random>
using namespace std;

#include "TradeDate.h"

/*
Write a random TRADE_DATE generator (by std::random_device), which can
generate 100,000 TRADE_DATE objects and store in a container
2.1. note that the duration should be positive value between 1 to 10 days for
each object. And all the year is between 1900 to 2000 A.D.
*/


//
// generate 100000 Trade Dates
//
void generateTradeDates(vector<TRADE_DATE>& list)
{
    list.clear();
    
    int maxDays = getDaysSince01_01_1900(make_tuple<int, int, int>(2001, 1, 1));

    random_device rd;
    uniform_int_distribution<int> distDays(0, maxDays - 1);
    uniform_int_distribution<int> distDuration(1, 10);
    tuple<int, int, int> begin_date;

    for (int i = 0; i < 100000; i++)
    {
        int days = distDays(rd);
        int duration = distDuration(rd);
        if (days + duration > maxDays)
            duration = maxDays - days;

        setDateSince01_01_1900(days, begin_date);

        list.push_back(TRADE_DATE(begin_date, duration));
    }
}



int _tmain(int argc, _TCHAR* argv[])
{
    vector<TRADE_DATE> list;
    generateTradeDates(list);

    for (const auto& date : list)
    {
        date.print();
    }

    return 0;
}

