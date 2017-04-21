// Answer03.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <algorithm>
#include "TradeDate03.h"

/*
Write a class “intersection_finder”
• print out all the TRADE_DATE objects that have overlaps
    • first, sort all the objects according to the begin_date with the std::sort,
        with the following predicates (write and test all of them)
        • an operator < in the class
        • an additional functor
        • a lambda function
    • second, use std::lower_bound/std::upper_bound to probe the possible
    intersection each object one after one:
        • For example:
        • auto low=std::lower_bound (v.begin(), v.end(), aaa);
        • auto up= std::upper_bound (v.begin(), v.end(), bbb);
        • check all objects in the range between “low” and “up”, and calculate
        the length of the overlapping days
    • The result should look like:
        • TRADE_DATA ID: X overlaps with TRADE_DATE ID: Y by Z days.
            • print out the date of X and Y to validate by eyeball check
*/



class intersection_finder
{
public:
    void sortByOperatorLess(vector<TRADE_DATE>& tradeDateList)
    {
        sort(tradeDateList.begin(), tradeDateList.end());
    }

    void sortByFunctor(vector<TRADE_DATE>& tradeDateList)
    {
        sort(tradeDateList.begin(), tradeDateList.end(), less<TRADE_DATE>());
    }

    void sortByLambdaFunction(vector<TRADE_DATE>& tradeDateList)
    {
        sort(tradeDateList.begin(), tradeDateList.end(),
            [](const TRADE_DATE& date1, const TRADE_DATE& date2){
            return date1 < date2;
        });
    }

    void testIntersection(const TRADE_DATE& date,
        vector<TRADE_DATE>::const_iterator first,
        vector<TRADE_DATE>::const_iterator last) const
    {
        // use lower_bound() and upper_bound() to find the candidates that would intersect with the target.

        // check the beginning date
        auto low = lower_bound(first, last, date);

        // check the end date
        auto date2 = TRADE_DATE(date.getEndDate(), 0);
        auto up = upper_bound(low, last, date2);

        // do the intersection test
        for (auto itr = low; itr < up; ++itr)
        {
            int days = itr->testIntersection(date);
            if (days > 0)
            {
                date.print();
                itr->print();
                cout << "TRADE_DATA ID : " << date.getID()
                    << " overlaps with TRADE_DATE ID : " << itr->getID()
                    << " by " << days << " days." << endl << endl;
            }
        }
    }

    void testIntersection(const vector<TRADE_DATE>& tradeDateList) const
    {
        // head is used to bypass the data that is already tested.
        int head = 1;
        
        // loop througn all dates in the list
        for (const auto& date : tradeDateList)
        {
            testIntersection(date, tradeDateList.begin() + head, tradeDateList.end());
            head++;
        }
    }

};


int _tmain(int argc, _TCHAR* argv[])
{
    vector<TRADE_DATE> tradeDateList1;
    vector<TRADE_DATE> tradeDateList2;
    vector<TRADE_DATE> tradeDateList3;

    intersection_finder finder;

    generateTradeDates(1000, tradeDateList1);
    generateTradeDates(1000, tradeDateList2);
    generateTradeDates(1000, tradeDateList3);

    finder.sortByOperatorLess(tradeDateList1);
    finder.sortByFunctor(tradeDateList2);
    finder.sortByLambdaFunction(tradeDateList3);

    finder.testIntersection(tradeDateList1);

    return 0;
}

