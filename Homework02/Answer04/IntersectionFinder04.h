#pragma once

#include <algorithm>
using namespace std;

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

    void intersect(const TRADE_DATE& date,
        vector<TRADE_DATE>::const_iterator first,
        vector<TRADE_DATE>::const_iterator last) const
    {
        // use lower_bound() and upper_bound() to find the candidates that would intersect with the target.

        // check the beginning date
        auto low = lower_bound(first, last, date);

        // check the end date
        auto date2 = TRADE_DATE(date.getEndDate(), 0);
        auto up = upper_bound(first, last, date2);

        // do the intersection test
        for (auto itr = low; itr < up; ++itr)
        {
            if (itr->getID() == date.getID())
                continue;

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
            intersect(date, tradeDateList.begin() + head, tradeDateList.end());
            head++;
        }
    }

};

